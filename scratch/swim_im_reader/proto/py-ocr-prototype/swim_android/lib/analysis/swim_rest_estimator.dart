import '../swim_analysis.dart';

/// OCR 랩 결과와 삼성 헬스 데이터를 비교한 휴식 추정 결과
class SwimRestEstimate {
  const SwimRestEstimate({
    required this.restSecondsByLap,
    required this.recognizedLapCount,
    required this.needsReview,
    required this.accuracyPercent,
  });

  final List<double?> restSecondsByLap;
  final int recognizedLapCount;
  final bool needsReview;
  final double accuracyPercent;
}

/// OCR 인식 결과에서 휴식 시간·일치율·검토 필요 여부를 계산
class SwimRestEstimator {
  const SwimRestEstimator._();

  /// 랩 번호, 영법, 랩 시간을 비교하고 99% 미만은 검토 대상으로 분류
  static SwimRestEstimate estimate({
    required List<double> intervalDurationsSeconds,
    required List<String> intervalStrokes,
    required SwimAnalysis ocrAnalysis,
  }) {
    if (intervalDurationsSeconds.length != intervalStrokes.length) {
      throw ArgumentError('삼성 헬스 랩 시간과 영법 개수가 일치하지 않음');
    }
    final recordsByLap = {
      for (final record in ocrAnalysis.records) record.lapNumber: record,
    };
    final accuracy = _calculateAccuracy(
      intervalDurationsSeconds,
      intervalStrokes,
      ocrAnalysis,
      recordsByLap,
    );
    final restSecondsByLap = List<double?>.generate(
      intervalDurationsSeconds.length,
      (index) {
        final record = recordsByLap[index + 1];
        return record == null
            ? null
            : (record.restCount > 0 ? record.restSeconds : 0);
      },
    );
    final hasLapCountMismatch =
        ocrAnalysis.records.length != intervalDurationsSeconds.length ||
        ocrAnalysis.estimatedMissingLapCount > 0 ||
        recordsByLap.length != intervalDurationsSeconds.length;
    final hasDurationMismatch =
        List<int>.generate(
          intervalDurationsSeconds.length,
          (index) => index,
        ).any((index) {
          final record = recordsByLap[index + 1];
          if (record == null) return false;
          final expectedSeconds = intervalDurationsSeconds[index];
          final difference = (record.timeSeconds - expectedSeconds).abs();
          return difference > 15 && difference > expectedSeconds * 0.35;
        });
    final hasStrokeMismatch =
        List<int>.generate(
          intervalDurationsSeconds.length,
          (index) => index,
        ).any((index) {
          final record = recordsByLap[index + 1];
          return record != null &&
              _normalizeStroke(record.stroke) !=
                  _normalizeStroke(intervalStrokes[index]);
        });
    return SwimRestEstimate(
      restSecondsByLap: restSecondsByLap,
      recognizedLapCount: ocrAnalysis.records.length,
      needsReview:
          hasLapCountMismatch ||
          hasDurationMismatch ||
          hasStrokeMismatch ||
          accuracy < 99,
      accuracyPercent: accuracy,
    );
  }
}

double _calculateAccuracy(
  List<double> intervalDurationsSeconds,
  List<String> intervalStrokes,
  SwimAnalysis analysis,
  Map<int, SwimRecord> recordsByLap,
) {
  final comparisonCount =
      intervalDurationsSeconds.length > analysis.records.length
      ? intervalDurationsSeconds.length
      : analysis.records.length;
  if (comparisonCount == 0) return 0;
  var score = 0.0;
  for (var index = 0; index < comparisonCount; index++) {
    if (index >= intervalDurationsSeconds.length) continue;
    final record = recordsByLap[index + 1];
    if (record == null) continue;
    final intervalDuration = intervalDurationsSeconds[index];
    final durationDifference = (record.timeSeconds - intervalDuration).abs();
    final durationAccuracy =
        (1 -
                durationDifference /
                    intervalDuration.abs().clamp(1, double.infinity))
            .clamp(0, 1)
            .toDouble();
    score += 1;
    score +=
        _normalizeStroke(record.stroke) ==
            _normalizeStroke(intervalStrokes[index])
        ? 1
        : 0;
    score += durationAccuracy;
  }
  return score / (comparisonCount * 3) * 100;
}

String _normalizeStroke(String stroke) {
  final normalized = stroke.trim().replaceAll(' ', '');
  return switch (normalized) {
    '자유' || '자유형' => '자유형',
    '접영' => '접영',
    '배영' => '배영',
    '평영' => '평영',
    '혼영' || 'IM' => '혼영',
    '킥판' => '킥판',
    _ => normalized,
  };
}
