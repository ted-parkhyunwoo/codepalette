import 'dart:math' as math;

import 'package:flutter/material.dart';

import '../swim_data.dart';

Color _ink(BuildContext context) => Theme.of(context).colorScheme.onSurface;
Color _muted(BuildContext context) =>
    Theme.of(context).colorScheme.onSurfaceVariant;
Color _accent(BuildContext context) => Theme.of(context).colorScheme.primary;
Color _tertiary(BuildContext context) => Theme.of(context).colorScheme.tertiary;

/// Shows every recognized lap in a horizontally scrollable, aligned table.
class AllRecordsPage extends StatelessWidget {
  const AllRecordsPage({required this.analysis, super.key});

  final SwimAnalysis analysis;

  @override
  Widget build(BuildContext context) {
    final records = analysis.records;
    return _ResultScaffold(
      title: '전체 기록',
      summary: '${records.length}랩 · ${analysis.totalDistanceMeters}m',
      child: records.isEmpty
          ? const _EmptyResult(message: '표시할 수영 기록이 없습니다.')
          : _ResultTable(
              headers: const ['랩', '영법', '거리', '기록', '휴식'],
              rows: records
                  .map(
                    (record) => [
                      '${record.lapNumber}',
                      record.stroke,
                      '${record.distanceMeters}m',
                      formatDuration(record.timeSeconds),
                      record.restCount == 0
                          ? '—'
                          : formatDuration(record.restSeconds),
                    ],
                  )
                  .toList(),
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
    return _ResultScaffold(
      title: 'IM $distance 찾기',
      summary: '${sessions.length}개 · 접영–배영–평영–자유형 순서',
      child: sessions.isEmpty
          ? _EmptyResult(message: '연속된 IM $distance 기록이 없습니다.')
          : Column(
              children: [
                _ComparisonChart(
                  title: '세션별 기록',
                  values: sessions.map((record) => record.timeSeconds).toList(),
                  labels: List.generate(
                    sessions.length,
                    (index) => '${index + 1}회',
                  ),
                  suffix: '초',
                ),
                const SizedBox(height: 16),
                _ResultTable(
                  headers: const [
                    '세션',
                    '랩',
                    '기록',
                    '페이스/100m',
                    '영법별 기록',
                    '구간 휴식'
                  ],
                  rows: sessions.indexed
                      .map(
                        (entry) => [
                          '${entry.$1 + 1}회',
                          '${entry.$2.lapNumber}–${entry.$2.lapNumber + entry.$2.lapCount - 1}',
                          formatDuration(entry.$2.timeSeconds),
                          formatDuration(
                            entry.$2.timeSeconds *
                                100 /
                                entry.$2.distanceMeters,
                          ),
                          entry.$2.splitsSeconds
                              .map(formatDuration)
                              .join(' / '),
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
    final summaries = analysis.strokeSummaries;
    return _ResultScaffold(
      title: '영법별 평가',
      summary: '영법별 거리와 100m 페이스',
      child: summaries.isEmpty
          ? const _EmptyResult(message: '평가할 수영 기록이 없습니다.')
          : Column(
              children: [
                _ComparisonChart(
                  title: '100m 페이스',
                  values: summaries
                      .map((summary) => summary.paceSecondsPer100m)
                      .toList(),
                  labels: summaries.map((summary) => summary.stroke).toList(),
                  suffix: '초',
                ),
                const SizedBox(height: 16),
                _ResultTable(
                  headers: const [
                    '영법',
                    '랩',
                    '거리',
                    '총 시간',
                    '페이스/100m',
                    '휴식',
                    '휴식 시간',
                  ],
                  rows: [
                    ...summaries.map(
                      (summary) => [
                        summary.stroke,
                        '${summary.lapCount}',
                        '${summary.totalDistanceMeters}m',
                        formatDuration(summary.totalTimeSeconds),
                        formatDuration(summary.paceSecondsPer100m),
                        '${summary.restCount}회',
                        formatDuration(summary.totalRestSeconds),
                      ],
                    ),
                    _totalRow(summaries),
                  ],
                ),
              ],
            ),
    );
  }

  List<String> _totalRow(List<StrokeSummary> summaries) {
    final laps = summaries.fold<int>(0, (total, item) => total + item.lapCount);
    final distance = summaries.fold<int>(
      0,
      (total, item) => total + item.totalDistanceMeters,
    );
    final time = summaries.fold<double>(
      0,
      (total, item) => total + item.totalTimeSeconds,
    );
    final rests =
        summaries.fold<int>(0, (total, item) => total + item.restCount);
    final restTime = summaries.fold<double>(
      0,
      (total, item) => total + item.totalRestSeconds,
    );
    return [
      '전체',
      '$laps',
      '${distance}m',
      formatDuration(time),
      formatDuration(distance == 0 ? 0 : time * 100 / distance),
      '$rests회',
      formatDuration(restTime),
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
    final scheme = Theme.of(context).colorScheme;
    return Scaffold(
      appBar: AppBar(
        title: Text(title, style: const TextStyle(fontWeight: FontWeight.w700)),
      ),
      body: ListView(
        padding: const EdgeInsets.fromLTRB(18, 8, 18, 28),
        children: [
          Text(summary, style: TextStyle(color: _muted(context), fontSize: 14)),
          const SizedBox(height: 16),
          DecoratedBox(
            decoration: BoxDecoration(
              color: scheme.surfaceContainerLow,
              borderRadius: BorderRadius.circular(20),
              border: Border.all(color: scheme.outlineVariant),
            ),
            child: Padding(
              padding: const EdgeInsets.all(16),
              child: child,
            ),
          ),
        ],
      ),
    );
  }
}

/// Formats IM rest values only for butterfly-backstroke, backstroke-breaststroke,
/// and breaststroke-freestyle transitions.
String _formatImRestIntervals(SwimAnalysis analysis, SwimRecord imRecord) {
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
    intervals.add('${labels[index]} ${formatDuration(lap.restSeconds)}');
  }
  return intervals.isEmpty ? '—' : intervals.join(' · ');
}

/// Renders a table with centered values, visible horizontal scrolling, and
/// alternating row surfaces for readability on narrow phones.
class _ResultTable extends StatefulWidget {
  const _ResultTable({required this.headers, required this.rows});

  final List<String> headers;
  final List<List<String>> rows;

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
    final naturalWidths = List.generate(widget.headers.length, (column) {
      final longestText = widget.rows.fold<int>(
        widget.headers[column].length,
        (longest, row) => math.max(longest, row[column].length),
      );
      return (longestText * 8.5 + 28).clamp(78.0, 260.0);
    });
    final minTableWidth = math.max(0, MediaQuery.sizeOf(context).width - 68);
    final naturalTableWidth =
        naturalWidths.fold<double>(0, (total, width) => total + width);
    final extraWidth =
        math.max(0, minTableWidth - naturalTableWidth) / naturalWidths.length;
    final columnWidths =
        naturalWidths.map((width) => width + extraWidth).toList();
    return Card(
      clipBehavior: Clip.antiAlias,
      margin: EdgeInsets.zero,
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.stretch,
        children: [
          Padding(
            padding: const EdgeInsets.fromLTRB(14, 11, 14, 7),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.end,
              children: [
                Icon(Icons.swipe_rounded, size: 16, color: _muted(context)),
                const SizedBox(width: 5),
                Text(
                  '좌우로 밀어 보기',
                  style: TextStyle(color: _muted(context), fontSize: 11),
                ),
              ],
            ),
          ),
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
                      background: scheme.surfaceContainerHighest,
                      isHeader: true,
                    ),
                    for (var index = 0; index < widget.rows.length; index++)
                      _TableRow(
                        values: widget.rows[index],
                        columnWidths: columnWidths,
                        background: index.isEven
                            ? scheme.surface
                            : scheme.surfaceContainerLow,
                        isEmphasized: widget.rows[index].first == '전체',
                      ),
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
    this.isHeader = false,
    this.isEmphasized = false,
  });

  final List<String> values;
  final List<double> columnWidths;
  final Color background;
  final bool isHeader;
  final bool isEmphasized;

  @override
  Widget build(BuildContext context) {
    return Container(
      constraints: const BoxConstraints(minHeight: 48),
      color: background,
      child: Row(
        children: List.generate(values.length, (index) {
          return SizedBox(
            width: columnWidths[index],
            child: Padding(
              padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 9),
              child: Text(
                values[index],
                textAlign: TextAlign.center,
                maxLines: 3,
                overflow: TextOverflow.ellipsis,
                style: TextStyle(
                  color: _ink(context),
                  fontSize: isHeader ? 11 : 12,
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
      padding: const EdgeInsets.symmetric(horizontal: 12, vertical: 30),
      child: Column(
        children: [
          Icon(Icons.search_off_rounded, color: _tertiary(context), size: 34),
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
  });

  final String title;
  final List<double> values;
  final List<String> labels;
  final String suffix;

  @override
  Widget build(BuildContext context) {
    final maximum =
        values.fold<double>(0, (max, value) => value > max ? value : max);
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
                  final ratio = maximum == 0 ? 0.0 : values[index] / maximum;
                  return Expanded(
                    child: Padding(
                      padding: const EdgeInsets.symmetric(horizontal: 5),
                      child: Column(
                        mainAxisAlignment: MainAxisAlignment.end,
                        children: [
                          Text(
                            '${values[index].toStringAsFixed(0)}$suffix',
                            style: TextStyle(
                              color: _muted(context),
                              fontSize: 10,
                            ),
                          ),
                          const SizedBox(height: 5),
                          Container(
                            height: 78 * ratio.clamp(0.08, 1),
                            decoration: BoxDecoration(
                              color: _accent(context).withValues(
                                alpha: 0.5 + 0.5 * ratio.clamp(0, 1),
                              ),
                              borderRadius: const BorderRadius.vertical(
                                top: Radius.circular(8),
                              ),
                            ),
                          ),
                          const SizedBox(height: 6),
                          Text(
                            labels[index],
                            maxLines: 1,
                            overflow: TextOverflow.ellipsis,
                            style: TextStyle(
                              color: _ink(context),
                              fontSize: 10,
                            ),
                          ),
                        ],
                      ),
                    ),
                  );
                }),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
