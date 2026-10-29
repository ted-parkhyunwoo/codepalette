import 'dart:math' as math;

import 'package:flutter/material.dart';

import '../swim_data.dart';

Color _ink(BuildContext context) =>
    Theme.of(context).colorScheme.onSurface;
Color _muted(BuildContext context) =>
    Theme.of(context).colorScheme.onSurfaceVariant;
Color _tertiary(BuildContext context) =>
    Theme.of(context).colorScheme.tertiary;
Color _excludedRecordColor(BuildContext context) => Colors.red;
Color _fastestPaceColor(BuildContext context) => Colors.green;

/// Shows every recognized lap in a horizontally scrollable, aligned table.
class AllRecordsPage extends StatelessWidget {
  const AllRecordsPage({required this.analysis, super.key});

  final SwimAnalysis analysis;

  @override
  Widget build(BuildContext context) {
    final records = analysis.records;
    final recordTimes =
        records.map((record) => record.timeSeconds).toList();
    final excludedRecords =
        records.where((record) => record.paceExcluded).toList();
    final strokeSummaries = analysis.strokeSummaries.toList()
      ..sort((first, second) =>
          second.lapCount.compareTo(first.lapCount));
    final strokeColorIndices = {
      for (var index = 0; index < strokeSummaries.length; index++)
        strokeSummaries[index].stroke: index,
    };
    final fastestPaceByStroke = <String, double>{};
    for (final record
        in records.where((record) => !record.paceExcluded)) {
      if (record.distanceMeters <= 0) continue;
      final pace = record.timeSeconds * 100 / record.distanceMeters;
      final current = fastestPaceByStroke[record.stroke];
      if (current == null || pace < current) {
        fastestPaceByStroke[record.stroke] = pace;
      }
    }
    final fastestRecordIndices = <int>{};
    for (var index = 0; index < records.length; index++) {
      final record = records[index];
      if (record.paceExcluded || record.distanceMeters <= 0) continue;
      final pace = record.timeSeconds * 100 / record.distanceMeters;
      if (pace == fastestPaceByStroke[record.stroke]) {
        fastestRecordIndices.add(index);
      }
    }
    return _ResultScaffold(
      title: '모든 기록',
      summary: '${analysis.poolLengthMeters}m 풀 · '
          '총 ${records.length}랩 · 총 ${analysis.totalDistanceMeters}m',
      child: records.isEmpty
          ? const _EmptyResult(message: '표시할 수영 기록이 없습니다.')
          : Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                if (excludedRecords.isNotEmpty)
                  Padding(
                    padding: const EdgeInsets.only(bottom: 8),
                    child: Text.rich(
                      TextSpan(
                        style: TextStyle(
                          color: _muted(context),
                          fontSize: 12,
                        ),
                        children: [
                          const TextSpan(
                            text: '빨간색',
                            style: TextStyle(
                              color: Colors.red,
                              fontWeight: FontWeight.w700,
                            ),
                          ),
                          const TextSpan(
                            text: ' 기록은 페이스 계산에서 제외됩니다.',
                          ),
                        ],
                      ),
                    ),
                  ),
                if (fastestPaceByStroke.isNotEmpty)
                  Padding(
                    padding: const EdgeInsets.only(bottom: 6),
                    child: Text.rich(
                      TextSpan(
                        style: TextStyle(
                          color: _muted(context),
                          fontSize: 12,
                        ),
                        children: [
                          const TextSpan(
                            text: '초록색',
                            style: TextStyle(
                              color: Colors.green,
                              fontWeight: FontWeight.w700,
                            ),
                          ),
                          const TextSpan(
                            text: ' 기록은 영법별 최고 기록입니다.',
                          ),
                        ],
                      ),
                    ),
                  ),
                _ResultTable(
                  cellTextColors: List.generate(
                    records.length,
                    (index) {
                      final record = records[index];
                      return [
                        null,
                        _strokeColor(
                          context,
                          record.stroke,
                          strokeColorIndices[record.stroke] ?? 0,
                        ),
                        fastestRecordIndices.contains(index)
                            ? _fastestPaceColor(context)
                            : record.paceExcluded
                                ? _excludedRecordColor(context)
                                : null,
                        null,
                        null,
                      ];
                    },
                  ),
                  horizontalCellPadding: 1,
                  columnWidthPadding: 0,
                  columnWidthAdjustments: const [0, 50, 30, 30, 30],
                  headers: const ['랩', '영법', '기록', '100m 페이스', '휴식'],
                  rows: records
                      .map(
                        (record) => [
                          '${record.lapNumber}',
                          record.stroke,
                          _formatTime(
                              record.timeSeconds, recordTimes),
                          record.distanceMeters <= 0
                              ? '—'
                              : formatDuration(
                                  record.timeSeconds *
                                      100 /
                                      record.distanceMeters,
                                ),
                          record.restCount == 0
                              ? '—'
                              : formatDuration(record.restSeconds),
                        ],
                      )
                      .toList(),
                ),
              ],
            ),
    );
  }
}

/// Presents detected individual medley sequences and their three transitions.
class ImEvaluationPage extends StatelessWidget {
  const ImEvaluationPage({required this.analysis, super.key});

  final SwimAnalysis analysis;

  @override
  Widget build(BuildContext context) {
    final sessions = analysis.imRecords;
    final distance = analysis.poolLengthMeters * 4;
    final sessionTimes =
        sessions.map((record) => record.timeSeconds).toList();
    final splitTimes =
        sessions.expand((record) => record.splitsSeconds).toList();
    final scheme = Theme.of(context).colorScheme;
    final chartSessions = sessions.indexed.toList()
      ..sort((first, second) =>
          first.$2.timeSeconds.compareTo(second.$2.timeSeconds));
    return _ResultScaffold(
      title: 'IM $distance 찾기',
      summary: '${sessions.length}개 세션을 찾았습니다 \n추정구간은 자배평자를 IM100으로 처리합니다',
      child: sessions.isEmpty
          ? _EmptyResult(message: '연속된 IM $distance 기록이 없습니다.')
          : Column(
              children: [
                _ComparisonChart(
                  title: '세션별 기록 (빠른순 정렬)',
                  values: chartSessions
                      .map((entry) => entry.$2.timeSeconds)
                      .toList(),
                  labels: chartSessions
                      .map((entry) => '${entry.$1 + 1}')
                      .toList(),
                  suffix: '초',
                  barColors: chartSessions
                      .map((session) => session.$2.inferred
                          ? scheme.tertiary
                          : scheme.primary)
                      .toList(),
                  legendItems: [
                    ('정상 인식', scheme.primary),
                    ('추정 구간', scheme.tertiary),
                  ],
                ),
                const SizedBox(height: 12),
                _ResultTable(
                  leadingCellColors: sessions
                      .map((session) =>
                          session.inferred ? scheme.tertiary : null)
                      .toList(),
                  columnWidthPadding: 0,
                  horizontalCellPadding: 4,
                  columnWidthAdjustments: const [35, 25, 10, 10, 15, 35],
                  headers: const [
                    '세션',
                    '기록',
                    '페이스/100m',
                    '영법별 기록 (접/배/평/자)',
                    '랩',
                    '구간 휴식'
                  ],
                  rows: sessions.indexed
                      .map(
                        (entry) => [
                          '${entry.$1 + 1}'
                              '${entry.$2.inferred ? ' (추정)' : ''}',
                          _formatTime(
                              entry.$2.timeSeconds, sessionTimes),
                          entry.$2.paceDistanceMeters == 0
                              ? '—'
                              : formatDuration(
                                  entry.$2.paceTimeSeconds! *
                                      100 /
                                      entry.$2.paceDistanceMeters!,
                                ),
                          entry.$2.splitsSeconds
                              .map((time) =>
                                  _formatTime(time, splitTimes))
                              .join(' / '),
                          '${entry.$2.lapNumber}–${entry.$2.lapNumber + entry.$2.lapCount - 1}',
                          _formatImRestIntervals(analysis, entry.$2),
                        ],
                      )
                      .toList(),
                ),
              ],
            ),
    );
  }
}

/// Summarizes lap counts, distance, pace, and rests for each stroke.
class StrokeEvaluationPage extends StatelessWidget {
  const StrokeEvaluationPage({required this.analysis, super.key});

  final SwimAnalysis analysis;

  @override
  Widget build(BuildContext context) {
    final summaries = analysis.strokeSummaries.toList()
      ..sort((first, second) =>
          second.lapCount.compareTo(first.lapCount));
    final paceSummaries = summaries.toList()
      ..sort((first, second) {
        final paceOrder = first.paceSecondsPer100m
            .compareTo(second.paceSecondsPer100m);
        return paceOrder != 0
            ? paceOrder
            : second.lapCount.compareTo(first.lapCount);
      });
    final strokeColors = {
      for (var index = 0; index < summaries.length; index++)
        summaries[index].stroke:
            _strokeColor(context, summaries[index].stroke, index),
    };
    final tableSummaries = paceSummaries;
    final excludedLaps = analysis.records
        .where((record) => record.paceExcluded)
        .map((record) => record.lapNumber)
        .toList()
      ..sort();
    return _ResultScaffold(
      title: '영법별 평가',
      summary: '영법별 기록과 휴식 요약',
      child: summaries.isEmpty
          ? const _EmptyResult(message: '평가할 수영 기록이 없습니다.')
          : Column(
              children: [
                _ComparisonChart(
                  title: '영법별 페이스',
                  values: paceSummaries
                      .map((summary) => summary.paceSecondsPer100m)
                      .toList(),
                  labels: paceSummaries
                      .map((summary) => summary.stroke)
                      .toList(),
                  suffix: '초',
                  barColors: paceSummaries
                      .map((summary) => strokeColors[summary.stroke]!)
                      .toList(),
                ),
                const SizedBox(height: 12),
                _ResultTable(
                  leadingCellColors: [
                    null,
                    ...tableSummaries.map(
                      (summary) => strokeColors[summary.stroke],
                    ),
                  ],
                  horizontalCellPadding: 1,
                  columnWidthPadding: 0,
                  columnWidthAdjustments: const [0, 0, 20, 0, 0, 20],
                  headers: const [
                    '영법',
                    '횟수',
                    '거리',
                    '총 시간',
                    '페이스',
                    '휴식',
                  ],
                  rows: [
                    _totalRow(summaries),
                    ...tableSummaries.map(
                      (summary) => [
                        summary.stroke,
                        '${summary.lapCount}',
                        '${summary.totalDistanceMeters}m',
                        formatDuration(summary.totalTimeSeconds),
                        summary.paceDistanceMeters == 0
                            ? '—'
                            : formatDuration(
                                summary.paceSecondsPer100m),
                        '${formatDuration(summary.totalRestSeconds)}'
                            ' (${summary.restCount}회)',
                      ],
                    ),
                  ],
                ),
                if (excludedLaps.isNotEmpty) ...[
                  const SizedBox(height: 10),
                  Align(
                    alignment: Alignment.centerLeft,
                    child: Text(
                      '평균 페이스에서 ${excludedLaps.length}개 랩 '
                      '(${excludedLaps.map((lap) => '$lap랩').join(', ')})을 '
                      '제외했습니다. \n전체 기록에는 원본을 유지합니다.',
                      style: TextStyle(
                        color: _muted(context),
                        fontSize: 12,
                        height: 1.4,
                      ),
                    ),
                  ),
                ],
              ],
            ),
    );
  }

  List<String> _totalRow(List<StrokeSummary> summaries) {
    final laps = summaries.fold<int>(
        0, (total, item) => total + item.lapCount);
    final distance = summaries.fold<int>(
      0,
      (total, item) => total + item.totalDistanceMeters,
    );
    final time = summaries.fold<double>(
      0,
      (total, item) => total + item.totalTimeSeconds,
    );
    final rests = summaries.fold<int>(
        0, (total, item) => total + item.restCount);
    final restTime = summaries.fold<double>(
      0,
      (total, item) => total + item.totalRestSeconds,
    );
    final paceTime = summaries.fold<double>(
      0,
      (total, item) => total + item.paceTimeSeconds,
    );
    final paceDistance = summaries.fold<int>(
      0,
      (total, item) => total + item.paceDistanceMeters,
    );
    return [
      '전체',
      '$laps',
      '${distance}m',
      formatDuration(time),
      paceDistance == 0
          ? '—'
          : formatDuration(paceTime * 100 / paceDistance),
      '${formatDuration(restTime)}($rests회)',
    ];
  }
}

/// Builds the consistent app bar and scrollable page body used by result views.
class _ResultScaffold extends StatelessWidget {
  const _ResultScaffold({
    required this.title,
    required this.summary,
    required this.child,
  });

  final String title;
  final String summary;
  final Widget child;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(title,
            style: const TextStyle(fontWeight: FontWeight.w700)),
      ),
      body: ListView(
        padding: const EdgeInsets.fromLTRB(18, 8, 18, 28),
        children: [
          Text(summary,
              style: TextStyle(color: _muted(context), fontSize: 14)),
          const SizedBox(height: 12),
          child,
          const SizedBox(height: 8),
        ],
      ),
    );
  }
}

/// Formats IM rest values only for butterfly-backstroke, backstroke-breaststroke,
/// and breaststroke-freestyle transitions.
String _formatImRestIntervals(
    SwimAnalysis analysis, SwimRecord imRecord) {
  const labels = ['접·배', '배·평', '평·자'];
  final startIndex = analysis.records.indexWhere(
    (record) => record.lapNumber == imRecord.lapNumber,
  );
  if (startIndex < 0) return '—';

  final intervals = <String>[];
  for (var index = 0; index < labels.length; index++) {
    final lapIndex = startIndex + index;
    if (lapIndex >= analysis.records.length) break;
    final lap = analysis.records[lapIndex];
    if (lap.restCount == 0 && lap.restSeconds == 0) continue;
    intervals
        .add('${labels[index]} ${formatDuration(lap.restSeconds)}');
  }
  return intervals.isEmpty ? '—' : intervals.join(' · ');
}

String _formatTime(double seconds, List<double> values) {
  return values.every((value) => value < 60)
      ? seconds.toStringAsFixed(1)
      : formatDuration(seconds);
}

Color _strokeColor(BuildContext context, String stroke, int index) {
  final isDark = Theme.of(context).brightness == Brightness.dark;
  if (stroke == '자유') {
    return isDark ? Colors.tealAccent : Colors.teal.shade800;
  }
  if (stroke == '배영') {
    return isDark ? Colors.lightBlueAccent : Colors.blue.shade700;
  }
  if (stroke == '평영') {
    return isDark ? Colors.amberAccent : Colors.orange.shade800;
  }
  if (stroke == '접영') {
    return isDark ? Colors.purpleAccent : Colors.deepPurple.shade600;
  }
  final colors = [
    isDark ? Colors.tealAccent : Colors.teal.shade800,
    isDark ? Colors.lightBlueAccent : Colors.blue.shade700,
    isDark ? Colors.amberAccent : Colors.orange.shade800,
    isDark ? Colors.purpleAccent : Colors.deepPurple.shade600,
  ];
  return colors[index % colors.length];
}

Color _categoryColor(BuildContext context, int index) {
  final scheme = Theme.of(context).colorScheme;
  final colors = [
    scheme.primary,
    scheme.tertiary,
    scheme.secondary,
    scheme.inversePrimary,
  ];
  return colors[index % colors.length];
}

/// Renders a compact table with centered values and horizontal scrolling.
class _ResultTable extends StatefulWidget {
  const _ResultTable({
    required this.headers,
    required this.rows,
    this.leadingCellColors,
    this.cellTextColors,
    this.horizontalCellPadding = 5,
    this.columnWidthPadding = 20,
    this.columnWidthAdjustments = const [],
  });

  final List<String> headers;
  final List<List<String>> rows;
  final List<Color?>? leadingCellColors;
  final List<List<Color?>>? cellTextColors;
  final double horizontalCellPadding;
  final double columnWidthPadding;
  final List<double> columnWidthAdjustments;

  @override
  State<_ResultTable> createState() => _ResultTableState();
}

class _ResultTableState extends State<_ResultTable> {
  final _scrollController = ScrollController();

  @override
  void dispose() {
    _scrollController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final scheme = Theme.of(context).colorScheme;
    final naturalWidths =
        List.generate(widget.headers.length, (column) {
      final longestText = widget.rows.fold<int>(
        widget.headers[column].length,
        (longest, row) => math.max(longest, row[column].length),
      );
      final adjustment = column < widget.columnWidthAdjustments.length
          ? widget.columnWidthAdjustments[column]
          : 0.0;
      return (longestText * 7.3 +
              widget.columnWidthPadding +
              adjustment)
          .clamp(48.0, 260.0);
    });
    final minTableWidth =
        math.max(0, MediaQuery.sizeOf(context).width - 36);
    final naturalTableWidth = naturalWidths.fold<double>(
        0, (total, width) => total + width);
    final extraWidth =
        math.max(0, minTableWidth - naturalTableWidth) /
            naturalWidths.length;
    final columnWidths =
        naturalWidths.map((width) => width + extraWidth).toList();
    return Card(
      clipBehavior: Clip.antiAlias,
      margin: EdgeInsets.zero,
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.stretch,
        children: [
          Scrollbar(
            controller: _scrollController,
            thumbVisibility: true,
            trackVisibility: true,
            child: SingleChildScrollView(
              controller: _scrollController,
              scrollDirection: Axis.horizontal,
              child: SizedBox(
                width: columnWidths.fold<double>(
                    0, (total, width) => total + width),
                child: Column(
                  children: [
                    _TableRow(
                      values: widget.headers,
                      columnWidths: columnWidths,
                      background: scheme.primaryContainer,
                      foreground: scheme.onPrimaryContainer,
                      isHeader: true,
                    ),
                    for (var index = 0;
                        index < widget.rows.length;
                        index++)
                      _TableRow(
                        values: widget.rows[index],
                        columnWidths: columnWidths,
                        background: widget.rows[index].first == '전체'
                            ? scheme.tertiaryContainer
                            : scheme.surface,
                        foreground: widget.rows[index].first == '전체'
                            ? scheme.onTertiaryContainer
                            : _ink(context),
                        isEmphasized:
                            widget.rows[index].first == '전체',
                        leadingCellColor: widget.leadingCellColors !=
                                    null &&
                                index <
                                    widget.leadingCellColors!.length
                            ? widget.leadingCellColors![index]
                            : null,
                        cellTextColors: widget.cellTextColors !=
                                    null &&
                                index < widget.cellTextColors!.length
                            ? widget.cellTextColors![index]
                            : null,
                        horizontalPadding:
                            widget.horizontalCellPadding,
                      ),
                    const SizedBox(height: 28),
                  ],
                ),
              ),
            ),
          ),
        ],
      ),
    );
  }
}

/// Lays out one equally spaced row in the results table.
class _TableRow extends StatelessWidget {
  const _TableRow({
    required this.values,
    required this.columnWidths,
    required this.background,
    required this.foreground,
    this.isHeader = false,
    this.isEmphasized = false,
    this.leadingCellColor,
    this.cellTextColors,
    this.horizontalPadding = 5,
  });

  final List<String> values;
  final List<double> columnWidths;
  final Color background;
  final Color foreground;
  final bool isHeader;
  final bool isEmphasized;
  final Color? leadingCellColor;
  final List<Color?>? cellTextColors;
  final double horizontalPadding;

  @override
  Widget build(BuildContext context) {
    return Container(
      constraints: const BoxConstraints(minHeight: 36),
      color: background,
      child: Row(
        children: List.generate(values.length, (index) {
          return SizedBox(
            width: columnWidths[index],
            child: Padding(
              padding: EdgeInsets.symmetric(
                horizontal: horizontalPadding,
                vertical: 4,
              ),
              child: Text(
                values[index],
                textAlign: TextAlign.center,
                maxLines: 3,
                overflow: TextOverflow.ellipsis,
                style: TextStyle(
                  color: (cellTextColors != null &&
                              index < cellTextColors!.length
                          ? cellTextColors![index]
                          : null) ??
                      (index == 0 && !isHeader
                          ? leadingCellColor ?? foreground
                          : foreground),
                  fontSize: isHeader ? 12 : 13,
                  fontWeight: isHeader || isEmphasized
                      ? FontWeight.w700
                      : FontWeight.w500,
                ),
              ),
            ),
          );
        }),
      ),
    );
  }
}

/// Shows an empty-state card when no rows can be presented.
class _EmptyResult extends StatelessWidget {
  const _EmptyResult({required this.message});

  final String message;

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding:
          const EdgeInsets.symmetric(horizontal: 12, vertical: 30),
      child: Column(
        children: [
          Icon(Icons.search_off_rounded,
              color: _tertiary(context), size: 34),
          const SizedBox(height: 10),
          Text(message, textAlign: TextAlign.center),
        ],
      ),
    );
  }
}

/// Compares per-session or per-stroke values with a compact bar chart.
class _ComparisonChart extends StatelessWidget {
  const _ComparisonChart({
    required this.title,
    required this.values,
    required this.labels,
    required this.suffix,
    this.barColors,
    this.legendItems = const [],
  });

  final String title;
  final List<double> values;
  final List<String> labels;
  final String suffix;
  final List<Color>? barColors;
  final List<(String, Color)> legendItems;

  @override
  Widget build(BuildContext context) {
    final maximum = values.fold<double>(
        0, (max, value) => value > max ? value : max);
    return Card(
      margin: EdgeInsets.zero,
      child: Padding(
        padding: const EdgeInsets.all(16),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text(title,
                style: TextStyle(
                  color: _ink(context),
                  fontWeight: FontWeight.w700,
                )),
            const SizedBox(height: 16),
            SizedBox(
              height: 132,
              child: Row(
                crossAxisAlignment: CrossAxisAlignment.end,
                children: List.generate(values.length, (index) {
                  final ratio =
                      maximum == 0 ? 0.0 : values[index] / maximum;
                  return Expanded(
                    child: Padding(
                      padding:
                          const EdgeInsets.symmetric(horizontal: 5),
                      child: Column(
                        mainAxisAlignment: MainAxisAlignment.end,
                        children: [
                          Text(
                            values.every((value) => value < 60)
                                ? '${values[index].toStringAsFixed(1)}$suffix'
                                : formatDuration(values[index]),
                            style: TextStyle(
                              color: _muted(context),
                              fontSize: 9,
                            ),
                          ),
                          const SizedBox(height: 5),
                          Container(
                            height: 78 * ratio.clamp(0.08, 1),
                            decoration: BoxDecoration(
                              color: barColors?[index] ??
                                  _categoryColor(context, index),
                              borderRadius:
                                  const BorderRadius.vertical(
                                top: Radius.circular(8),
                              ),
                            ),
                          ),
                          const SizedBox(height: 6),
                          Text(
                            labels[index],
                            maxLines: 1,
                            overflow: TextOverflow.ellipsis,
                            textAlign: TextAlign.center,
                            style: TextStyle(
                              color:
                                  barColors?[index] ?? _ink(context),
                              fontSize: 10,
                              fontWeight: FontWeight.w600,
                            ),
                          ),
                        ],
                      ),
                    ),
                  );
                }),
              ),
            ),
            if (legendItems.isNotEmpty) ...[
              const SizedBox(height: 12),
              Align(
                alignment: Alignment.center,
                child: Wrap(
                  alignment: WrapAlignment.center,
                  spacing: 16,
                  runSpacing: 8,
                  children: legendItems
                      .map(
                        (item) => Row(
                          mainAxisSize: MainAxisSize.min,
                          children: [
                            Container(
                              width: 9,
                              height: 9,
                              decoration: BoxDecoration(
                                color: item.$2,
                                borderRadius:
                                    BorderRadius.circular(3),
                              ),
                            ),
                            const SizedBox(width: 5),
                            Text(
                              item.$1,
                              style: TextStyle(
                                color: item.$2,
                                fontSize: 10,
                                fontWeight: FontWeight.w700,
                              ),
                            ),
                          ],
                        ),
                      )
                      .toList(),
                ),
              ),
            ],
          ],
        ),
      ),
    );
  }
}
