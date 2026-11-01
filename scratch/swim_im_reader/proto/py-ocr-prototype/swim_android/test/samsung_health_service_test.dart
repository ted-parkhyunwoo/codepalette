import 'dart:convert';

import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:swim_android/models/swim_health_session.dart';
import 'package:swim_android/services/samsung_health_service.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  const channel = MethodChannel('com.codepalette.swim_android/health');
  final messenger =
      TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger;

  setUp(() {
    SharedPreferences.setMockInitialValues({});
  });

  tearDown(() {
    messenger.setMockMethodCallHandler(channel, null);
  });

  test(
    'loads once, then requests only from the last workout and persists',
    () async {
      final firstWorkout = DateTime(2026, 10, 1, 7);
      final latestWorkout = DateTime(2026, 10, 10, 7);
      final newWorkout = DateTime(2026, 10, 20, 7);
      final calls = <MethodCall>[];
      messenger.setMockMethodCallHandler(channel, (call) async {
        calls.add(call);
        if (calls.length == 1) {
          return [_session(firstWorkout), _session(latestWorkout)];
        }
        return [_session(latestWorkout), _session(newWorkout)];
      });

      final service = SamsungHealthService();
      final initial = await service.synchronizeSessions();
      expect(calls.first.arguments, isNull);
      expect(initial.sessions, hasLength(2));
      expect(initial.lastWorkoutTime, latestWorkout);

      await service.saveSession(
        initial.sessions.first.withEditedRestSeconds([12]),
      );
      final updated = await service.synchronizeSessions();
      expect(calls.last.arguments, {
        'sinceTimeMillis': latestWorkout.millisecondsSinceEpoch,
      });
      expect(updated.sessions, hasLength(3));
      expect(updated.lastWorkoutTime, newWorkout);

      final restored = await service.readCachedSessions();
      expect(restored.sessions, hasLength(3));
      expect(restored.lastWorkoutTime, newWorkout);
      expect(restored.sessions.first.restAnalysis!.restSecondsByLap, [12]);
    },
  );

  test('refreshes cache for end-time data and keeps lap rests', () async {
    final workout = DateTime(2026, 10, 10, 7);
    final originalSession = SwimHealthSession.fromMap(_session(workout))
        .withEditedRestSeconds([8]);
    final oldSessionData = originalSession.toMap()..remove('endTimeMillis');
    SharedPreferences.setMockInitialValues({
      'swim_health_session_cache_v1': jsonEncode({
        'heartRateDataVersion': 1,
        'lastWorkoutTimeMillis': workout.millisecondsSinceEpoch,
        'sessions': [oldSessionData],
      }),
    });
    final calls = <MethodCall>[];
    messenger.setMockMethodCallHandler(channel, (call) async {
      calls.add(call);
      return [
        {
          ..._session(workout),
          'endTimeMillis': workout
              .add(const Duration(seconds: 60))
              .millisecondsSinceEpoch,
          'heartRateSamples': [
            {
              'timestampMillis': workout
                  .add(const Duration(seconds: 10))
                  .millisecondsSinceEpoch,
              'heartRateBpm': 140,
            },
          ],
        },
      ];
    });

    final service = SamsungHealthService();
    final updated = await service.synchronizeSessions();

    expect(calls.single.arguments, isNull);
    expect(updated.sessions.single.heartRateSamples, hasLength(1));
    expect(
      updated.sessions.single.endTime,
      workout.add(const Duration(seconds: 60)),
    );
    expect(updated.sessions.single.restAnalysis!.restSecondsByLap, [8]);
    final savedCache = jsonDecode(
      (await SharedPreferences.getInstance()).getString(
        'swim_health_session_cache_v1',
      )!,
    ) as Map<String, dynamic>;
    expect(savedCache['heartRateDataVersion'], 2);
  });
}

Map<String, Object?> _session(DateTime startTime) => {
  'startTimeMillis': startTime.millisecondsSinceEpoch,
  'exerciseType': 'SWIMMING',
  'durationSeconds': 60,
  'distanceMeters': 100,
  'poolLengthMeters': 25,
  'intervals': [
    {'durationSeconds': 30, 'strokeType': 'FREESTYLE', 'strokeCount': 20},
  ],
};
