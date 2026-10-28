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
      },
    );

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
