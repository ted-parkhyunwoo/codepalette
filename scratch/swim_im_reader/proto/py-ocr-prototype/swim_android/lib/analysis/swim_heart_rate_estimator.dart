import '../models/swim_heart_rate_sample.dart';

/// 누산한 랩 구간과 절대 시각 심박 로그의 연결 결과
class HeartRateLapWindow {
  const HeartRateLapWindow({
    required this.startElapsedSeconds,
    required this.endElapsedSeconds,
    required this.samples,
  });

  final double startElapsedSeconds;
  final double endElapsedSeconds;
  final List<SwimHeartRateSample> samples;
}

/// 랩 시간과 OCR 휴식 시간을 누산해 심박 로그를 랩 구간에 배정
class SwimHeartRateEstimator {
  const SwimHeartRateEstimator._();

  /// 휴식은 누산 시간에만 반영하고 휴식 중 심박 로그는 어떤 랩에도 넣지 않음
  ///
  /// 첫 랩 및 10분 이상 휴식 뒤에는 세 번 연속 상승하는 로그가 있을 때만
  /// 해당 활동 시작 시각을 다음 랩의 기준으로 사용
  static List<HeartRateLapWindow> mapSamplesToLaps({
    required DateTime startTime,
    required DateTime endTime,
    required List<double> lapDurationsSeconds,
    required List<double?> restSecondsByLap,
    required List<SwimHeartRateSample> heartRateSamples,
    bool alignActivityOnset = true,
  }) {
    if (endTime.isBefore(startTime)) {
      throw ArgumentError.value(endTime, 'endTime', '세션 종료는 시작 이후여야 함');
    }
    if (lapDurationsSeconds.length != restSecondsByLap.length) {
      throw ArgumentError('랩 시간과 휴식 시간의 개수가 일치하지 않음');
    }
    final sessionElapsedSeconds =
        endTime.difference(startTime).inMilliseconds / 1000;
    final samples =
        heartRateSamples
            .where(
              (sample) =>
                  !sample.timestamp.isBefore(startTime) &&
                  sample.timestamp.isBefore(endTime),
            )
            .toList()
          ..sort(
            (first, second) => first.timestamp.compareTo(second.timestamp),
          );
    final result = <HeartRateLapWindow>[];
    var sampleIndex = 0;
    var timelineSeconds = 0.0;
    if (alignActivityOnset && lapDurationsSeconds.isNotEmpty) {
      final initialSearchLimit = (lapDurationsSeconds.first + 120)
          .clamp(0, sessionElapsedSeconds)
          .toDouble();
      timelineSeconds =
          _activityOnsetSeconds(
            samples,
            startTime: startTime,
            fromSeconds: 0,
            withinSeconds: initialSearchLimit,
          ) ??
          timelineSeconds;
    }

    for (var index = 0; index < lapDurationsSeconds.length; index++) {
      final lapStartSeconds = timelineSeconds;
      final lapEndSeconds = lapStartSeconds + lapDurationsSeconds[index];
      final matchedSamples = <SwimHeartRateSample>[];
      while (sampleIndex < samples.length) {
        final sampleElapsedSeconds =
            samples[sampleIndex].timestamp
                .difference(startTime)
                .inMilliseconds /
            1000;
        if (sampleElapsedSeconds < lapStartSeconds) {
          sampleIndex++;
          continue;
        }
        if (sampleElapsedSeconds >= lapEndSeconds ||
            sampleElapsedSeconds >= sessionElapsedSeconds) {
          break;
        }
        matchedSamples.add(samples[sampleIndex]);
        sampleIndex++;
      }
      result.add(
        HeartRateLapWindow(
          startElapsedSeconds: lapStartSeconds,
          endElapsedSeconds: lapEndSeconds,
          samples: matchedSamples,
        ),
      );

      final restSeconds = restSecondsByLap[index] ?? 0;
      timelineSeconds = lapEndSeconds + restSeconds;
      if (alignActivityOnset &&
          restSeconds >= 600 &&
          index + 1 < lapDurationsSeconds.length) {
        timelineSeconds =
            _activityOnsetSeconds(
              samples,
              startTime: startTime,
              fromSeconds: timelineSeconds,
              withinSeconds: sessionElapsedSeconds - timelineSeconds,
            ) ??
            timelineSeconds;
      }
    }
    return result;
  }

  /// 각 랩 창의 평균·최대 심박을 계산
  static List<({int? average, int? maximum})> summarize(
    List<HeartRateLapWindow> lapWindows,
  ) => [
    for (final window in lapWindows)
      (
        average: window.samples.isEmpty
            ? null
            : (window.samples.fold<int>(
                        0,
                        (total, sample) => total + sample.beatsPerMinute,
                      ) /
                      window.samples.length)
                  .round(),
        maximum: window.samples.isEmpty
            ? null
            : window.samples
                  .map((sample) => sample.beatsPerMinute)
                  .reduce((first, second) => first > second ? first : second),
      ),
  ];

  static double? _activityOnsetSeconds(
    List<SwimHeartRateSample> samples, {
    required DateTime startTime,
    required double fromSeconds,
    required double withinSeconds,
  }) {
    final candidates = samples
        .map(
          (sample) => (
            elapsedSeconds:
                sample.timestamp.difference(startTime).inMilliseconds / 1000,
            beatsPerMinute: sample.beatsPerMinute,
          ),
        )
        .where(
          (sample) =>
              sample.elapsedSeconds >= fromSeconds &&
              sample.elapsedSeconds <= fromSeconds + withinSeconds,
        )
        .toList();
    for (var index = 0; index + 2 < candidates.length; index++) {
      final first = candidates[index];
      final second = candidates[index + 1];
      final third = candidates[index + 2];
      final firstRise = second.beatsPerMinute - first.beatsPerMinute;
      final secondRise = third.beatsPerMinute - second.beatsPerMinute;
      if (firstRise >= 2 &&
          secondRise >= 2 &&
          third.elapsedSeconds - first.elapsedSeconds <= 120) {
        return first.elapsedSeconds;
      }
    }
    return null;
  }
}
