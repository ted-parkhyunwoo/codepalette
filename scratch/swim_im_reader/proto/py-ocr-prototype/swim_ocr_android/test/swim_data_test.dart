import 'package:flutter_test/flutter_test.dart';
import 'package:swim_ocr_android/swim_data.dart';

void main() {
  group('analyzeSwimText', () {
    test('parses laps, attaches rest, and summarizes stroke pace', () {
      final analysis = analyzeSwimText('1 자유형 0:32.5\n휴식 0:10\n2 자유형 0:35.0');

      expect(analysis.records, hasLength(2));
      expect(analysis.records.first.stroke, '자유');
      expect(analysis.records.first.restSeconds, 10);
      expect(analysis.records.last.lapNumber, 2);
      expect(analysis.strokeSummaries.single.totalDistanceMeters, 50);
      expect(analysis.strokeSummaries.single.paceSecondsPer100m, 135);
    });

    test(
      'combines consecutive butterfly-backstroke-breaststroke-freestyle laps',
      () {
        final analysis = analyzeSwimText(
          '3 접영 0:30.0\n'
          '4 배영 0:32.0\n'
          '5 평영 0:35.0\n'
          '6 자유형 0:28.0',
        );

        expect(analysis.imRecords, hasLength(1));
        expect(analysis.imRecords.single.lapNumber, 3);
        expect(analysis.imRecords.single.distanceMeters, 100);
        expect(analysis.imRecords.single.timeSeconds, 125);
        expect(analysis.imRecords.single.splitsSeconds, [30, 32, 35, 28]);
        expect(analysis.imRecords.single.inferred, isFalse);
      },
    );

    test('infers butterfly when OCR reads the first stroke as freestyle', () {
      final analysis = analyzeSwimText(
        '1 자유형 0:30.0\n휴식 0:05.0\n'
        '2 배영 0:32.0\n휴식 0:06.0\n'
        '3 평영 0:35.0\n휴식 0:07.0\n'
        '4 자유형 0:28.0\n휴식 0:99.0',
      );

      expect(analysis.imRecords, hasLength(1));
      expect(analysis.imRecords.single.inferred, isTrue);
      expect(
        analysis.imRecords.single.transitionRestSeconds,
        [5, 6, 7],
      );
      expect(analysis.imRecords.single.restSeconds, 18);
    });

    test('can disable inferred IM100 sessions', () {
      const inferredText = '1 자유형 0:30.0\n'
          '2 배영 0:32.0\n'
          '3 평영 0:35.0\n'
          '4 자유형 0:28.0';
      final analysis = analyzeSwimText(inferredText, inferIm100: false);
      final explicitImAnalysis = analyzeSwimText(
        '1 접영 0:30.0\n'
        '2 배영 0:32.0\n'
        '3 평영 0:35.0\n'
        '4 자유형 0:28.0',
        inferIm100: false,
      );

      expect(analysis.imRecords, isEmpty);
      expect(explicitImAnalysis.imRecords, hasLength(1));
      expect(explicitImAnalysis.imRecords.single.inferred, isFalse);
    });

    test('excludes a long lap from pace but preserves its record and totals',
        () {
      final analysis = analyzeSwimText(
        '1 자유형 0:30.0\n'
        '2 자유형 0:32.0\n'
        '3 자유형 0:35.0\n'
        '4 자유형 2:00.0',
      );
      final summary = analysis.strokeSummaries.single;

      expect(analysis.records.last.paceExcluded, isTrue);
      expect(summary.totalTimeSeconds, 217);
      expect(summary.totalDistanceMeters, 100);
      expect(summary.paceTimeSeconds, 97);
      expect(summary.paceDistanceMeters, 75);
      expect(summary.paceSecondsPer100m, closeTo(129.333333, 0.000001));
      expect(summary.excludedLapNumbers, [4]);
    });

    test('keeps laps at exactly 1.7 times the untrimmed median', () {
      final analysis = analyzeSwimText(
        '1 자유형 0:30.0\n'
        '2 자유형 0:30.0\n'
        '3 자유형 0:51.0',
      );

      expect(analysis.records.last.paceExcluded, isFalse);
    });

    test('can retain outlier laps in pace calculations', () {
      final analysis = analyzeSwimText(
        '1 자유형 0:30.0\n'
        '2 자유형 0:32.0\n'
        '3 자유형 0:35.0\n'
        '4 자유형 2:00.0',
        excludePaceOutliers: false,
      );
      final summary = analysis.strokeSummaries.single;

      expect(analysis.records.last.paceExcluded, isFalse);
      expect(summary.paceTimeSeconds, 217);
      expect(summary.paceDistanceMeters, 100);
      expect(summary.excludedLapNumbers, isEmpty);
      expect(summary.paceSecondsPer100m, 217);
    });

    test('uses the more lenient 2.5 threshold when fins are included', () {
      final analysis = analyzeSwimText(
        '1 자유형 0:30.0\n'
        '2 자유형 0:30.0\n'
        '3 자유형 0:30.0\n'
        '4 자유형 1:00.0',
        finSwimmingIncluded: true,
      );

      expect(analysis.records.last.paceExcluded, isFalse);
    });

    test('trims two paces from each end when there are 12 to 19 laps', () {
      final seconds = [
        10,
        10,
        30,
        30,
        30,
        30,
        30,
        30,
        75,
        75,
        75,
        75,
      ];
      final analysis = analyzeSwimText(
        List.generate(
          seconds.length,
          (index) =>
              '${index + 1} 자유형 ${seconds[index] ~/ 60}:${(seconds[index] % 60).toString().padLeft(2, '0')}',
        ).join('\n'),
      );

      expect(
        analysis.records.map((record) => record.paceExcluded),
        [
          false,
          false,
          false,
          false,
          false,
          false,
          false,
          false,
          true,
          true,
          true,
          true
        ],
      );
      expect(analysis.strokeSummaries.single.paceSecondsPer100m, 100);
    });

    test('trims three paces from each end when there are at least 20 laps', () {
      final seconds = [
        10,
        10,
        10,
        10,
        ...List<int>.filled(14, 30),
        75,
        75,
        75,
        75,
        75,
        75,
      ];
      final analysis = analyzeSwimText(
        List.generate(
          seconds.length,
          (index) =>
              '${index + 1} 자유형 ${seconds[index] ~/ 60}:${(seconds[index] % 60).toString().padLeft(2, '0')}',
        ).join('\n'),
      );

      expect(analysis.records, hasLength(24));
      expect(
        analysis.records.where((record) => record.paceExcluded),
        hasLength(6),
      );
      expect(
        analysis.strokeSummaries.single.paceSecondsPer100m,
        closeTo(102.222222, 0.000001),
      );
    });

    test('detects a 50-meter pool and labels the IM as 200 meters', () {
      final analysis = analyzeSwimText(
        '구간(50m)\n'
        '1 접영 0:30.0\n'
        '2 배영 0:32.0\n'
        '3 평영 0:35.0\n'
        '4 자유형 0:28.0',
      );

      expect(analysis.poolLengthMeters, 50);
      expect(analysis.records.every((record) => record.distanceMeters == 50),
          isTrue);
      expect(analysis.imRecords.single.distanceMeters, 200);
    });

    test(
        'does not count the same lap twice when overlapping OCR tiles repeat it',
        () {
      final analysis = analyzeSwimText(
        '구간(25m)\n'
        '1 자유형 0:30.0\n'
        '2 평영 0:32.0\n'
        '2 평영 0:32.8\n'
        '3 자유형 0:35.0',
      );

      expect(analysis.records.map((record) => record.lapNumber), [1, 2, 3]);
      expect(
        analysis.records.fold<int>(
          0,
          (total, record) => total + record.distanceMeters,
        ),
        75,
      );
    });

    test('recovers a lap number omitted by OCR between numbered laps', () {
      final analysis = analyzeSwimText(
        '구간(25m)\n'
        '8 자유형(크롤) 00:19.5\n'
        '자유형(크롤) 00:15.0 01\'00"\n'
        '휴식 00:17.0\n'
        '10 자유형(크롤) 00:18.8',
      );

      expect(analysis.records.map((record) => record.lapNumber), [8, 9, 10]);
      expect(analysis.records[1].stroke, '자유');
      expect(analysis.records[1].timeSeconds, 15);
      expect(analysis.records[1].restSeconds, 17);
      expect(analysis.totalDistanceMeters, 75);
    });

    test('keeps all 60 laps and 1500m when OCR misses lap 9 number', () {
      final lines = ['구간(25m)'];
      for (var lapNumber = 1; lapNumber <= 60; lapNumber++) {
        lines.add(
          lapNumber == 9
              ? '자유형(크롤) 00:15.0 01\'00"'
              : '$lapNumber 자유형(크롤) 00:20.0 01\'20"',
        );
        if (lapNumber == 9) lines.add('휴식 00:17.0');
      }

      final analysis = analyzeSwimText(lines.join('\n'));

      expect(analysis.records, hasLength(60));
      expect(analysis.totalDistanceMeters, 1500);
      expect(
        analysis.records.map((record) => record.lapNumber),
        List<int>.generate(60, (index) => index + 1),
      );
      expect(analysis.records[8].restSeconds, 17);
    });

    test('does not re-add an unnumbered duplicate before a numbered lap', () {
      final records = parseSwimRecords([
        '8 자유형 0:20.0',
        '자유형 0:20.0',
        '9 자유형 0:21.0',
      ]);

      expect(records.map((record) => record.lapNumber), [8, 9]);
      expect(records.last.timeSeconds, 21);
    });

    test('does not combine an IM when lap sequence has a gap', () {
      final records = parseSwimRecords([
        '1 접영 0:30',
        '2 배영 0:32',
        '4 평영 0:35',
        '5 자유형 0:28',
      ]);

      expect(findImRecords(records), isEmpty);
    });
  });
}
