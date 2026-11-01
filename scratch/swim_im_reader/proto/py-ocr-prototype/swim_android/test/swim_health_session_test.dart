import 'package:flutter_test/flutter_test.dart';
import 'package:swim_android/models/swim_health_session.dart';
import 'package:swim_android/swim_analysis.dart';

void main() {
  group('SwimHealthSession', () {
    test('converts Samsung swim intervals into IM analysis records', () {
      final session = SwimHealthSession.fromMap({
        'startTimeMillis': DateTime(2026, 10, 30, 7).millisecondsSinceEpoch,
        'exerciseType': 'SWIMMING',
        'durationSeconds': 1800,
        'distanceMeters': 400,
        'calories': 250,
        'poolLengthMeters': 25,
        'poolLengthUnit': 'm',
        'intervals': [
          _interval(30, 'FREESTYLE'),
          _interval(32, 'BACKSTROKE'),
          _interval(35, 'BREASTSTROKE'),
          _interval(28, 'FREESTYLE'),
        ],
      });

      final analysis = session.analyze(inferIm100: true);

      expect(session.startTime, DateTime(2026, 10, 30, 7));
      expect(session.displayExerciseType, '수영');
      expect(session.distanceMeters, 400);
      expect(session.intervals.map((interval) => interval.displayStroke), [
        '자유',
        '배영',
        '평영',
        '자유',
      ]);
      expect(analysis.records, hasLength(4));
      expect(analysis.imRecords, hasLength(1));
      expect(analysis.imRecords.single.inferred, isTrue);
      expect(analysis.imRecords.single.timeSeconds, 125);
      expect(analysis.imRecords.single.distanceMeters, 100);
    });

    test('does not infer freestyle-led IM when the option is disabled', () {
      final session = SwimHealthSession.fromMap({
        'startTimeMillis': 1,
        'exerciseType': 'SWIMMING',
        'durationSeconds': 120,
        'poolLengthMeters': 25,
        'intervals': [
          _interval(30, 'FREESTYLE'),
          _interval(32, 'BACKSTROKE'),
          _interval(35, 'BREASTSTROKE'),
          _interval(28, 'FREESTYLE'),
        ],
      });

      expect(session.analyze(inferIm100: false).imRecords, isEmpty);
    });

    test('ignores unknown pool lengths instead of treating them as meters', () {
      final session = SwimHealthSession.fromMap({
        'startTimeMillis': 1,
        'durationSeconds': 60,
        'poolLengthMeters': 0,
        'intervals': [_interval(30, 'FREESTYLE')],
      });

      expect(session.poolLengthMeters, isNull);
      final longCourseAnalysis = session.analyze(
        inferIm100: false,
        longCoursePool: true,
      );
      expect(longCourseAnalysis.poolLengthMeters, 50);
      expect(longCourseAnalysis.records.single.distanceMeters, 50);
    });

    test('supports outlier and fin-swimming pace options', () {
      final session = SwimHealthSession.fromMap({
        'startTimeMillis': 1,
        'durationSeconds': 180,
        'poolLengthMeters': 25,
        'intervals': [
          _interval(30, 'FREESTYLE'),
          _interval(30, 'FREESTYLE'),
          _interval(30, 'FREESTYLE'),
          _interval(70, 'FREESTYLE'),
        ],
      });

      expect(
        session.analyze(inferIm100: false).records.last.paceExcluded,
        isTrue,
      );
      expect(
        session
            .analyze(inferIm100: false, finSwimmingIncluded: true)
            .records
            .last
            .paceExcluded,
        isFalse,
      );
      expect(
        session
            .analyze(inferIm100: false, excludePaceOutliers: false)
            .records
            .last
            .paceExcluded,
        isFalse,
      );
    });

    test(
      'estimates only total rest without assigning it to individual laps',
      () {
        final session = SwimHealthSession.fromMap({
          'startTimeMillis': DateTime(2026, 10, 30, 7).millisecondsSinceEpoch,
          'endTimeMillis': DateTime(
            2026,
            10,
            30,
            7,
            2,
            5,
          ).millisecondsSinceEpoch,
          'durationSeconds': 125,
          'poolLengthMeters': 25,
          'intervals': [
            _interval(30, 'BUTTERFLY', startTime: DateTime(2026, 10, 30, 7)),
            _interval(
              30,
              'BACKSTROKE',
              startTime: DateTime(2026, 10, 30, 7, 0, 40),
            ),
            _interval(
              30,
              'BREASTSTROKE',
              startTime: DateTime(2026, 10, 30, 7, 1, 20),
            ),
            _interval(
              30,
              'FREESTYLE',
              startTime: DateTime(2026, 10, 30, 7, 1, 55),
            ),
          ],
        });

        expect(session.estimatedRestSeconds, 5);
        expect(
          session.toMap()['intervals'],
          everyElement(isNot(contains('startTimeMillis'))),
        );

        final analysis = session.analyze(inferIm100: false);
        expect(
          analysis.records.map((record) => record.restSeconds),
          everyElement(0),
        );
        expect(analysis.imRecords.single.transitionRestSeconds, [
          null,
          null,
          null,
        ]);

        final restored = SwimHealthSession.fromMap(session.toMap());
        expect(restored.estimatedRestSeconds, 5);
      },
    );

    test(
      'maps OCR rest and heart-rate samples to laps and persists analysis',
      () {
        final startTime = DateTime(2026, 10, 30, 7);
        final session = SwimHealthSession.fromMap({
          'startTimeMillis': startTime.millisecondsSinceEpoch,
          'exerciseType': 'POOL_SWIMMING',
          'durationSeconds': 150,
          'poolLengthMeters': 25,
          'intervals': [
            _interval(30, 'BUTTERFLY'),
            _interval(32, 'BACKSTROKE'),
            _interval(35, 'BREASTSTROKE'),
            _interval(28, 'FREESTYLE'),
          ],
          'heartRateSamples': [
            _heartRate(startTime.add(const Duration(seconds: 10)), 130),
            _heartRate(startTime.add(const Duration(seconds: 35)), 140),
            _heartRate(startTime.add(const Duration(seconds: 50)), 150),
          ],
        });

        final ocr = analyzeSwimText(
          '1 접영 0:30.0\n'
          '휴식 0:08.0\n'
          '2 배영 0:32.0\n'
          '휴식 0:05.0\n'
          '3 평영 0:35.0\n'
          '4 자유 0:28.0',
        );
        final analyzed = session.withOcrRestAnalysis(ocr);

        expect(analyzed.restAnalysis!.needsReview, isFalse);
        expect(analyzed.restAnalysis!.restSecondsByLap, [8, 5, 0, 0]);
        expect(analyzed.restAnalysis!.ocrAccuracyPercent, 100);
        expect(analyzed.restAnalysis!.averageHeartRateByLap, [
          130,
          150,
          null,
          null,
        ]);
        expect(analyzed.restAnalysis!.maximumHeartRateByLap, [
          130,
          150,
          null,
          null,
        ]);
        expect(
          analyzed
              .analyze(inferIm100: false)
              .imRecords
              .single
              .transitionRestSeconds,
          [8, 5, null],
        );

        final restored = SwimHealthSession.fromMap(analyzed.toMap());
        expect(restored.restAnalysis!.restSecondsByLap, [8, 5, 0, 0]);
        expect(restored.restAnalysis!.ocrAccuracyPercent, 100);
        expect(restored.displayAverageHeartRateBpm, 140);
        expect(restored.displayMaximumHeartRateBpm, 150);
        expect(restored.heartRateForLap(0).average, 135);
        expect(restored.heartRateForLap(1).average, 150);
      },
    );

    test('does not assign lap heart rates before OCR confirms rests', () {
      final startTime = DateTime(2026, 10, 30, 7);
      final session = SwimHealthSession.fromMap({
        'startTimeMillis': startTime.millisecondsSinceEpoch,
        'durationSeconds': 100,
        'intervals': [
          _interval(20, 'FREESTYLE'),
          _interval(20, 'FREESTYLE'),
          _interval(20, 'FREESTYLE'),
          _interval(20, 'FREESTYLE'),
        ],
        'heartRateSamples': [
          _heartRate(startTime.add(const Duration(seconds: 10)), 100),
          _heartRate(startTime.add(const Duration(seconds: 35)), 110),
          _heartRate(startTime.add(const Duration(seconds: 55)), 120),
          _heartRate(startTime.add(const Duration(seconds: 70)), 130),
        ],
      });

      expect(
        session.heartRatesByLap.map((lap) => lap.average),
        everyElement(isNull),
      );
      expect(session.heartRateForLap(3).maximum, isNull);
    });

    test(
      'does not spread unassigned long breaks across later lap heart rates',
      () {
        final startTime = DateTime(2026, 10, 31, 7);
        const lapCount = 210;
        final restSeconds = List<double?>.filled(lapCount, 0);
        restSeconds[0] = 900;
        final session = SwimHealthSession.fromMap({
          'startTimeMillis': startTime.millisecondsSinceEpoch,
          'durationSeconds': lapCount * 30 + 900 + 900,
          'intervals': [
            for (var index = 0; index < lapCount; index++)
              _interval(30, 'FREESTYLE'),
          ],
          'heartRateSamples': [
            _heartRate(startTime.add(const Duration(seconds: 15)), 100),
            _heartRate(startTime.add(const Duration(seconds: 60)), 150),
            _heartRate(startTime.add(const Duration(seconds: 945)), 120),
            _heartRate(
              startTime.add(const Duration(seconds: 900 + 199 * 30 + 15)),
              160,
            ),
          ],
          'restAnalysis': {
            'restSecondsByLap': restSeconds,
            'recognizedLapCount': lapCount,
            'needsReview': false,
            'averageHeartRateByLap': List<int?>.filled(lapCount, null),
            'maximumHeartRateByLap': List<int?>.filled(lapCount, null),
          },
        });

        expect(session.heartRatesByLap[0].average, 100);
        expect(session.heartRatesByLap[1].average, 120);
        expect(session.heartRatesByLap[199].average, 160);
      },
    );

    test('aligns delayed first lap at the first clear heart-rate rise', () {
      final startTime = DateTime(2026, 10, 31, 7);
      final session = SwimHealthSession.fromMap({
        'startTimeMillis': startTime.millisecondsSinceEpoch,
        'endTimeMillis': startTime
            .add(const Duration(seconds: 240))
            .millisecondsSinceEpoch,
        'durationSeconds': 240,
        'intervals': [
          _interval(30, 'FREESTYLE'),
          _interval(30, 'FREESTYLE'),
          _interval(30, 'FREESTYLE'),
        ],
        'heartRateSamples': [
          _heartRate(startTime.add(const Duration(seconds: 125)), 90),
          _heartRate(startTime.add(const Duration(seconds: 135)), 94),
          _heartRate(startTime.add(const Duration(seconds: 145)), 100),
          _heartRate(startTime.add(const Duration(seconds: 160)), 110),
        ],
        'restAnalysis': {
          'restSecondsByLap': [0, 0, 0],
          'recognizedLapCount': 3,
          'needsReview': false,
          'averageHeartRateByLap': [null, null, null],
          'maximumHeartRateByLap': [null, null, null],
        },
      });

      final lapWindows = session.heartRateSamplesByLap;
      expect(lapWindows[0].startElapsedSeconds, 125);
      expect(lapWindows[0].samples, hasLength(3));
      expect(lapWindows[1].startElapsedSeconds, 155);
      expect(session.heartRatesByLap[0].average, 95);
      expect(session.heartRatesByLap[1].average, 110);
    });

    test('aligns the next lap at activity after a long OCR rest', () {
      final startTime = DateTime(2026, 10, 31, 7);
      final session = SwimHealthSession.fromMap({
        'startTimeMillis': startTime.millisecondsSinceEpoch,
        'endTimeMillis': startTime
            .add(const Duration(seconds: 1050))
            .millisecondsSinceEpoch,
        'durationSeconds': 1050,
        'intervals': [
          _interval(30, 'FREESTYLE'),
          _interval(30, 'FREESTYLE'),
          _interval(30, 'FREESTYLE'),
        ],
        'heartRateSamples': [
          _heartRate(startTime.add(const Duration(seconds: 5)), 90),
          _heartRate(startTime.add(const Duration(seconds: 15)), 94),
          _heartRate(startTime.add(const Duration(seconds: 25)), 100),
          _heartRate(startTime.add(const Duration(seconds: 990)), 90),
          _heartRate(startTime.add(const Duration(seconds: 1000)), 96),
          _heartRate(startTime.add(const Duration(seconds: 1010)), 103),
        ],
        'restAnalysis': {
          'restSecondsByLap': [900, 0, 0],
          'recognizedLapCount': 3,
          'needsReview': false,
          'averageHeartRateByLap': [null, null, null],
          'maximumHeartRateByLap': [null, null, null],
        },
      });
      final lapWindows = session.heartRateSamplesByLap;
      expect(lapWindows[1].startElapsedSeconds, 990);
      expect(lapWindows[1].samples, hasLength(3));
      expect(session.heartRatesByLap[1].average, 96);
      expect(lapWindows[2].startElapsedSeconds, 1020);
    });

    test('does not use a post-rest rise as the first lap onset', () {
      final startTime = DateTime(2026, 10, 31, 7);
      final session = SwimHealthSession.fromMap({
        'startTimeMillis': startTime.millisecondsSinceEpoch,
        'endTimeMillis': startTime
            .add(const Duration(seconds: 1050))
            .millisecondsSinceEpoch,
        'durationSeconds': 1050,
        'intervals': [
          _interval(30, 'FREESTYLE'),
          _interval(30, 'FREESTYLE'),
          _interval(30, 'FREESTYLE'),
        ],
        'heartRateSamples': [
          _heartRate(startTime.add(const Duration(seconds: 990)), 90),
          _heartRate(startTime.add(const Duration(seconds: 1000)), 96),
          _heartRate(startTime.add(const Duration(seconds: 1010)), 103),
        ],
        'restAnalysis': {
          'restSecondsByLap': [900, 0, 0],
          'recognizedLapCount': 3,
          'needsReview': false,
          'averageHeartRateByLap': [null, null, null],
          'maximumHeartRateByLap': [null, null, null],
        },
      });

      final lapWindows = session.heartRateSamplesByLap;
      expect(lapWindows[0].startElapsedSeconds, 0);
      expect(lapWindows[0].samples, isEmpty);
      expect(lapWindows[1].startElapsedSeconds, 990);
      expect(lapWindows[1].samples, hasLength(3));
    });

    test('keeps accumulating OCR rest after a long rest with no HR change', () {
      final startTime = DateTime(2026, 10, 31, 7);
      final session = SwimHealthSession.fromMap({
        'startTimeMillis': startTime.millisecondsSinceEpoch,
        'endTimeMillis': startTime
            .add(const Duration(seconds: 1050))
            .millisecondsSinceEpoch,
        'durationSeconds': 1050,
        'intervals': [
          _interval(30, 'FREESTYLE'),
          _interval(30, 'FREESTYLE'),
          _interval(30, 'FREESTYLE'),
        ],
        'heartRateSamples': [
          _heartRate(startTime.add(const Duration(seconds: 15)), 100),
          _heartRate(startTime.add(const Duration(seconds: 990)), 100),
          _heartRate(startTime.add(const Duration(seconds: 1000)), 99),
          _heartRate(startTime.add(const Duration(seconds: 1010)), 100),
        ],
        'restAnalysis': {
          'restSecondsByLap': [900, 0, 0],
          'recognizedLapCount': 3,
          'needsReview': false,
          'averageHeartRateByLap': [null, null, null],
          'maximumHeartRateByLap': [null, null, null],
        },
      });

      final lapWindows = session.heartRateSamplesByLap;
      expect(lapWindows[1].startElapsedSeconds, 930);
      expect(lapWindows[1].samples, isEmpty);
    });

    test('requires review below 99 percent OCR agreement', () {
      final session = SwimHealthSession.fromMap({
        'startTimeMillis': 1,
        'durationSeconds': 60,
        'poolLengthMeters': 25,
        'intervals': [_interval(30, 'FREESTYLE')],
      }).withOcrRestAnalysis(analyzeSwimText('1 자유 0:31'));

      expect(session.restAnalysis!.ocrAccuracyPercent, closeTo(98.9, 0.1));
      expect(session.restAnalysis!.needsReview, isTrue);
      expect(session.hasCompleteRestAnalysis, isFalse);

      final reviewedSession = session.withEditedRestSeconds([0]);
      expect(reviewedSession.restAnalysis!.needsReview, isFalse);
      expect(reviewedSession.hasCompleteRestAnalysis, isTrue);
      expect(
        reviewedSession.restAnalysis!.ocrAccuracyPercent,
        closeTo(98.9, 0.1),
      );
      expect(
        SwimHealthSession.fromMap(reviewedSession.toMap())
            .restAnalysis!
            .needsReview,
        isFalse,
      );

      final oldCachedSession = session.toMap();
      oldCachedSession['restAnalysis'] = {
        ...session.restAnalysis!.toMap(),
        'needsReview': false,
        'manuallyReviewed': false,
      };
      expect(
        SwimHealthSession.fromMap(oldCachedSession).restAnalysis!.needsReview,
        isTrue,
      );
    });

    test('accepts 99 percent OCR agreement without review', () {
      final session = SwimHealthSession.fromMap({
        'startTimeMillis': 1,
        'durationSeconds': 60,
        'poolLengthMeters': 25,
        'intervals': [_interval(30, 'FREESTYLE')],
      }).withOcrRestAnalysis(analyzeSwimText('1 자유 0:30.9'));

      expect(session.restAnalysis!.ocrAccuracyPercent, closeTo(99, 0.0001));
      expect(session.restAnalysis!.needsReview, isFalse);
      expect(session.hasCompleteRestAnalysis, isTrue);
    });

    test(
      'flags mismatched OCR laps and supports reset and manual correction',
      () {
        final session = SwimHealthSession.fromMap({
          'startTimeMillis': 1,
          'durationSeconds': 120,
          'poolLengthMeters': 25,
          'intervals': [
            _interval(30, 'BUTTERFLY'),
            _interval(32, 'BACKSTROKE'),
            _interval(35, 'BREASTSTROKE'),
            _interval(28, 'FREESTYLE'),
          ],
        });
        final ocr = analyzeSwimText('1 접영 0:30\n2 배영 0:32\n3 평영 0:35');

        final needsReview = session.withOcrRestAnalysis(ocr);
        expect(needsReview.restAnalysis!.needsReview, isTrue);
        expect(needsReview.restAnalysis!.ocrAccuracyPercent, 75);
        expect(needsReview.restAnalysis!.restSecondsByLap, [0, 0, 0, null]);

        final corrected = needsReview.withEditedRestSeconds([2, 3, 0, 0]);
        expect(corrected.restAnalysis!.needsReview, isFalse);
        expect(corrected.restAnalysis!.restSecondsByLap, [2, 3, 0, 0]);
        expect(corrected.withRestAnalysis(null).restAnalysis, isNull);
      },
    );

    test(
      'keeps old cached rest-analysis data readable without OCR accuracy',
      () {
        final session = SwimHealthSession.fromMap({
          'startTimeMillis': 1,
          'durationSeconds': 30,
          'intervals': [_interval(30, 'FREESTYLE')],
          'restAnalysis': {
            'restSecondsByLap': [0],
            'recognizedLapCount': 1,
            'needsReview': false,
            'averageHeartRateByLap': [null],
            'maximumHeartRateByLap': [null],
          },
        });

        expect(session.restAnalysis!.ocrAccuracyPercent, isNull);
      },
    );
  });
}

Map<String, Object?> _interval(
  double durationSeconds,
  String strokeType, {
  DateTime? startTime,
}) => {
  'durationSeconds': durationSeconds,
  'strokeType': strokeType,
  'strokeCount': 20,
  'startTimeMillis': startTime?.millisecondsSinceEpoch,
};

Map<String, int> _heartRate(DateTime timestamp, int bpm) => {
  'timestampMillis': timestamp.millisecondsSinceEpoch,
  'heartRateBpm': bpm,
};
