import '../analysis/swim_heart_rate_estimator.dart';
import '../analysis/swim_rest_estimator.dart';
import '../swim_analysis.dart';
import 'swim_heart_rate_sample.dart';

export 'swim_heart_rate_sample.dart';

class SwimHealthSession {
  const SwimHealthSession({
    required this.startTime,
    required this.endTime,
    required this.exerciseType,
    required this.durationSeconds,
    required this.intervals,
    this.heartRateSamples = const [],
    this.averageHeartRateBpm,
    this.maximumHeartRateBpm,
    this.restAnalysis,
    this.distanceMeters,
    this.calories,
    this.poolLengthMeters,
    this.poolLengthUnit,
  });

  factory SwimHealthSession.fromMap(Map<String, dynamic> data) {
    final rawIntervals = data['intervals'];
    final intervals = rawIntervals is List
        ? rawIntervals
              .whereType<Map>()
              .map(
                (interval) => SwimHealthInterval.fromMap(
                  Map<String, dynamic>.from(interval),
                ),
              )
              .toList()
        : <SwimHealthInterval>[];
    final startTimeMillis = data['startTimeMillis'];
    final endTimeMillis = data['endTimeMillis'];
    final durationSeconds = data['durationSeconds'];
    if (startTimeMillis is! num || durationSeconds is! num) {
      throw const FormatException('삼성 헬스 기록의 날짜 또는 시간이 올바르지 않습니다.');
    }
    final startTime = DateTime.fromMillisecondsSinceEpoch(
      startTimeMillis.toInt(),
    );
    final endTime = endTimeMillis is num
        ? DateTime.fromMillisecondsSinceEpoch(endTimeMillis.toInt())
        : startTime.add(
            Duration(milliseconds: (durationSeconds.toDouble() * 1000).round()),
          );
    if (endTime.isBefore(startTime)) {
      throw const FormatException('삼성 헬스 기록의 종료 시각이 시작 시각보다 빠릅니다.');
    }
    final rawHeartRateSamples = data['heartRateSamples'];
    final heartRateSamples = rawHeartRateSamples is List
        ? rawHeartRateSamples
              .whereType<Map>()
              .map(
                (sample) => SwimHeartRateSample.fromMap(
                  Map<String, dynamic>.from(sample),
                ),
              )
              .toList()
        : <SwimHeartRateSample>[];
    final rawRestAnalysis = data['restAnalysis'];
    final restAnalysis = rawRestAnalysis is Map
        ? SwimRestAnalysis.fromMap(Map<String, dynamic>.from(rawRestAnalysis))
        : null;
    if (restAnalysis != null &&
        (restAnalysis.restSecondsByLap.length != intervals.length ||
            restAnalysis.averageHeartRateByLap.length != intervals.length ||
            restAnalysis.maximumHeartRateByLap.length != intervals.length)) {
      throw const FormatException('저장된 휴식 분석의 랩 수가 세션 기록과 일치하지 않습니다.');
    }

    return SwimHealthSession(
      startTime: startTime,
      endTime: endTime,
      exerciseType: data['exerciseType'] as String? ?? '수영',
      durationSeconds: durationSeconds.toDouble(),
      distanceMeters: _number(data['distanceMeters']),
      calories: _number(data['calories']),
      poolLengthMeters: _poolLength(data['poolLengthMeters']),
      poolLengthUnit: data['poolLengthUnit'] as String?,
      intervals: intervals,
      heartRateSamples: heartRateSamples,
      averageHeartRateBpm: _integer(data['averageHeartRateBpm']),
      maximumHeartRateBpm: _integer(data['maximumHeartRateBpm']),
      restAnalysis: restAnalysis,
    );
  }
  final DateTime startTime;
  final DateTime endTime;
  final String exerciseType;
  final double durationSeconds;
  final double? distanceMeters;
  final double? calories;
  final int? poolLengthMeters;
  final String? poolLengthUnit;
  final List<SwimHealthInterval> intervals;
  final List<SwimHeartRateSample> heartRateSamples;
  final int? averageHeartRateBpm;
  final int? maximumHeartRateBpm;
  final SwimRestAnalysis? restAnalysis;

  bool get hasCompleteRestAnalysis {
    final analysis = restAnalysis;
    return analysis != null &&
        !analysis.needsReview &&
        analysis.restSecondsByLap.length == intervals.length &&
        analysis.restSecondsByLap.every((rest) => rest != null);
  }

  String get displayExerciseType =>
      switch (exerciseType.toUpperCase().split('.').last) {
        'POOL_SWIMMING' => '실내수영',
        'SWIMMING' => '수영',
        _ => exerciseType,
      };

  Map<String, Object?> toMap() => {
    'startTimeMillis': startTime.millisecondsSinceEpoch,
    'endTimeMillis': endTime.millisecondsSinceEpoch,
    'exerciseType': exerciseType,
    'durationSeconds': durationSeconds,
    'distanceMeters': distanceMeters,
    'calories': calories,
    'poolLengthMeters': poolLengthMeters,
    'poolLengthUnit': poolLengthUnit,
    'intervals': intervals.map((interval) => interval.toMap()).toList(),
    'heartRateSamples': heartRateSamples
        .map((sample) => sample.toMap())
        .toList(),
    'averageHeartRateBpm': averageHeartRateBpm,
    'maximumHeartRateBpm': maximumHeartRateBpm,
    'restAnalysis': restAnalysis?.toMap(),
  };

  SwimHealthSession withOcrRestAnalysis(SwimAnalysis analysis) {
    final estimate = SwimRestEstimator.estimate(
      intervalDurationsSeconds: intervals
          .map((interval) => interval.durationSeconds)
          .toList(),
      intervalStrokes: intervals
          .map((interval) => interval.analysisStroke)
          .toList(),
      ocrAnalysis: analysis,
    );
    final heartRates = _heartRatesFor(estimate.restSecondsByLap);
    return _copyWithRestAnalysis(
      SwimRestAnalysis(
        restSecondsByLap: estimate.restSecondsByLap,
        recognizedLapCount: estimate.recognizedLapCount,
        needsReview: estimate.needsReview,
        ocrAccuracyPercent: estimate.accuracyPercent,
        averageHeartRateByLap: heartRates.average,
        maximumHeartRateByLap: heartRates.maximum,
      ),
    );
  }

  SwimHealthSession withEditedRestSeconds(List<double> values) {
    if (values.length != intervals.length ||
        values.any((value) => !value.isFinite || value < 0)) {
      throw ArgumentError.value(values, 'values', '랩별 휴식 시간 값이 올바르지 않습니다.');
    }
    final heartRates = _heartRatesFor(values);
    return _copyWithRestAnalysis(
      SwimRestAnalysis(
        restSecondsByLap: values,
        recognizedLapCount:
            restAnalysis?.recognizedLapCount ?? intervals.length,
        needsReview: false,
        manuallyReviewed: true,
        ocrAccuracyPercent: restAnalysis?.ocrAccuracyPercent,
        averageHeartRateByLap: heartRates.average,
        maximumHeartRateByLap: heartRates.maximum,
      ),
    );
  }

  SwimHealthSession withRestAnalysis(SwimRestAnalysis? analysis) =>
      _copyWithRestAnalysis(analysis);

  SwimHealthSession _copyWithRestAnalysis(SwimRestAnalysis? analysis) =>
      SwimHealthSession(
        startTime: startTime,
        endTime: endTime,
        exerciseType: exerciseType,
        durationSeconds: durationSeconds,
        intervals: intervals,
        distanceMeters: distanceMeters,
        calories: calories,
        poolLengthMeters: poolLengthMeters,
        poolLengthUnit: poolLengthUnit,
        heartRateSamples: heartRateSamples,
        averageHeartRateBpm: averageHeartRateBpm,
        maximumHeartRateBpm: maximumHeartRateBpm,
        restAnalysis: analysis,
      );

  ({int? average, int? maximum}) heartRateForLap(int index) {
    if (index < 0 || index >= intervals.length) {
      throw RangeError.index(index, intervals, 'index');
    }
    if (!hasCompleteRestAnalysis) {
      return (average: null, maximum: null);
    }
    return heartRatesByLap[index];
  }

  List<({int? average, int? maximum})> get heartRatesByLap {
    if (!hasCompleteRestAnalysis) {
      return List.filled(intervals.length, (
        average: null,
        maximum: null,
      ), growable: false);
    }
    final lapSamples = heartRateSamplesByLap;
    final calculatedHeartRates = SwimHeartRateEstimator.summarize(lapSamples);
    return List.generate(
      intervals.length,
      (index) => (
        average:
            calculatedHeartRates[index].average ??
            (heartRateSamples.isEmpty
                ? restAnalysis!.averageHeartRateByLap[index]
                : null),
        maximum:
            calculatedHeartRates[index].maximum ??
            (heartRateSamples.isEmpty
                ? restAnalysis!.maximumHeartRateByLap[index]
                : null),
      ),
      growable: false,
    );
  }

  List<HeartRateLapWindow> get heartRateSamplesByLap {
    if (!hasCompleteRestAnalysis) return const [];
    return SwimHeartRateEstimator.mapSamplesToLaps(
      startTime: startTime,
      endTime: endTime,
      lapDurationsSeconds: intervals
          .map((interval) => interval.durationSeconds)
          .toList(),
      restSecondsByLap: restAnalysis!.restSecondsByLap,
      heartRateSamples: heartRateSamples,
    );
  }

  ({List<int?> average, List<int?> maximum}) _heartRatesFor(
    List<double?> rests,
  ) {
    final lapWindows = SwimHeartRateEstimator.mapSamplesToLaps(
      startTime: startTime,
      endTime: endTime,
      lapDurationsSeconds: intervals
          .map((interval) => interval.durationSeconds)
          .toList(),
      restSecondsByLap: rests,
      heartRateSamples: heartRateSamples,
      alignActivityOnset: false,
    );
    final summaries = SwimHeartRateEstimator.summarize(lapWindows);
    return (
      average: summaries.map((summary) => summary.average).toList(),
      maximum: summaries.map((summary) => summary.maximum).toList(),
    );
  }

  int get distanceForSummaryMeters =>
      distanceMeters?.round() ?? intervals.length * (poolLengthMeters ?? 25);

  double? get restAdjustedDurationSeconds {
    final analysis = restAnalysis;
    if (analysis == null) return null;
    return analysis.restSecondsByLap.fold<double>(
      0,
      (total, seconds) => total + (seconds ?? 0),
    );
  }

  int? get displayAverageHeartRateBpm {
    if (averageHeartRateBpm != null) return averageHeartRateBpm;
    if (heartRateSamples.isEmpty) return null;
    return (heartRateSamples.fold<int>(
              0,
              (total, sample) => total + sample.beatsPerMinute,
            ) /
            heartRateSamples.length)
        .round();
  }

  int? get displayMaximumHeartRateBpm {
    if (maximumHeartRateBpm != null) return maximumHeartRateBpm;
    if (heartRateSamples.isEmpty) return null;
    return heartRateSamples
        .map((sample) => sample.beatsPerMinute)
        .reduce((first, second) => first > second ? first : second);
  }

  double get estimatedRestSeconds {
    final analyzedRest = restAdjustedDurationSeconds;
    if (analyzedRest != null) return analyzedRest;
    final intervalSeconds = intervals.fold<double>(
      0,
      (total, interval) => total + interval.durationSeconds,
    );
    return (durationSeconds - intervalSeconds)
        .clamp(0, double.infinity)
        .toDouble();
  }

  String get strokeCountSummary =>
      intervals.isEmpty ? '구간 정보 없음' : '${intervals.length}개 구간';

  SwimAnalysis analyze({
    required bool inferIm100,
    bool excludePaceOutliers = true,
    bool finSwimmingIncluded = false,
    bool longCoursePool = false,
  }) {
    final effectivePoolLength = longCoursePool ? 50 : poolLengthMeters;
    final poolLength = effectivePoolLength == 50 ? 50 : 25;
    final lines = <String>[
      if (effectivePoolLength == 25 || effectivePoolLength == 50)
        '구간(${poolLength}m)',
    ];
    for (var index = 0; index < intervals.length; index++) {
      final interval = intervals[index];
      if (interval.durationSeconds <= 0) continue;
      lines.add(
        '${index + 1} ${interval.analysisStroke} '
        '${formatDuration(interval.durationSeconds)}',
      );
      final restSeconds =
          restAnalysis != null && index < restAnalysis!.restSecondsByLap.length
          ? restAnalysis!.restSecondsByLap[index]
          : null;
      if (restSeconds != null && restSeconds > 0) {
        lines.add('휴식 ${formatDuration(restSeconds)}');
      }
    }
    return analyzeSwimText(
      lines.join('\n'),
      inferIm100: inferIm100,
      excludePaceOutliers: excludePaceOutliers,
      finSwimmingIncluded: finSwimmingIncluded,
    );
  }

  static double? _number(Object? value) =>
      value is num ? value.toDouble() : null;

  static int? _integer(Object? value) => value is num ? value.round() : null;

  static int? _poolLength(Object? value) {
    final length = _number(value)?.round();
    return length == 25 || length == 50 ? length : null;
  }
}

class SwimRestAnalysis {
  const SwimRestAnalysis({
    required this.restSecondsByLap,
    required this.recognizedLapCount,
    required this.needsReview,
    required this.averageHeartRateByLap,
    required this.maximumHeartRateByLap,
    this.manuallyReviewed = false,
    this.ocrAccuracyPercent,
  });

  factory SwimRestAnalysis.fromMap(Map<String, dynamic> data) {
    final rests = data['restSecondsByLap'];
    final recognizedLapCount = data['recognizedLapCount'];
    final averageHeartRates = data['averageHeartRateByLap'];
    final maximumHeartRates = data['maximumHeartRateByLap'];
    final accuracy = data['ocrAccuracyPercent'];
    final manuallyReviewed = data['manuallyReviewed'];
    if (rests is! List ||
        recognizedLapCount is! num ||
        data['needsReview'] is! bool ||
        averageHeartRates is! List ||
        maximumHeartRates is! List ||
        (accuracy != null && accuracy is! num) ||
        (manuallyReviewed != null && manuallyReviewed is! bool)) {
      throw const FormatException('저장된 휴식 분석 데이터 형식이 올바르지 않습니다.');
    }
    if (accuracy is num && (accuracy < 0 || accuracy > 100)) {
      throw const FormatException('저장된 OCR 일치율이 올바르지 않습니다.');
    }
    return SwimRestAnalysis(
      restSecondsByLap: _nullableNumbers(rests),
      recognizedLapCount: recognizedLapCount.toInt(),
      needsReview:
          (data['needsReview'] as bool) ||
          (accuracy is num && accuracy < 99 && manuallyReviewed != true),
      manuallyReviewed: manuallyReviewed == true,
      averageHeartRateByLap: _nullableIntegers(averageHeartRates),
      maximumHeartRateByLap: _nullableIntegers(maximumHeartRates),
      ocrAccuracyPercent: (accuracy as num?)?.toDouble(),
    );
  }

  final List<double?> restSecondsByLap;
  final int recognizedLapCount;
  final bool needsReview;
  final List<int?> averageHeartRateByLap;
  final List<int?> maximumHeartRateByLap;
  final bool manuallyReviewed;
  final double? ocrAccuracyPercent;

  Map<String, Object?> toMap() => {
    'restSecondsByLap': restSecondsByLap,
    'recognizedLapCount': recognizedLapCount,
    'needsReview': needsReview,
    'manuallyReviewed': manuallyReviewed,
    'averageHeartRateByLap': averageHeartRateByLap,
    'maximumHeartRateByLap': maximumHeartRateByLap,
    'ocrAccuracyPercent': ocrAccuracyPercent,
  };

  static List<double?> _nullableNumbers(List values) => [
    for (final value in values)
      if (value == null)
        null
      else if (value is num)
        value.toDouble()
      else
        throw const FormatException('랩별 휴식 시간 형식이 올바르지 않습니다.'),
  ];

  static List<int?> _nullableIntegers(List values) => [
    for (final value in values)
      if (value == null)
        null
      else if (value is num)
        value.round()
      else
        throw const FormatException('랩별 심박수 형식이 올바르지 않습니다.'),
  ];
}

class SwimHealthInterval {
  const SwimHealthInterval({
    required this.durationSeconds,
    required this.strokeType,
    required this.strokeCount,
  });

  factory SwimHealthInterval.fromMap(Map<String, dynamic> data) {
    final duration = data['durationSeconds'];
    final strokeCount = data['strokeCount'];
    if (duration is! num || strokeCount is! num) {
      throw const FormatException('삼성 헬스 수영 구간 데이터가 올바르지 않습니다.');
    }
    return SwimHealthInterval(
      durationSeconds: duration.toDouble(),
      strokeType: data['strokeType'] as String? ?? 'UNKNOWN',
      strokeCount: strokeCount.toInt(),
    );
  }

  final double durationSeconds;
  final String strokeType;
  final int strokeCount;

  Map<String, Object?> toMap() => {
    'durationSeconds': durationSeconds,
    'strokeType': strokeType,
    'strokeCount': strokeCount,
  };

  String get analysisStroke {
    final type = strokeType.toLowerCase().replaceAll('_', '');
    if (type.contains('butterfly') || type.contains('접영')) {
      return '접영';
    }
    if (type.contains('backstroke') || type.contains('배영')) {
      return '배영';
    }
    if (type.contains('breaststroke') || type.contains('평영')) {
      return '평영';
    }
    if (type.contains('freestyle') ||
        type.contains('free') ||
        type.contains('자유')) {
      return '자유형';
    }
    if (type.contains('medley') || type.contains('혼영')) return '혼영';
    if (type.contains('kick') || type.contains('킥')) return '킥판';
    return strokeType;
  }

  String get displayStroke => switch (analysisStroke) {
    '자유형' => '자유',
    '접영' => '접영',
    '배영' => '배영',
    '평영' => '평영',
    '혼영' => '혼영',
    '킥판' => '킥판',
    _ => '기타',
  };
}
