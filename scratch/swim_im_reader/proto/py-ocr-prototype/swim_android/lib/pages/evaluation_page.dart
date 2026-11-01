import 'package:flutter/material.dart';

import '../models/swim_health_session.dart';
import '../swim_analysis.dart';
import '../theme/swim_colors.dart';

class EvaluationPage extends StatefulWidget {
  const EvaluationPage({
    required this.session,
    required this.occurrence,
    required this.inferIm100,
    required this.excludePaceOutliers,
    required this.finSwimmingIncluded,
    required this.onSessionChanged,
    this.maximumHeartRateBpm,
    super.key,
  });

  final SwimHealthSession session;
  final int occurrence;
  final bool inferIm100;
  final bool excludePaceOutliers;
  final bool finSwimmingIncluded;
  final Future<void> Function(SwimHealthSession) onSessionChanged;
  final int? maximumHeartRateBpm;

  @override
  State<EvaluationPage> createState() => _EvaluationPageState();
}

class _EvaluationPageState extends State<EvaluationPage> {
  late SwimHealthSession _session = widget.session;

  Future<void> _saveSession(SwimHealthSession session) async {
    await widget.onSessionChanged(session);
    if (mounted) setState(() => _session = session);
  }

  @override
  void didUpdateWidget(covariant EvaluationPage oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (oldWidget.session.startTime != widget.session.startTime) {
      _session = widget.session;
    }
  }

  @override
  Widget build(BuildContext context) {
    final session = _session;
    final analysis = session.analyze(
      inferIm100: widget.inferIm100,
      excludePaceOutliers: widget.excludePaceOutliers,
      finSwimmingIncluded: widget.finSwimmingIncluded,
    );
    final time = TimeOfDay.fromDateTime(session.startTime).format(context);
    final poolLength = session.poolLengthMeters;
    final distance = session.distanceMeters;
    final sortedImRecords = analysis.imRecords.toList()
      ..sort(
        (first, second) => first.timeSeconds.compareTo(second.timeSeconds),
      );
    return Scaffold(
      appBar: AppBar(title: Text('${widget.occurrence}회차 평가')),
      body: ListView(
        padding: const EdgeInsets.fromLTRB(18, 8, 18, 28),
        children: [
          _SessionSummaryCard(
            session: session,
            occurrence: widget.occurrence,
            time: time,
          ),
          const SizedBox(height: 14),
          if (session.intervals.isEmpty)
            const _InfoCard(
              message: '삼성 헬스가 이 기록의 랩/영법 구간을 제공하지 않아 세션 시간과 거리만 표시합니다.',
              icon: Icons.info_outline_rounded,
            )
          else ...[
            if (poolLength == null) ...[
              const _InfoCard(
                message: '풀 길이 정보가 없어 25m 기준으로 계산합니다. IM 거리와 페이스는 추정값입니다.',
                icon: Icons.warning_amber_rounded,
              ),
              const SizedBox(height: 12),
            ],
            _SectionTitle(
              title: '구간별 기록',
              trailing: poolLength == null ? '풀 길이 정보 없음' : '$poolLength m 풀',
            ),
            const SizedBox(height: 8),
            _IntervalTable(
              session: session,
              poolLengthMeters: poolLength,
              maximumHeartRateBpm: widget.maximumHeartRateBpm,
              onSessionChanged: _saveSession,
            ),
            if (session.restAnalysis?.needsReview == true) ...[
              const SizedBox(height: 8),
              const _InfoCard(
                message: 'OCR 일치율이 99% 미만이거나 삼성 헬스와 랩 수·영법·기록 시간이 다릅니다. 휴식 시간을 수정하거나 원본으로 되돌려 확인해 주세요.',
                icon: Icons.warning_amber_rounded,
              ),
            ],
            const SizedBox(height: 16),
            _SectionTitle(
              title: 'IM ${analysis.poolLengthMeters * 4} 평가',
              trailing: '${analysis.imRecords.length}개 발견',
            ),
            const SizedBox(height: 8),
            if (analysis.imRecords.isEmpty)
              const _InfoCard(
                message: '연속된 접·배·평·자 또는 설정한 IM100 추정 구간이 없습니다.',
                icon: Icons.search_off_rounded,
              )
            else ...[
              _ComparisonChart(
                title: 'IM 세션별 기록',
                values: sortedImRecords
                    .map((record) => record.timeSeconds)
                    .toList(),
                labels: [
                  for (final record in sortedImRecords)
                    '혼영세션 ${analysis.imRecords.indexOf(record) + 1}'
                        '${record.inferred ? ' 추정' : ''}',
                ],
                barColors: [
                  for (final record in sortedImRecords)
                    record.inferred
                        ? swimStrokeColor(context, '자유')
                        : Theme.of(context).brightness == Brightness.dark
                        ? Colors.lightGreenAccent
                        : Colors.green.shade600,
                ],
              ),
              const SizedBox(height: 8),
              for (var index = 0; index < analysis.imRecords.length; index++)
                _ImCard(
                  record: analysis.imRecords[index],
                  index: index + 1,
                  poolLengthMeters: analysis.poolLengthMeters,
                ),
            ],
            if (analysis.strokeSummaries.isNotEmpty) ...[
              const SizedBox(height: 16),
              const _SectionTitle(title: '영법별 요약'),
              const SizedBox(height: 8),
              _StrokeOverview(analysis: analysis),
              const SizedBox(height: 10),
              for (final summary in _orderedStrokeSummaries(
                analysis.strokeSummaries,
              ))
                _StrokeSummaryCard(summary: summary, records: analysis.records),
              if (analysis.records.any((record) => record.paceExcluded))
                _ExcludedLapsNote(analysis: analysis),
            ],
          ],
          if (distance == null && session.intervals.isNotEmpty) ...[
            const SizedBox(height: 8),
            const _InfoCard(
              message: '삼성 헬스에서 총 거리를 제공하지 않아 구간 수와 풀 길이로 계산한 값만 사용합니다.',
              icon: Icons.straighten_rounded,
            ),
          ],
        ],
      ),
    );
  }
}

List<StrokeSummary> _orderedStrokeSummaries(List<StrokeSummary> summaries) {
  const order = {
    '자유': 0,
    '자유형': 0,
    '배영': 1,
    '평영': 2,
    '접영': 3,
    '킥판': 4,
    '혼영': 5,
  };
  return summaries.toList()..sort((first, second) {
    final rank = (order[first.stroke] ?? 6).compareTo(
      order[second.stroke] ?? 6,
    );
    return rank == 0 ? first.stroke.compareTo(second.stroke) : rank;
  });
}

class _SessionSummaryCard extends StatelessWidget {
  const _SessionSummaryCard({
    required this.session,
    required this.occurrence,
    required this.time,
  });

  final SwimHealthSession session;
  final int occurrence;
  final String time;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    final restAnalysis = session.restAnalysis;
    final sessionLabel = restAnalysis == null
        ? '$occurrence회차 · $time'
        : '$occurrence회차 · $time - '
              '${restAnalysis.needsReview ? '휴식구간 점검 필요' : '휴식구간 분석 완료'}';
    final statusColor = restAnalysis == null
        ? colors.onPrimaryContainer
        : restAnalysisStatusColor(
            context,
            analyzed: true,
            needsReview: restAnalysis.needsReview,
          );
    return Container(
      padding: const EdgeInsets.all(20),
      decoration: BoxDecoration(
        color: colors.primaryContainer,
        borderRadius: BorderRadius.circular(20),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(
            sessionLabel,
            style: TextStyle(
              color: statusColor,
              fontSize: 20,
              fontWeight: FontWeight.w800,
            ),
          ),
          const SizedBox(height: 4),
          Text(
            '${session.startTime.year}년 ${session.startTime.month}월 '
            '${session.startTime.day}일 · ${session.displayExerciseType}',
            style: TextStyle(color: colors.onPrimaryContainer),
          ),
          const SizedBox(height: 16),
          Wrap(
            spacing: 18,
            runSpacing: 12,
            children: [
              _Metric(
                label: '거리',
                value: session.distanceMeters == null
                    ? '—'
                    : '${session.distanceMeters!.round()}m',
              ),
              _Metric(
                label: '운동시간',
                value: formatDuration(session.durationSeconds),
              ),
              _Metric(
                label: '전체 휴식 추정',
                value: session.estimatedRestSeconds <= 0
                    ? '—'
                    : formatDuration(session.estimatedRestSeconds),
              ),
              if (session.displayAverageHeartRateBpm != null)
                _Metric(
                  label: '평균 심박수',
                  value: '${session.displayAverageHeartRateBpm} bpm',
                ),
              if (session.displayMaximumHeartRateBpm != null)
                _Metric(
                  label: '최고 심박수',
                  value: '${session.displayMaximumHeartRateBpm} bpm',
                ),
              if (restAnalysis?.ocrAccuracyPercent case final accuracy?)
                _Metric(
                  label: 'OCR 일치율',
                  value: '${accuracy.toStringAsFixed(1)}%',
                  valueColor: ocrAccuracyColor(context, accuracy),
                ),
              _Metric(
                label: '칼로리',
                value: session.calories == null
                    ? '—'
                    : '${session.calories!.round()} kcal',
              ),
              _Metric(label: '구간', value: '${session.intervals.length}개'),
            ],
          ),
        ],
      ),
    );
  }
}

class _Metric extends StatelessWidget {
  const _Metric({required this.label, required this.value, this.valueColor});

  final String label;
  final String value;
  final Color? valueColor;

  @override
  Widget build(BuildContext context) {
    final color = Theme.of(context).colorScheme.onPrimaryContainer;
    return SizedBox(
      width: 100,
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(label, style: TextStyle(color: color.withValues(alpha: 0.75))),
          const SizedBox(height: 2),
          Text(
            value,
            style: TextStyle(
              color: valueColor ?? color,
              fontWeight: FontWeight.w800,
              fontSize: 16,
            ),
          ),
        ],
      ),
    );
  }
}

class _SectionTitle extends StatelessWidget {
  const _SectionTitle({required this.title, this.trailing});

  final String title;
  final String? trailing;

  @override
  Widget build(BuildContext context) {
    return Row(
      children: [
        Expanded(
          child: Text(
            title,
            style: Theme.of(context).textTheme.titleMedium
                ?.copyWith(fontWeight: FontWeight.w800),
          ),
        ),
        if (trailing != null)
          Text(
            trailing!,
            style: TextStyle(
              color: Theme.of(context).colorScheme.onSurfaceVariant,
              fontSize: 12,
            ),
          ),
      ],
    );
  }
}

class _IntervalTable extends StatefulWidget {
  const _IntervalTable({
    required this.session,
    required this.poolLengthMeters,
    required this.maximumHeartRateBpm,
    required this.onSessionChanged,
  });

  final SwimHealthSession session;
  final int? poolLengthMeters;
  final int? maximumHeartRateBpm;
  final Future<void> Function(SwimHealthSession) onSessionChanged;

  @override
  State<_IntervalTable> createState() => _IntervalTableState();
}

class _IntervalTableState extends State<_IntervalTable> {
  bool _isExpanded = false;
  late List<({int? average, int? maximum})> _lapHeartRates;
  late List<_HeartRatePoint> _heartRatePoints;

  @override
  void initState() {
    super.initState();
    _prepareHeartRateData(widget.session);
  }

  @override
  void didUpdateWidget(covariant _IntervalTable oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (oldWidget.session != widget.session) {
      _prepareHeartRateData(widget.session);
    }
  }

  void _prepareHeartRateData(SwimHealthSession session) {
    _lapHeartRates = session.heartRatesByLap;
    final sessionElapsedSeconds =
        session.endTime.difference(session.startTime).inMilliseconds / 1000;
    _heartRatePoints = session.hasCompleteRestAnalysis
        ? (session.heartRateSamples
              .map(
                (sample) => _HeartRatePoint(
                  sample.timestamp
                          .difference(session.startTime)
                          .inMilliseconds /
                      1000,
                  sample.beatsPerMinute.toDouble(),
                ),
              )
              .where(
                (point) =>
                    point.seconds >= 0 && point.seconds < sessionElapsedSeconds,
              )
              .toList()
            ..sort((first, second) => first.seconds.compareTo(second.seconds)))
        : [];
    if (_heartRatePoints.isEmpty && session.hasCompleteRestAnalysis) {
      var elapsedSeconds = 0.0;
      for (var index = 0; index < session.intervals.length; index++) {
        final interval = session.intervals[index];
        final heartRate = _lapHeartRates[index].average;
        if (heartRate != null) {
          _heartRatePoints.add(
            _HeartRatePoint(
              elapsedSeconds + interval.durationSeconds / 2,
              heartRate.toDouble(),
            ),
          );
        }
        elapsedSeconds +=
            interval.durationSeconds +
            (session.restAnalysis!.restSecondsByLap[index] ?? 0);
      }
    }
  }

  Future<void> _editRestSeconds() async {
    final session = widget.session;
    final analysis = session.restAnalysis;
    if (analysis == null) return;
    final controllers = [
      for (var index = 0; index < session.intervals.length; index++)
        TextEditingController(
          text: (analysis.restSecondsByLap[index] ?? 0).toStringAsFixed(1),
        ),
    ];
    try {
      final values = await showDialog<List<double>>(
        context: context,
        builder: (context) => AlertDialog(
          title: const Text('랩별 휴식 시간 수정'),
          content: SizedBox(
            width: 380,
            child: ListView.builder(
              shrinkWrap: true,
              itemCount: session.intervals.length,
              itemBuilder: (context, index) => Padding(
                padding: const EdgeInsets.symmetric(vertical: 4),
                child: Row(
                  children: [
                    SizedBox(
                      width: 74,
                      child: Text(
                        '${index + 1}랩 · ${session.intervals[index].displayStroke}',
                      ),
                    ),
                    const SizedBox(width: 8),
                    Expanded(
                      child: TextField(
                        controller: controllers[index],
                        keyboardType: const TextInputType.numberWithOptions(
                          decimal: true,
                        ),
                        decoration: const InputDecoration(
                          labelText: '휴식 초',
                          suffixText: '초',
                          isDense: true,
                        ),
                      ),
                    ),
                  ],
                ),
              ),
            ),
          ),
          actions: [
            TextButton(
              onPressed: () => Navigator.pop(context),
              child: const Text('취소'),
            ),
            FilledButton(
              onPressed: () {
                final parsed = <double>[];
                for (final controller in controllers) {
                  final value = double.tryParse(controller.text.trim());
                  if (value == null || !value.isFinite || value < 0) {
                    ScaffoldMessenger.of(context).showSnackBar(
                      const SnackBar(
                        content: Text('휴식 시간은 0 이상의 초 단위 숫자로 입력해 주세요.'),
                      ),
                    );
                    return;
                  }
                  parsed.add(value);
                }
                Navigator.pop(context, parsed);
              },
              child: const Text('저장'),
            ),
          ],
        ),
      );
      if (values != null && mounted) {
        await _saveChanges(session.withEditedRestSeconds(values));
      }
    } finally {
      for (final controller in controllers) {
        controller.dispose();
      }
    }
  }

  Future<void> _resetRestAnalysis() async {
    final confirmed = await showDialog<bool>(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('휴식 분석 되돌리기'),
        content: const Text('OCR 및 수동 수정한 휴식 시간과 심박 표시를 원래 상태로 되돌릴까요?'),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(context, false),
            child: const Text('취소'),
          ),
          FilledButton(
            onPressed: () => Navigator.pop(context, true),
            child: const Text('원상태'),
          ),
        ],
      ),
    );
    if (confirmed == true && mounted) {
      await _saveChanges(widget.session.withRestAnalysis(null));
    }
  }

  Future<void> _saveChanges(SwimHealthSession session) async {
    try {
      await widget.onSessionChanged(session);
    } catch (error) {
      if (!mounted) return;
      ScaffoldMessenger.of(
        context,
      ).showSnackBar(SnackBar(content: Text('휴식 분석 결과를 저장하지 못했습니다.\n$error')));
    }
  }

  @override
  Widget build(BuildContext context) {
    final session = widget.session;
    final visibleLapIndexes = _visibleLapIndexes();
    final bestLapIndexes = visibleLapIndexes.toSet();
    final restAnalysis = session.restAnalysis;
    final hasStoredLapHeartRate =
        session.hasCompleteRestAnalysis &&
        (restAnalysis?.averageHeartRateByLap.any((rate) => rate != null) ??
            false);
    final showHeartRate =
        session.hasCompleteRestAnalysis &&
        (session.heartRateSamples.isNotEmpty || hasStoredLapHeartRate);
    final tableColumns = <DataColumn>[
      const DataColumn(label: Text('랩')),
      const DataColumn(label: Text('영법')),
      const DataColumn(label: Text('기록')),
      if (restAnalysis != null) const DataColumn(label: Text('휴식')),
      const DataColumn(label: Text('페이스/100m')),
      const DataColumn(label: Text('스트로크')),
      const DataColumn(label: Text('SWOLF')),
      if (showHeartRate) const DataColumn(label: Text('심박')),
    ];
    return Card(
      clipBehavior: Clip.antiAlias,
      child: Padding(
        padding: const EdgeInsets.fromLTRB(14, 8, 14, 14),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              children: [
                Expanded(
                  child: Text(
                    '전체 구간 기록',
                    style: Theme.of(context).textTheme.titleSmall
                        ?.copyWith(fontWeight: FontWeight.w800),
                  ),
                ),
                if (restAnalysis != null) ...[
                  IconButton(
                    tooltip: '휴식 시간 수정',
                    onPressed: _editRestSeconds,
                    icon: const Icon(Icons.edit_outlined),
                    visualDensity: VisualDensity.compact,
                  ),
                  IconButton(
                    tooltip: '휴식 분석 원상태로',
                    onPressed: _resetRestAnalysis,
                    icon: const Icon(Icons.restore_rounded),
                    visualDensity: VisualDensity.compact,
                  ),
                ],
                TextButton.icon(
                  onPressed: () => setState(() => _isExpanded = !_isExpanded),
                  icon: Icon(
                    _isExpanded
                        ? Icons.expand_less_rounded
                        : Icons.expand_more_rounded,
                  ),
                  label: Text(_isExpanded ? '접어보기' : '펼쳐보기'),
                ),
              ],
            ),
            const Divider(height: 12),
            Text(
              '영법별 최고 기록',
              style: Theme.of(context).textTheme.labelLarge
                  ?.copyWith(fontWeight: FontWeight.w700),
            ),
            const SizedBox(height: 4),
            for (final index in visibleLapIndexes) _lapPaceRow(context, index),
            if (session.hasCompleteRestAnalysis &&
                widget.maximumHeartRateBpm != null) ...[
              const SizedBox(height: 12),
              _HeartRateChart(
                points: _heartRatePoints,
                durationSeconds:
                    session.endTime
                        .difference(session.startTime)
                        .inMilliseconds /
                    1000,
                maximumHeartRateBpm: widget.maximumHeartRateBpm!,
              ),
            ],
            if (_isExpanded) ...[
              const Divider(height: 20),
              SingleChildScrollView(
                scrollDirection: Axis.horizontal,
                child: DataTable(
                  columnSpacing: 18,
                  columns: tableColumns,
                  rows: [
                    for (
                      var index = 0;
                      index < session.intervals.length;
                      index++
                    )
                      _intervalRow(
                        context,
                        index,
                        isBest: bestLapIndexes.contains(index),
                        showRest: restAnalysis != null,
                        showHeartRate: showHeartRate,
                        heartRate: _lapHeartRates[index],
                      ),
                  ],
                ),
              ),
            ],
          ],
        ),
      ),
    );
  }

  List<int> _visibleLapIndexes() {
    final bestIndexByStroke = <String, int>{};
    for (var index = 0; index < widget.session.intervals.length; index++) {
      final interval = widget.session.intervals[index];
      final currentIndex = bestIndexByStroke[interval.displayStroke];
      if (currentIndex == null ||
          interval.durationSeconds <
              widget.session.intervals[currentIndex].durationSeconds) {
        bestIndexByStroke[interval.displayStroke] = index;
      }
    }
    final indexes = bestIndexByStroke.values.toList()..sort();
    return indexes;
  }

  Widget _lapPaceRow(BuildContext context, int index) {
    final interval = widget.session.intervals[index];
    final pace = widget.poolLengthMeters == null
        ? null
        : interval.durationSeconds * 100 / widget.poolLengthMeters!;
    final paceLabel = pace == null ? '—' : '${formatDuration(pace)}/100m';
    final muted = Theme.of(context).colorScheme.onSurfaceVariant;
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 5),
      child: Row(
        children: [
          SizedBox(
            width: 48,
            child: Text(
              '${index + 1}랩',
              style: TextStyle(color: muted, fontSize: 12),
            ),
          ),
          Expanded(
            child: Text(
              interval.displayStroke,
              style: TextStyle(
                color: swimStrokeColor(context, interval.displayStroke),
                fontWeight: FontWeight.w700,
              ),
            ),
          ),
          const SizedBox(width: 8),
          Text(
            formatDuration(interval.durationSeconds),
            style: TextStyle(color: muted, fontSize: 12),
          ),
          const SizedBox(width: 8),
          Text(paceLabel, style: TextStyle(color: muted, fontSize: 12)),
        ],
      ),
    );
  }

  DataRow _intervalRow(
    BuildContext context,
    int index, {
    required bool isBest,
    required bool showRest,
    required bool showHeartRate,
    required ({int? average, int? maximum}) heartRate,
  }) {
    final interval = widget.session.intervals[index];
    final restAnalysis = widget.session.restAnalysis;
    final bestColor = Theme.of(context).brightness == Brightness.dark
        ? Colors.lightGreenAccent
        : Colors.green.shade700;
    final analysisColor = restAnalysis == null
        ? null
        : restAnalysisStatusColor(
            context,
            analyzed: true,
            needsReview: restAnalysis.needsReview,
          );
    final pace = widget.poolLengthMeters == null
        ? '—'
        : formatDuration(
            interval.durationSeconds * 100 / widget.poolLengthMeters!,
          );
    final cells = <DataCell>[
      DataCell(
        Text(
          '${index + 1}',
          style: analysisColor == null
              ? null
              : TextStyle(color: analysisColor, fontWeight: FontWeight.w800),
        ),
      ),
      DataCell(
        Text(
          interval.displayStroke,
          style: TextStyle(
            color: swimStrokeColor(context, interval.displayStroke),
            fontWeight: FontWeight.w700,
          ),
        ),
      ),
      DataCell(
        Text(
          formatDuration(interval.durationSeconds),
          style: isBest
              ? TextStyle(color: bestColor, fontWeight: FontWeight.w800)
              : null,
        ),
      ),
      if (showRest)
        DataCell(
          Text(
            restAnalysis!.restSecondsByLap[index] == null
                ? '확인'
                : restAnalysis.restSecondsByLap[index]! <= 0
                ? '—'
                : formatDuration(restAnalysis.restSecondsByLap[index]!),
          ),
        ),
      DataCell(Text(pace)),
      DataCell(Text('${interval.strokeCount}')),
      DataCell(
        Text('${(interval.durationSeconds + interval.strokeCount).round()}'),
      ),
      if (showHeartRate) DataCell(Text('${heartRate.average ?? '—'} bpm')),
    ];
    return DataRow(cells: cells);
  }
}

class _HeartRatePoint {
  const _HeartRatePoint(this.seconds, this.beatsPerMinute);

  final double seconds;
  final double beatsPerMinute;
}

class _HeartRateChart extends StatelessWidget {
  const _HeartRateChart({
    required this.points,
    required this.durationSeconds,
    required this.maximumHeartRateBpm,
  });

  final List<_HeartRatePoint> points;
  final double durationSeconds;
  final int maximumHeartRateBpm;

  static const _zonePercentRanges = [
    (0.0, 0.6),
    (0.6, 0.7),
    (0.7, 0.8),
    (0.8, 0.9),
    (0.9, 1.0),
  ];

  @override
  Widget build(BuildContext context) {
    if (points.isEmpty) return const SizedBox.shrink();
    final colors = heartRateZoneColors(context);
    final textColor = Theme.of(context).colorScheme.onSurfaceVariant;
    final gridColor = Theme.of(context).dividerColor.withValues(alpha: 0.5);
    return Card(
      child: Padding(
        padding: const EdgeInsets.all(14),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            const Text('심박수 곡선', style: TextStyle(fontWeight: FontWeight.w700)),
            const SizedBox(height: 2),
            Text(
              '심박 로그가 비어 있는 구간은 선으로 연결하지 않습니다.',
              style: TextStyle(
                color: Theme.of(context).colorScheme.onSurfaceVariant,
                fontSize: 11,
              ),
            ),
            const SizedBox(height: 8),
            SizedBox(
              width: double.infinity,
              height: 210,
              child: CustomPaint(
                painter: _HeartRateChartPainter(
                  points: points,
                  durationSeconds: durationSeconds,
                  maximumHeartRateBpm: maximumHeartRateBpm,
                  zoneColors: colors,
                  textColor: textColor,
                  gridColor: gridColor,
                ),
              ),
            ),
            const SizedBox(height: 8),
            Wrap(
              spacing: 10,
              runSpacing: 6,
              children: [
                for (var index = 0; index < colors.length; index++)
                  Row(
                    mainAxisSize: MainAxisSize.min,
                    children: [
                      Container(
                        width: 12,
                        height: 3,
                        decoration: BoxDecoration(
                          color: colors[index],
                          borderRadius: BorderRadius.circular(2),
                        ),
                      ),
                      const SizedBox(width: 4),
                      Text(
                        'Zone${index + 1} '
                        '(${(_zonePercentRanges[index].$1 * 100).round()}'
                        '-${(_zonePercentRanges[index].$2 * 100).round()}%)',
                        style: TextStyle(color: textColor, fontSize: 10),
                      ),
                    ],
                  ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}

class _HeartRateChartPainter extends CustomPainter {
  const _HeartRateChartPainter({
    required this.points,
    required this.durationSeconds,
    required this.maximumHeartRateBpm,
    required this.zoneColors,
    required this.textColor,
    required this.gridColor,
  });

  final List<_HeartRatePoint> points;
  final double durationSeconds;
  final int maximumHeartRateBpm;
  final List<Color> zoneColors;
  final Color textColor;
  final Color gridColor;

  int _zoneFor(double heartRate) {
    final percentage = heartRate / maximumHeartRateBpm;
    if (percentage < 0.6) return 0;
    if (percentage < 0.7) return 1;
    if (percentage < 0.8) return 2;
    if (percentage < 0.9) return 3;
    return 4;
  }

  String _formatTime(double seconds) {
    final wholeSeconds = seconds.round();
    final minutes = wholeSeconds ~/ 60;
    final remainingSeconds = wholeSeconds % 60;
    return '$minutes:${remainingSeconds.toString().padLeft(2, '0')}';
  }

  void _drawLabel(
    Canvas canvas,
    String text,
    Offset offset, {
    TextAlign align = TextAlign.left,
  }) {
    final painter = TextPainter(
      text: TextSpan(
        text: text,
        style: TextStyle(color: textColor, fontSize: 10),
      ),
      textDirection: TextDirection.ltr,
      textAlign: align,
    )..layout();
    painter.paint(canvas, offset);
  }

  @override
  void paint(Canvas canvas, Size size) {
    if (points.isEmpty || maximumHeartRateBpm <= 0) return;
    final minObserved = points
        .map((point) => point.beatsPerMinute)
        .reduce((first, second) => first < second ? first : second);
    final maxObserved = points
        .map((point) => point.beatsPerMinute)
        .reduce((first, second) => first > second ? first : second);
    final minBpm = ((minObserved - 10) / 10).floor() * 10;
    var maxBpm = ((maxObserved + 10) / 10).ceil() * 10;
    if (maxBpm <= minBpm) maxBpm = minBpm + 20;
    final chart = Rect.fromLTRB(42, 12, size.width - 10, size.height - 34);
    final bpmRange = (maxBpm - minBpm).toDouble();
    final timeRange = [
      durationSeconds,
      points.last.seconds,
    ].reduce((first, second) => first > second ? first : second);
    final effectiveTimeRange = timeRange > 0 ? timeRange : 1;
    final gridPaint = Paint()
      ..color = gridColor
      ..strokeWidth = 1;

    for (var tick = 0; tick <= 4; tick++) {
      final ratio = tick / 4;
      final y = chart.bottom - chart.height * ratio;
      canvas.drawLine(Offset(chart.left, y), Offset(chart.right, y), gridPaint);
      _drawLabel(
        canvas,
        '${(minBpm + bpmRange * ratio).round()}',
        Offset(2, y - 6),
      );
    }
    _drawLabel(canvas, 'bpm', const Offset(2, 0));
    for (var tick = 0; tick <= 2; tick++) {
      final ratio = tick / 2;
      final x = chart.left + chart.width * ratio;
      _drawLabel(
        canvas,
        _formatTime(effectiveTimeRange * ratio),
        Offset(x - 14, chart.bottom + 5),
      );
    }
    _drawLabel(canvas, '시간', Offset(chart.center.dx - 10, size.height - 12));
    if (points.length < 2) return;

    canvas.save();
    canvas.clipRect(chart);
    final sampleGaps = [
      for (var index = 1; index < points.length; index++)
        points[index].seconds - points[index - 1].seconds,
    ]..sort();
    final typicalGap = sampleGaps.isEmpty
        ? 0.0
        : sampleGaps[sampleGaps.length ~/ 2];
    final maximumContinuousGap = typicalGap > 0
        ? (typicalGap * 4 > 30 ? typicalGap * 4 : 30)
        : 30.0;
    for (var index = 0; index < points.length - 1; index++) {
      final first = points[index];
      final second = points[index + 1];
      if (second.seconds - first.seconds > maximumContinuousGap) {
        continue;
      }
      final firstPoint = Offset(
        chart.left + chart.width * (first.seconds / effectiveTimeRange),
        chart.bottom -
            chart.height * ((first.beatsPerMinute - minBpm) / bpmRange),
      );
      final secondPoint = Offset(
        chart.left + chart.width * (second.seconds / effectiveTimeRange),
        chart.bottom -
            chart.height * ((second.beatsPerMinute - minBpm) / bpmRange),
      );
      final color =
          zoneColors[_zoneFor(
            (first.beatsPerMinute + second.beatsPerMinute) / 2,
          )];
      canvas.drawLine(
        firstPoint,
        secondPoint,
        Paint()
          ..color = color
          ..strokeWidth = 2.6
          ..strokeCap = StrokeCap.round,
      );
    }
    canvas.restore();
  }

  @override
  bool shouldRepaint(covariant _HeartRateChartPainter oldDelegate) =>
      oldDelegate.points != points ||
      oldDelegate.durationSeconds != durationSeconds ||
      oldDelegate.maximumHeartRateBpm != maximumHeartRateBpm ||
      oldDelegate.zoneColors != zoneColors ||
      oldDelegate.textColor != textColor ||
      oldDelegate.gridColor != gridColor;
}

class _ImCard extends StatelessWidget {
  const _ImCard({
    required this.record,
    required this.index,
    required this.poolLengthMeters,
  });

  final SwimRecord record;
  final int index;
  final int poolLengthMeters;

  @override
  Widget build(BuildContext context) {
    final strokes = const ['접영', '배영', '평영', '자유'];
    return Card(
      margin: const EdgeInsets.only(bottom: 8),
      child: Padding(
        padding: const EdgeInsets.all(16),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              children: [
                Expanded(
                  child: Text(
                    '혼영세션 $index · ${formatDuration(record.timeSeconds)}',
                    style: const TextStyle(fontWeight: FontWeight.w800),
                  ),
                ),
                if (record.inferred)
                  const Chip(
                    label: Text('자배평자 추정'),
                    visualDensity: VisualDensity.compact,
                  )
                else
                  const Chip(
                    label: Text('영법 확인'),
                    visualDensity: VisualDensity.compact,
                  ),
              ],
            ),
            Text(
              '${record.distanceMeters}m · '
              '${formatDuration(record.timeSeconds * 100 / record.distanceMeters)} /100m',
              style: TextStyle(
                color: Theme.of(context).colorScheme.onSurfaceVariant,
              ),
            ),
            const SizedBox(height: 8),
            const SizedBox(height: 10),
            for (
              var splitIndex = 0;
              splitIndex < record.splitsSeconds.length;
              splitIndex++
            )
              _imSplitRow(context, record, splitIndex, strokes),
          ],
        ),
      ),
    );
  }

  Widget _imSplitRow(
    BuildContext context,
    SwimRecord record,
    int splitIndex,
    List<String> strokes,
  ) {
    final stroke = strokes[splitIndex];
    final restSeconds = splitIndex < record.transitionRestSeconds.length
        ? record.transitionRestSeconds[splitIndex]
        : null;
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 2),
      child: Row(
        children: [
          Expanded(
            child: Text.rich(
              TextSpan(
                children: [
                  TextSpan(
                    text: stroke,
                    style: TextStyle(
                      color: swimStrokeColor(context, stroke),
                      fontWeight: FontWeight.w700,
                    ),
                  ),
                  if (restSeconds != null && restSeconds > 0)
                    TextSpan(
                      text: ' (휴식: ${_formatRestSeconds(restSeconds)}초)',
                      style: TextStyle(
                        color: Theme.of(context).colorScheme.onSurfaceVariant,
                        fontSize: 12,
                      ),
                    ),
                ],
              ),
            ),
          ),
          const SizedBox(width: 8),
          Text(
            '${poolLengthMeters}m · '
            '${formatDuration(record.splitsSeconds[splitIndex])}',
            style: TextStyle(
              color: swimStrokeColor(context, stroke),
              fontWeight: FontWeight.w700,
            ),
          ),
        ],
      ),
    );
  }
}

String _formatRestSeconds(double seconds) {
  final formatted = seconds == seconds.roundToDouble()
      ? seconds.toStringAsFixed(0)
      : seconds.toStringAsFixed(1);
  return formatted;
}

class _StrokeSummaryCard extends StatelessWidget {
  const _StrokeSummaryCard({required this.summary, required this.records});

  final StrokeSummary summary;
  final List<SwimRecord> records;

  @override
  Widget build(BuildContext context) {
    final excluded = summary.excludedLapNumbers;
    return Card(
      margin: const EdgeInsets.only(bottom: 7),
      child: Padding(
        padding: const EdgeInsets.all(14),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              children: [
                CircleAvatar(
                  radius: 7,
                  backgroundColor: swimStrokeColor(context, summary.stroke),
                ),
                const SizedBox(width: 8),
                Expanded(
                  child: Text(
                    summary.stroke,
                    style: const TextStyle(fontWeight: FontWeight.w800),
                  ),
                ),
                Text(
                  summary.paceDistanceMeters == 0
                      ? '—'
                      : '${formatDuration(summary.paceSecondsPer100m)}/100m',
                  style: TextStyle(
                    color: swimStrokeColor(context, summary.stroke),
                    fontWeight: FontWeight.w800,
                  ),
                ),
              ],
            ),
            const SizedBox(height: 6),
            Text(
              '${summary.lapCount}랩 · ${summary.totalDistanceMeters}m · '
              '${formatDuration(summary.totalTimeSeconds)}',
              style: TextStyle(
                color: Theme.of(context).colorScheme.onSurfaceVariant,
                fontSize: 12,
              ),
            ),
            if (excluded.isNotEmpty)
              Text(
                '페이스 제외: ${excluded.map((lap) => _formatExcludedLap(lap)).join(', ')}',
                style: TextStyle(
                  color: Theme.of(context).colorScheme.error,
                  fontSize: 12,
                  fontWeight: FontWeight.w700,
                ),
              ),
          ],
        ),
      ),
    );
  }

  String _formatExcludedLap(int lapNumber) {
    for (final record in records) {
      if (record.lapNumber == lapNumber) {
        final seconds = record.timeSeconds;
        final formattedSeconds = seconds == seconds.roundToDouble()
            ? seconds.toStringAsFixed(0)
            : seconds.toStringAsFixed(1);
        return '$lapNumber랩($formattedSeconds초)';
      }
    }
    return '$lapNumber랩';
  }
}

class _StrokeOverview extends StatelessWidget {
  const _StrokeOverview({required this.analysis});

  final SwimAnalysis analysis;

  @override
  Widget build(BuildContext context) {
    final summaries = analysis.strokeSummaries;
    final lapCount = summaries.fold<int>(
      0,
      (total, summary) => total + summary.lapCount,
    );
    final distance = summaries.fold<int>(
      0,
      (total, summary) => total + summary.totalDistanceMeters,
    );
    final duration = summaries.fold<double>(
      0,
      (total, summary) => total + summary.totalTimeSeconds,
    );
    final paceTime = summaries.fold<double>(
      0,
      (total, summary) => total + summary.paceTimeSeconds,
    );
    final paceDistance = summaries.fold<int>(
      0,
      (total, summary) => total + summary.paceDistanceMeters,
    );
    final bestPaceByStroke = <String, double>{};
    for (final record in analysis.records.where(
      (record) => !record.paceExcluded && record.distanceMeters > 0,
    )) {
      final pace = record.timeSeconds * 100 / record.distanceMeters;
      final current = bestPaceByStroke[record.stroke];
      if (current == null || pace < current) {
        bestPaceByStroke[record.stroke] = pace;
      }
    }
    final sortedStrokes = bestPaceByStroke.keys.toList()
      ..sort(
        (first, second) =>
            bestPaceByStroke[first]!.compareTo(bestPaceByStroke[second]!),
      );
    return Column(
      children: [
        _ComparisonChart(
          title: '영법별 최고 페이스',
          values: sortedStrokes
              .map((stroke) => bestPaceByStroke[stroke]!)
              .toList(),
          labels: sortedStrokes,
          barColors: sortedStrokes
              .map((stroke) => swimStrokeColor(context, stroke))
              .toList(),
        ),
        const SizedBox(height: 10),
        Card(
          child: ListTile(
            leading: const Icon(Icons.summarize_rounded),
            title: const Text(
              '전체',
              style: TextStyle(fontWeight: FontWeight.w800),
            ),
            subtitle: Text(
              '$lapCount랩 · ${distance}m · ${formatDuration(duration)}',
            ),
            trailing: Text(
              paceDistance == 0
                  ? '—'
                  : '${formatDuration(paceTime * 100 / paceDistance)}/100m',
              style: const TextStyle(fontWeight: FontWeight.w800),
            ),
          ),
        ),
      ],
    );
  }
}

class _ExcludedLapsNote extends StatelessWidget {
  const _ExcludedLapsNote({required this.analysis});

  final SwimAnalysis analysis;

  @override
  Widget build(BuildContext context) {
    final excluded = analysis.records
        .where((record) => record.paceExcluded)
        .toList();
    return _InfoCard(
      message:
          '오계측 의심 랩 ${excluded.length}개'
          '(${excluded.map(_formatExcludedLap).join(', ')})를 '
          '평균 페이스에서 제외했습니다.',
      icon: Icons.filter_alt_rounded,
    );
  }

  String _formatExcludedLap(SwimRecord record) {
    final seconds = record.timeSeconds;
    final formattedSeconds = seconds == seconds.roundToDouble()
        ? seconds.toStringAsFixed(0)
        : seconds.toStringAsFixed(1);
    return '${record.lapNumber}랩 $formattedSeconds초';
  }
}

class _ComparisonChart extends StatelessWidget {
  const _ComparisonChart({
    required this.title,
    required this.values,
    required this.labels,
    required this.barColors,
  });

  final String title;
  final List<double> values;
  final List<String> labels;
  final List<Color> barColors;

  @override
  Widget build(BuildContext context) {
    if (values.isEmpty) return const SizedBox.shrink();
    final maximum = values.fold<double>(
      0,
      (max, value) => value > max ? value : max,
    );
    final screenWidth = MediaQuery.sizeOf(context).width - 72;
    final chartWidth =
        (screenWidth > values.length * 52 ? screenWidth : values.length * 52)
            .toDouble();
    final colors = Theme.of(context).colorScheme;
    return Card(
      child: Padding(
        padding: const EdgeInsets.all(14),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text(title, style: const TextStyle(fontWeight: FontWeight.w700)),
            const SizedBox(height: 10),
            SingleChildScrollView(
              scrollDirection: Axis.horizontal,
              child: SizedBox(
                width: chartWidth,
                height: 128,
                child: Row(
                  crossAxisAlignment: CrossAxisAlignment.end,
                  children: [
                    for (var index = 0; index < values.length; index++)
                      Expanded(
                        child: Padding(
                          padding: const EdgeInsets.symmetric(horizontal: 3),
                          child: Column(
                            mainAxisAlignment: MainAxisAlignment.end,
                            children: [
                              Text(
                                formatDuration(values[index]),
                                style: TextStyle(
                                  color: colors.onSurfaceVariant,
                                  fontSize: 9,
                                ),
                              ),
                              const SizedBox(height: 4),
                              Container(
                                height: maximum == 0
                                    ? 5
                                    : 72 *
                                          (values[index] / maximum).clamp(
                                            0.08,
                                            1,
                                          ),
                                decoration: BoxDecoration(
                                  color: barColors[index],
                                  borderRadius: const BorderRadius.vertical(
                                    top: Radius.circular(7),
                                  ),
                                ),
                              ),
                              const SizedBox(height: 5),
                              Text(
                                labels[index],
                                maxLines: 1,
                                overflow: TextOverflow.ellipsis,
                                style: TextStyle(
                                  color: barColors[index],
                                  fontSize: 9,
                                  fontWeight: FontWeight.w700,
                                ),
                              ),
                            ],
                          ),
                        ),
                      ),
                  ],
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

class _InfoCard extends StatelessWidget {
  const _InfoCard({required this.message, required this.icon});

  final String message;
  final IconData icon;

  @override
  Widget build(BuildContext context) {
    return Card(
      child: Padding(
        padding: const EdgeInsets.all(16),
        child: Row(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Icon(icon),
            const SizedBox(width: 12),
            Expanded(child: Text(message)),
          ],
        ),
      ),
    );
  }
}
