package com.example.shealthreadtest

import android.os.Bundle
import android.widget.Button
import android.widget.LinearLayout
import android.widget.ScrollView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.lifecycleScope
import com.samsung.android.sdk.health.data.HealthDataService
import com.samsung.android.sdk.health.data.HealthDataStore
import com.samsung.android.sdk.health.data.permission.AccessType
import com.samsung.android.sdk.health.data.permission.Permission
import com.samsung.android.sdk.health.data.request.LocalTimeFilter
import com.samsung.android.sdk.health.data.request.DataTypes
import kotlinx.coroutines.launch
import java.time.LocalDate
import java.time.LocalDateTime

class MainActivity : AppCompatActivity() {
    private lateinit var output: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        output = TextView(this).apply {
            text = "Samsung Health Data SDK read test\n\nTap the button to request Exercise read access."
            textSize = 16f
            setPadding(28, 24, 28, 24)
        }

        val button = Button(this).apply {
            text = "Request permission and read exercises"
            setOnClickListener { runReadTest() }
        }

        val layout = LinearLayout(this).apply {
            orientation = LinearLayout.VERTICAL
            setPadding(16, 16, 16, 16)
            addView(button)
            addView(output)
        }
        setContentView(ScrollView(this).apply { addView(layout) })
    }

    private fun runReadTest() {
        output.text = "Connecting to Samsung Health…"
        lifecycleScope.launch {
            try {
                val store: HealthDataStore = HealthDataService.getStore(applicationContext)
                val permissions = setOf(
                    Permission.of(DataTypes.EXERCISE, AccessType.READ)
                )
                val granted = store.getGrantedPermissions(permissions)
                if (!granted.containsAll(permissions)) {
                    output.text = "Requesting Exercise read permission…"
                    store.requestPermissions(permissions, this@MainActivity)
                }

                output.text = "Reading exercise records from the last 90 days…"
                val start = LocalDate.now().minusDays(90).atStartOfDay()
                val end = LocalDateTime.now()
                val filter = LocalTimeFilter.of(start, end)
                val request = DataTypes.EXERCISE.readDataRequestBuilder
                    .setLocalTimeFilter(filter)
                    .build()
                val result = store.readData(request)
                val points = result.dataList

                if (points.isEmpty()) {
                    output.text = "SDK read call succeeded, but no Exercise records were returned for the last 90 days."
                    return@launch
                }

                val text = StringBuilder("Read succeeded. Exercise data points: ${points.size}\n\n")
                points.forEachIndexed { index, point ->
                    text.append("Record ${index + 1}\n")
                    val type = point.getValue(com.samsung.android.sdk.health.data.request.DataType.ExerciseType.EXERCISE_TYPE)
                    val sessions = point.getValue(com.samsung.android.sdk.health.data.request.DataType.ExerciseType.SESSIONS)
                    text.append("Exercise type: $type\n")
                    text.append("Sessions: ${sessions?.size ?: 0}\n")
                    sessions?.forEach { session ->
                        text.append(" • ${session.exerciseType}, duration=${session.duration}, calories=${session.calories}\n")
                    }
                    text.append("\n")
                }
                output.text = text.toString()
            } catch (e: Exception) {
                output.text = "Read test failed:\n${e.javaClass.name}\n${e.message ?: "(no message)"}"
            }
        }
    }
}
