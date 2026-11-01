package com.codepalette.swim_android

import androidx.lifecycle.lifecycleScope
import com.samsung.android.sdk.health.data.HealthDataService
import com.samsung.android.sdk.health.data.permission.AccessType
import com.samsung.android.sdk.health.data.permission.Permission
import com.samsung.android.sdk.health.data.request.DataTypes
import com.samsung.android.sdk.health.data.request.LocalTimeFilter
import io.flutter.embedding.android.FlutterActivity
import io.flutter.embedding.engine.FlutterEngine
import io.flutter.plugin.common.MethodChannel
import kotlinx.coroutines.launch
import java.time.Instant
import java.time.LocalDate
import java.time.LocalDateTime
import java.time.ZoneId

class MainActivity : FlutterActivity() {
    private val channelName = "com.codepalette.swim_android/health"

    override fun configureFlutterEngine(flutterEngine: FlutterEngine) {
        super.configureFlutterEngine(flutterEngine)
        MethodChannel(flutterEngine.dartExecutor.binaryMessenger, channelName)
            .setMethodCallHandler { call, result ->
                if (call.method != "readSwimSessions") {
                    result.notImplemented()
                } else {
                    readSwimSessions(
                        call.argument<Number>("sinceTimeMillis")?.toLong(),
                        result
                    )
                }
            }
    }

    private fun readSwimSessions(
        sinceTimeMillis: Long?,
        result: MethodChannel.Result
    ) {
        lifecycleScope.launch {
            try {
                val store = HealthDataService.getStore(applicationContext)
                val permissions = setOf(
                    Permission.of(DataTypes.EXERCISE, AccessType.READ)
                )
                if (!store.getGrantedPermissions(permissions).containsAll(permissions)) {
                    store.requestPermissions(permissions, this@MainActivity)
                }
                if (!store.getGrantedPermissions(permissions).containsAll(permissions)) {
                    throw SecurityException("Samsung Health Exercise read permission was not granted.")
                }

                val startTime = sinceTimeMillis?.let {
                    Instant.ofEpochMilli(it).atZone(ZoneId.systemDefault())
                        .toLocalDateTime()
                } ?: LocalDate.now().minusDays(365).atStartOfDay()
                val filter = LocalTimeFilter.of(startTime, LocalDateTime.now())
                val request = DataTypes.EXERCISE.readDataRequestBuilder
                    .setLocalTimeFilter(filter)
                    .build()
                val points = store.readData(request).dataList
                val sessions = points.flatMap { point ->
                    point.getValue(
                        com.samsung.android.sdk.health.data.request.DataType.ExerciseType.SESSIONS
                    ).orEmpty()
                }.mapNotNull { session ->
                    val exerciseType = session.exerciseType.toString()
                    if (!exerciseType.contains("swim", ignoreCase = true) &&
                        !exerciseType.contains("수영")
                    ) {
                        return@mapNotNull null
                    }

                    val swimmingLog = session.swimmingLog
                    val swimmingIntervals = swimmingLog?.swimmingIntervals.orEmpty()
                    val intervals = swimmingIntervals.map { interval ->
                        mapOf(
                            "durationSeconds" to interval.duration.toMillis() / 1000.0,
                            "strokeType" to interval.strokeType.toString(),
                            "strokeCount" to interval.strokeCount
                        )
                    }
                    val heartRateSamples = session.log.orEmpty().mapNotNull { log ->
                        log.heartRate?.let { heartRate ->
                            mapOf(
                                "timestampMillis" to log.timestamp.toEpochMilli(),
                                "heartRateBpm" to heartRate.toDouble()
                            )
                        }
                    }
                    val loggedHeartRates = heartRateSamples.mapNotNull {
                        it["heartRateBpm"] as? Double
                    }
                    mapOf(
                        "startTimeMillis" to session.startTime.toEpochMilli(),
                        "endTimeMillis" to session.endTime.toEpochMilli(),
                        "exerciseType" to exerciseType,
                        "durationSeconds" to session.duration.toMillis() / 1000.0,
                        "averageHeartRateBpm" to (
                            session.meanHeartRate?.toDouble()
                                ?: loggedHeartRates.takeIf { it.isNotEmpty() }?.average()
                        ),
                        "maximumHeartRateBpm" to (
                            session.maxHeartRate?.toDouble()
                                ?: loggedHeartRates.maxOrNull()
                        ),
                        "heartRateSamples" to heartRateSamples,
                        "distanceMeters" to (
                            swimmingLog?.totalDistance?.toDouble()
                                ?: session.distance?.toDouble()
                            ),
                        "calories" to session.calories?.toDouble(),
                        "poolLengthMeters" to swimmingLog?.poolLength,
                        "poolLengthUnit" to swimmingLog?.poolLengthUnit,
                        "intervals" to intervals
                    )
                }.sortedBy { it["startTimeMillis"] as Long }

                result.success(sessions)
            } catch (error: Exception) {
                result.error(
                    "SAMSUNG_HEALTH_READ_FAILED",
                    error.message ?: error.javaClass.simpleName,
                    error.javaClass.name
                )
            }
        }
    }
}
