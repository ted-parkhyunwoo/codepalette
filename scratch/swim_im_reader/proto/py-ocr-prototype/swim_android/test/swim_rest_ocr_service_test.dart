import 'dart:io';

import 'package:flutter_test/flutter_test.dart';
import 'package:swim_android/services/samsung_health_lap_ocr_reader.dart';
import 'package:swim_android/services/swim_rest_ocr_service.dart';

void main() {
  test('separates screenshot text reading from lap-pattern analysis', () async {
    final service = SwimRestOcrService(
      reader: _FixedTextReader('1 접영 0:30\n휴식 0:08\n2 배영 0:32'),
    );

    final analysis = await service.analyze(File('unused-capture.jpg'));

    expect(analysis.records, hasLength(2));
    expect(analysis.records.first.restSeconds, 8);
    expect(analysis.records.last.stroke, '배영');
  });

  test('reports captures without recognized lap records', () {
    final service = SwimRestOcrService(reader: _FixedTextReader('운동 요약'));

    expect(
      service.analyze(File('unused-capture.jpg')),
      throwsA(isA<FormatException>()),
    );
  });
}

class _FixedTextReader extends SamsungHealthLapOcrReader {
  _FixedTextReader(this.text);

  final String text;

  @override
  Future<String> read(File source) async => text;
}
