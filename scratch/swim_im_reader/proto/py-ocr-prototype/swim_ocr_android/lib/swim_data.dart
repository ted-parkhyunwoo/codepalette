/// One parsed swim lap or a derived multi-lap medley.
class SwimRecord {
  SwimRecord({
    required this.lapNumber,
    required this.stroke,
    required this.timeSeconds,
    required this.distanceMeters,
    this.restSeconds = 0,
    this.restCount = 0,
    this.lapCount = 1,
    this.splitsSeconds = const [],
    this.inferred = false,
    this.paceExcluded = false,
    this.paceTimeSeconds,
    this.paceDistanceMeters,
    this.excludedLapNumbers = const [],
    this.transitionRestSeconds = const [],
  });

  final int lapNumber;
  final String stroke;
  final double timeSeconds;
  final int distanceMeters;
  double restSeconds;
  int restCount;
  final int lapCount;
  final List<double> splitsSeconds;
  final bool inferred;
  bool paceExcluded;
  final double? paceTimeSeconds;
  final int? paceDistanceMeters;
  final List<int> excludedLapNumbers;
  final List<double?> transitionRestSeconds;
}

/// Aggregated time, distance, pace, and rest metrics for one stroke.
class StrokeSummary {
  const StrokeSummary({
    required this.stroke,
    required this.lapCount,
    required this.totalTimeSeconds,
    required this.totalDistanceMeters,
    required this.paceSecondsPer100m,
    required this.restCount,
    required this.totalRestSeconds,
    required this.paceTimeSeconds,
    required this.paceDistanceMeters,
    required this.excludedLapNumbers,
  });

  final String stroke;
  final int lapCount;
  final double totalTimeSeconds;
  final int totalDistanceMeters;
  final double paceSecondsPer100m;
  final int restCount;
  final double totalRestSeconds;
  final double paceTimeSeconds;
  final int paceDistanceMeters;
  final List<int> excludedLapNumbers;
}

/// All transient records and summary metrics derived from one uploaded image.
class SwimAnalysis {
  const SwimAnalysis({
    required this.records,
    required this.imRecords,
    required this.strokeSummaries,
    required this.recognizedLines,
    required this.poolLengthMeters,
    required this.totalDistanceMeters,
  });

  final List<SwimRecord> records;
  final List<SwimRecord> imRecords;
  final List<StrokeSummary> strokeSummaries;
  final List<String> recognizedLines;
  final int poolLengthMeters;
  final int totalDistanceMeters;
}

/// Parses OCR text, detects pool length, and computes activity summaries.
///
/// The returned analysis is held in memory only; it is not persisted.
// Android-only analysis controls; keep Python and C++ prototype behavior unchanged.
SwimAnalysis analyzeSwimText(
  String text, {
  int? poolLengthMeters,
  bool inferIm100 = true,
  bool excludePaceOutliers = true,
  bool finSwimmingIncluded = false,
}) {
  final lines = text.split(RegExp(r'\r?\n'));
  final resolvedPoolLength = poolLengthMeters ?? _detectPoolLength(lines);
  final records = parseSwimRecords(
    lines,
    poolLengthMeters: resolvedPoolLength,
  );
  markPaceOutliers(
    records,
    excludeOutliers: excludePaceOutliers,
    finSwimmingIncluded: finSwimmingIncluded,
  );
  return SwimAnalysis(
    records: records,
    imRecords: findImRecords(records, inferIm100: inferIm100),
    strokeSummaries: summarizeByStroke(records),
    recognizedLines: text
        .split(RegExp(r'\r?\n'))
        .map((line) => line.trim())
        .where((line) => line.isNotEmpty)
        .toList(),
    poolLengthMeters: resolvedPoolLength,
    totalDistanceMeters: records.fold<int>(
      0,
      (total, record) => total + record.distanceMeters,
    ),
  );
}

/// Converts recognized lap and rest lines into ordered swim records.
List<SwimRecord> parseSwimRecords(
  List<String> lines, {
  int poolLengthMeters = 25,
}) {
  final records = <SwimRecord>[];
  SwimRecord? lastRecord;
  final seenLapNumbers = <int>{};
  final timePattern = RegExp(r'(\d+):(\d{2}(?:\.\d+)?)');
  final lapPattern = RegExp(r'^\s*(\d+)');

  for (var lineIndex = 0; lineIndex < lines.length; lineIndex++) {
    final line = lines[lineIndex].trim();
    if (line.isEmpty) continue;

    final lapMatch = lapPattern.firstMatch(line);
    if (lapMatch != null) {
      final lapNumber = int.parse(lapMatch.group(1)!);
      final remainingLine = line.substring(lapMatch.end);
      final timeMatch = timePattern.firstMatch(remainingLine);
      if (timeMatch == null) continue;
      if (!seenLapNumbers.add(lapNumber)) continue;
      final strokeText = remainingLine.substring(0, timeMatch.start).trim();
      final seconds = _durationFromMatch(timeMatch);
      final record = SwimRecord(
        lapNumber: lapNumber,
        stroke: _normalizeStroke(strokeText),
        timeSeconds: seconds,
        distanceMeters: poolLengthMeters,
      );
      records.add(record);
      lastRecord = record;
      continue;
    }

    final timeMatch = timePattern.firstMatch(line);
    if (timeMatch != null && lastRecord != null) {
      final strokeText = line.substring(0, timeMatch.start).trim();
      final stroke = _normalizeStroke(strokeText);
      if (stroke != '기타') {
        // Android ML Kit may omit a lap number while still recognizing its stroke and time.
        final lapNumber = lastRecord.lapNumber + 1;
        final nextLapNumber = _nextNumberedLapNumber(
          lines,
          lineIndex + 1,
          lapPattern,
          timePattern,
        );
        if ((nextLapNumber == null || nextLapNumber > lapNumber) &&
            seenLapNumbers.add(lapNumber)) {
          final record = SwimRecord(
            lapNumber: lapNumber,
            stroke: stroke,
            timeSeconds: _durationFromMatch(timeMatch),
            distanceMeters: poolLengthMeters,
          );
          records.add(record);
          lastRecord = record;
        }
        continue;
      } else {
        lastRecord
          ..restSeconds = _durationFromMatch(timeMatch)
          ..restCount = 1;
      }
    }
  }
  return records;
}

int? _nextNumberedLapNumber(
  List<String> lines,
  int startIndex,
  RegExp lapPattern,
  RegExp timePattern,
) {
  for (final line in lines.skip(startIndex)) {
    final trimmed = line.trim();
    final lapMatch = lapPattern.firstMatch(trimmed);
    if (lapMatch == null ||
        !timePattern.hasMatch(trimmed.substring(lapMatch.end))) {
      continue;
    }
    return int.parse(lapMatch.group(1)!);
  }
  return null;
}

/// Excludes laps over the configured multiple of a trimmed median 100m pace.
void markPaceOutliers(
  List<SwimRecord> records, {
  bool excludeOutliers = true,
  bool finSwimmingIncluded = false,
}) {
  if (!excludeOutliers) {
    for (final record in records) {
      record.paceExcluded = false;
    }
    return;
  }

  final paces = records
      .map(
        (record) => record.distanceMeters > 0
            ? record.timeSeconds * 100 / record.distanceMeters
            : 0.0,
      )
      .toList();
  final validPaces = paces.where((pace) => pace > 0).toList()..sort();
  final trimCount = validPaces.length >= 20
      ? 3
      : validPaces.length >= 12
          ? 2
          : 0;
  final trimmedPaces = trimCount == 0
      ? validPaces
      : validPaces.sublist(trimCount, validPaces.length - trimCount);
  if (trimmedPaces.isEmpty) return;

  final middle = trimmedPaces.length ~/ 2;
  final median = trimmedPaces.length.isOdd
      ? trimmedPaces[middle]
      : (trimmedPaces[middle - 1] + trimmedPaces[middle]) / 2;
  final threshold = median * (finSwimmingIncluded ? 2.5 : 1.7);
  for (var index = 0; index < records.length; index++) {
    records[index].paceExcluded = paces[index] > 0 && paces[index] > threshold;
  }
}

/// Reads the pool length from a Samsung Health `구간(25m/50m)` heading.
int _detectPoolLength(List<String> lines) {
  final header = RegExp(r'구간\s*\(\s*(25|50)\s*m\s*\)', caseSensitive: false);
  for (final line in lines) {
    final match = header.firstMatch(line.replaceAll(RegExp(r'\s+'), ' '));
    if (match != null) return int.parse(match.group(1)!);
  }
  return 25;
}

/// Finds consecutive butterfly, backstroke, breaststroke, and freestyle sets.
List<SwimRecord> findImRecords(
  List<SwimRecord> records, {
  bool inferIm100 = true,
}) {
  const expectedStrokes = ['접영', '배영', '평영', '자유'];
  const inferredStrokes = ['자유', '배영', '평영', '자유'];
  final result = <SwimRecord>[];

  for (var start = 0;
      start <= records.length - expectedStrokes.length;
      start++) {
    final laps = records.sublist(start, start + expectedStrokes.length);
    final hasExpectedStrokes = List.generate(
      expectedStrokes.length,
      (index) => laps[index].stroke == expectedStrokes[index],
    ).every((matches) => matches);
    final hasInferredStrokes = List.generate(
      inferredStrokes.length,
      (index) => laps[index].stroke == inferredStrokes[index],
    ).every((matches) => matches);
    final hasConsecutiveLapNumbers = List.generate(
      laps.length - 1,
      (index) => laps[index].lapNumber + 1 == laps[index + 1].lapNumber,
    ).every((matches) => matches);

    if ((!hasExpectedStrokes && (!inferIm100 || !hasInferredStrokes)) ||
        !hasConsecutiveLapNumbers) {
      continue;
    }
    result.add(
      SwimRecord(
        lapNumber: laps.first.lapNumber,
        stroke: 'IM',
        timeSeconds: laps.fold(0, (total, lap) => total + lap.timeSeconds),
        restSeconds: laps
            .take(laps.length - 1)
            .fold(0, (total, lap) => total + lap.restSeconds),
        distanceMeters: laps.fold(
          0,
          (total, lap) => total + lap.distanceMeters,
        ),
        restCount: laps
            .take(laps.length - 1)
            .fold(0, (total, lap) => total + lap.restCount),
        lapCount: laps.length,
        splitsSeconds: laps.map((lap) => lap.timeSeconds).toList(),
        inferred: hasInferredStrokes,
        paceTimeSeconds: laps
            .where((lap) => !lap.paceExcluded)
            .fold<double>(0, (total, lap) => total + lap.timeSeconds),
        paceDistanceMeters: laps
            .where((lap) => !lap.paceExcluded)
            .fold<int>(0, (total, lap) => total + lap.distanceMeters),
        excludedLapNumbers: laps
            .where((lap) => lap.paceExcluded)
            .map((lap) => lap.lapNumber)
            .toList(),
        transitionRestSeconds: List.generate(laps.length - 1, (index) {
          final lap = laps[index];
          return lap.restCount > 0 || lap.restSeconds > 0
              ? lap.restSeconds
              : null;
        }),
      ),
    );
  }
  return result;
}

/// Aggregates records by stroke to calculate distance, pace, time, and rests.
List<StrokeSummary> summarizeByStroke(List<SwimRecord> records) {
  final grouped = <String, List<SwimRecord>>{};
  for (final record in records) {
    grouped.putIfAbsent(record.stroke, () => []).add(record);
  }

  return grouped.entries.map((entry) {
    final laps = entry.value;
    final time = laps.fold<double>(0, (total, lap) => total + lap.timeSeconds);
    final distance = laps.fold<int>(
      0,
      (total, lap) => total + lap.distanceMeters,
    );
    final restCount = laps.fold<int>(0, (total, lap) {
      return total +
          ((lap.restCount > 0 || lap.restSeconds > 0)
              ? (lap.restCount == 0 ? 1 : lap.restCount)
              : 0);
    });
    final restTime = laps.fold<double>(
      0,
      (total, lap) => total + lap.restSeconds,
    );
    final paceLaps = laps.where((lap) => !lap.paceExcluded);
    final paceTime = paceLaps.fold<double>(
      0,
      (total, lap) => total + lap.timeSeconds,
    );
    final paceDistance = paceLaps.fold<int>(
      0,
      (total, lap) => total + lap.distanceMeters,
    );
    return StrokeSummary(
      stroke: entry.key,
      lapCount: laps.fold(0, (total, lap) => total + lap.lapCount),
      totalTimeSeconds: time,
      totalDistanceMeters: distance,
      paceSecondsPer100m: paceDistance == 0 ? 0 : paceTime * 100 / paceDistance,
      restCount: restCount,
      totalRestSeconds: restTime,
      paceTimeSeconds: paceTime,
      paceDistanceMeters: paceDistance,
      excludedLapNumbers: laps
          .where((lap) => lap.paceExcluded)
          .map((lap) => lap.lapNumber)
          .toList(),
    );
  }).toList();
}

/// Formats seconds as minutes and tenths for consistent result display.
String formatDuration(double seconds) {
  final wholeSeconds = seconds.floor();
  final minutes = wholeSeconds ~/ 60;
  final remainder = seconds - minutes * 60;
  return '$minutes:${remainder.toStringAsFixed(1).padLeft(4, '0')}';
}

String _normalizeStroke(String text) {
  final compact = text.replaceAll(RegExp(r'\s+'), '');
  if (compact.startsWith('자')) return '자유';
  if (compact.startsWith('접')) return '접영';
  if (compact.startsWith('배') || compact.startsWith('H')) return '배영';
  if (compact.startsWith('평')) return '평영';
  if (compact.startsWith('킥')) return '킥판';
  if (compact.startsWith('혼')) return '혼영';
  return '기타';
}

double _durationFromMatch(RegExpMatch match) {
  return int.parse(match.group(1)!) * 60 + double.parse(match.group(2)!);
}
