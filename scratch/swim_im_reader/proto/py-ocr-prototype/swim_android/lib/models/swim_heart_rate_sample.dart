/// 삼성 헬스 로그의 절대 시각 심박 샘플
class SwimHeartRateSample {
  const SwimHeartRateSample({
    required this.timestamp,
    required this.beatsPerMinute,
  });

  factory SwimHeartRateSample.fromMap(Map<String, dynamic> data) {
    final timestampMillis = data['timestampMillis'];
    final beatsPerMinute = data['heartRateBpm'];
    if (timestampMillis is! num || beatsPerMinute is! num) {
      throw const FormatException('삼성 헬스 심박수 기록 형식이 올바르지 않습니다.');
    }
    return SwimHeartRateSample(
      timestamp: DateTime.fromMillisecondsSinceEpoch(timestampMillis.toInt()),
      beatsPerMinute: beatsPerMinute.round(),
    );
  }

  final DateTime timestamp;
  final int beatsPerMinute;

  Map<String, Object> toMap() => {
    'timestampMillis': timestamp.millisecondsSinceEpoch,
    'heartRateBpm': beatsPerMinute,
  };
}
