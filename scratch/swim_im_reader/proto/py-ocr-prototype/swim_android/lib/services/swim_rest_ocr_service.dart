import 'dart:io';

import '../swim_analysis.dart';
import 'samsung_health_lap_ocr_reader.dart';

class SwimRestOcrService {
  SwimRestOcrService({SamsungHealthLapOcrReader? reader})
    : _reader = reader ?? SamsungHealthLapOcrReader();

  final SamsungHealthLapOcrReader _reader;

  /// 캡처 텍스트 판독과 랩 패턴 분석을 연결
  Future<SwimAnalysis> analyze(File source, {int? poolLengthMeters}) async {
    final text = await _reader.read(source);
    final analysis = analyzeSwimText(text, poolLengthMeters: poolLengthMeters);
    if (analysis.records.isEmpty) {
      throw const FormatException(
        '랩 기록을 찾지 못했습니다. 삼성 헬스 랩 목록 화면이 보이는 캡처를 선택해 주세요.',
      );
    }
    return analysis;
  }
}
