import 'dart:io';

import 'package:flutter/material.dart';
import 'package:image_picker/image_picker.dart';
import 'package:flutter/services.dart';
import 'package:shared_preferences/shared_preferences.dart';

import '../models/swim_health_session.dart';
import '../services/samsung_health_service.dart';
import '../services/swim_rest_ocr_service.dart';
import '../swim_analysis.dart';
import '../theme/swim_colors.dart';
import 'evaluation_page.dart';

class CalendarPage extends StatefulWidget {
  const CalendarPage({super.key});

  @override
  State<CalendarPage> createState() => _CalendarPageState();
}

class _CalendarPageState extends State<CalendarPage> {
  static const _pendingRestAnalysisKey =
      'swim_health_pending_rest_analysis_session';
  static const _birthYearKey = 'swim_health_birth_year';
  final _healthService = SamsungHealthService();
  final _imagePicker = ImagePicker();
  final _restOcrService = SwimRestOcrService();
  final _birthYearController = TextEditingController();
  final _today = DateTime.now();
  late DateTime _visibleMonth = DateTime(_today.year, _today.month);
  late DateTime _selectedDate = DateTime(_today.year, _today.month, _today.day);
  List<SwimHealthSession> _sessions = const [];
  bool _isLoading = false;
  bool _inferIm100 = true;
  bool _excludePaceOutliers = true;
  bool _finSwimmingIncluded = false;
  bool _isBirthYearVisible = false;
  int? _birthYear;
  DateTime? _lastWorkoutTime;
  bool _hasLoaded = false;
  String? _errorMessage;

  Future<void> _saveSession(SwimHealthSession session) async {
    await _healthService.saveSession(session);
    if (!mounted) return;
    setState(() {
      _sessions = [
        for (final existing in _sessions)
          if (existing.startTime == session.startTime) session else existing,
      ];
    });
  }

  Future<void> _setPendingRestAnalysis(DateTime? startTime) async {
    final preferences = await SharedPreferences.getInstance();
    final saved = startTime == null
        ? await preferences.remove(_pendingRestAnalysisKey)
        : await preferences.setInt(
            _pendingRestAnalysisKey,
            startTime.millisecondsSinceEpoch,
          );
    if (!saved) {
      throw StateError('휴식 분석 진행 상태를 저장하지 못했습니다.');
    }
  }

  @override
  void initState() {
    super.initState();
    _restoreAndSynchronize();
  }

  @override
  void dispose() {
    _birthYearController.dispose();
    super.dispose();
  }

  List<SwimHealthSession> get _selectedSessions {
    final selected = _sessions.where(
      (session) => _sameDay(session.startTime, _selectedDate),
    );
    return selected.toList()
      ..sort((first, second) => first.startTime.compareTo(second.startTime));
  }

  Future<void> _restoreAndSynchronize() async {
    await _loadBirthYear();
    try {
      final cached = await _healthService.readCachedSessions();
      if (!mounted) return;
      setState(() {
        _sessions = cached.sessions;
        _lastWorkoutTime = cached.lastWorkoutTime;
        _hasLoaded = cached.sessions.isNotEmpty;
      });
    } catch (error) {
      if (!mounted) return;
      setState(() {
        _errorMessage = '저장된 수영 기록을 읽지 못했습니다.\n$error';
      });
    }
    final recoveryError = await _restoreLostRestAnalysis();
    await _synchronizeSessions();
    if (recoveryError != null && mounted) {
      setState(() {
        _errorMessage = _errorMessage == null
            ? recoveryError
            : '$_errorMessage\n$recoveryError';
      });
    }
  }

  Future<void> _loadBirthYear() async {
    final preferences = await SharedPreferences.getInstance();
    final birthYear = preferences.getInt(_birthYearKey);
    if (!mounted) return;
    setState(() {
      _birthYear = birthYear;
      _birthYearController.text = birthYear?.toString() ?? '';
    });
    if (birthYear == null) {
      await WidgetsBinding.instance.endOfFrame;
      if (mounted) await _showBirthYearDialog();
    }
  }

  Future<void> _showBirthYearDialog() async {
    var hasError = false;
    await showDialog<void>(
      context: context,
      barrierDismissible: false,
      builder: (dialogContext) => StatefulBuilder(
        builder: (context, setDialogState) => AlertDialog(
          title: const Text('출생연도 입력'),
          content: TextField(
            controller: _birthYearController,
            autofocus: true,
            keyboardType: TextInputType.number,
            maxLength: 4,
            decoration: InputDecoration(
              labelText: '출생연도',
              hintText: '예: 1990',
              suffixText: '년',
              errorText: hasError ? '올바른 출생연도를 입력해 주세요.' : null,
            ),
          ),
          actions: [
            FilledButton(
              onPressed: () async {
                final saved = await _saveBirthYear(
                  _birthYearController.text,
                  showError: false,
                );
                if (!saved) {
                  setDialogState(() => hasError = true);
                } else if (dialogContext.mounted) {
                  Navigator.pop(dialogContext);
                }
              },
              child: const Text('저장'),
            ),
          ],
        ),
      ),
    );
  }

  Future<bool> _saveBirthYear(String text, {bool showError = true}) async {
    final birthYear = int.tryParse(text.trim());
    final currentYear = DateTime.now().year;
    if (birthYear == null || birthYear < 1900 || birthYear > currentYear) {
      if (showError && mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(content: Text('1900년부터 현재 연도까지의 출생연도를 입력해 주세요.')),
        );
      }
      return false;
    }
    final preferences = await SharedPreferences.getInstance();
    final saved = await preferences.setInt(_birthYearKey, birthYear);
    if (!saved) {
      throw StateError('출생연도를 저장하지 못했습니다.');
    }
    if (mounted) {
      setState(() => _birthYear = birthYear);
    }
    return true;
  }

  Future<String?> _restoreLostRestAnalysis() async {
    SharedPreferences? preferences;
    String? errorMessage;
    try {
      preferences = await SharedPreferences.getInstance();
      final pendingStartMillis = preferences.getInt(_pendingRestAnalysisKey);
      if (pendingStartMillis != null) {
        final response = await _imagePicker.retrieveLostData();
        final image = response.file;
        if (image == null) {
          if (!response.isEmpty) {
            throw response.exception ??
                const FormatException('선택한 사진을 복원하지 못했습니다.');
          }
        } else {
          final targetTime = DateTime.fromMillisecondsSinceEpoch(
            pendingStartMillis,
          );
          final matchingSessions = _sessions.where(
            (session) => session.startTime == targetTime,
          );
          if (matchingSessions.isEmpty) {
            throw StateError('사진을 분석할 운동 세션을 찾지 못했습니다.');
          }

          final session = matchingSessions.first;
          final analysis = await _restOcrService.analyze(
            File(image.path),
            poolLengthMeters: session.poolLengthMeters,
          );
          await _saveSession(session.withOcrRestAnalysis(analysis));
        }
      }
    } catch (error) {
      errorMessage = '중단된 휴식 분석을 복원하지 못했습니다.\n$error';
    }

    if (preferences != null) {
      try {
        final removed = await preferences.remove(_pendingRestAnalysisKey);
        if (!removed) {
          errorMessage = [
            ?errorMessage,
            '중단된 휴식 분석 상태를 정리하지 못했습니다.',
          ].join('\n');
        }
      } catch (error) {
        errorMessage = [
          ?errorMessage,
          '중단된 휴식 분석 상태를 정리하지 못했습니다.\n$error',
        ].join('\n');
      }
    }
    return errorMessage;
  }

  Future<void> _synchronizeSessions() async {
    setState(() {
      _isLoading = true;
      _errorMessage = null;
    });
    try {
      final cache = await _healthService.synchronizeSessions();
      if (!mounted) return;
      setState(() {
        _sessions = cache.sessions;
        _lastWorkoutTime = cache.lastWorkoutTime;
        _hasLoaded = true;
        _isLoading = false;
      });
    } catch (error) {
      if (!mounted) return;
      setState(() {
        _isLoading = false;
        _errorMessage = '삼성 헬스 기록을 불러오지 못했습니다.\n$error';
      });
    }
  }

  void _changeMonth(int monthDelta) {
    setState(() {
      _visibleMonth = DateTime(
        _visibleMonth.year,
        _visibleMonth.month + monthDelta,
      );
      _selectedDate = DateTime(_visibleMonth.year, _visibleMonth.month, 1);
    });
  }

  void _selectDate(DateTime date) {
    setState(() => _selectedDate = date);
  }

  @override
  Widget build(BuildContext context) {
    final selectedSessions = _selectedSessions;
    return Scaffold(
      appBar: AppBar(
        title: const Text(
          '수영 기록 달력',
          style: TextStyle(fontWeight: FontWeight.w800),
        ),
      ),
      body: ListView(
        padding: const EdgeInsets.fromLTRB(18, 8, 18, 30),
        children: [
          _WelcomeCard(
            isLoading: _isLoading,
            hasLoaded: _hasLoaded,
            sessionCount: _sessions.length,
            lastWorkoutTime: _lastWorkoutTime,
          ),
          if (_errorMessage case final message?) ...[
            const SizedBox(height: 14),
            _ErrorCard(message: message),
          ],
          const SizedBox(height: 14),
          _MonthlySummaryCard(month: _visibleMonth, sessions: _sessions),
          const SizedBox(height: 14),
          _CalendarCard(
            month: _visibleMonth,
            selectedDate: _selectedDate,
            sessions: _sessions,
            onMonthChanged: _changeMonth,
            onDateSelected: _selectDate,
          ),
          const SizedBox(height: 14),
          _AnalysisOptions(
            inferIm100: _inferIm100,
            excludePaceOutliers: _excludePaceOutliers,
            finSwimmingIncluded: _finSwimmingIncluded,
            birthYearController: _birthYearController,
            isBirthYearVisible: _isBirthYearVisible,
            maximumHeartRateBpm: _maximumHeartRateBpm,
            onInferIm100Changed: (value) => setState(() => _inferIm100 = value),
            onExcludePaceOutliersChanged: (value) =>
                setState(() => _excludePaceOutliers = value),
            onFinSwimmingIncludedChanged: (value) =>
                setState(() => _finSwimmingIncluded = value),
            onBirthYearVisibilityChanged: (value) =>
                setState(() => _isBirthYearVisible = value),
            onBirthYearSubmitted: _saveBirthYear,
          ),
          const SizedBox(height: 16),
          _SelectedDaySection(
            date: _selectedDate,
            sessions: selectedSessions,
            hasLoaded: _hasLoaded,
            inferIm100: _inferIm100,
            excludePaceOutliers: _excludePaceOutliers,
            finSwimmingIncluded: _finSwimmingIncluded,
            maximumHeartRateBpm: _maximumHeartRateBpm,
            onSessionChanged: _saveSession,
            onPendingRestAnalysisChanged: _setPendingRestAnalysis,
          ),
        ],
      ),
    );
  }

  int? get _maximumHeartRateBpm {
    final birthYear = _birthYear;
    if (birthYear == null) return null;
    final age = DateTime.now().year - birthYear;
    final estimate = 220 - age;
    return estimate > 0 ? estimate : null;
  }
}

class _WelcomeCard extends StatelessWidget {
  const _WelcomeCard({
    required this.isLoading,
    required this.hasLoaded,
    required this.sessionCount,
    required this.lastWorkoutTime,
  });

  final bool isLoading;
  final bool hasLoaded;
  final int sessionCount;
  final DateTime? lastWorkoutTime;

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;
    return Container(
      padding: const EdgeInsets.all(22),
      decoration: BoxDecoration(
        borderRadius: BorderRadius.circular(22),
        gradient: LinearGradient(
          colors: [colors.primary, colors.tertiary],
          begin: Alignment.topLeft,
          end: Alignment.bottomRight,
        ),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(
            '삼성 헬스 수영 기록',
            style: TextStyle(
              color: colors.onPrimary,
              fontSize: 22,
              fontWeight: FontWeight.w800,
            ),
          ),
          const SizedBox(height: 6),
          Text(
            hasLoaded
                ? '저장된 기록 $sessionCount개${lastWorkoutTime == null ? '' : ' · 마지막 운동 ${lastWorkoutTime!.year}.${lastWorkoutTime!.month.toString().padLeft(2, '0')}.${lastWorkoutTime!.day.toString().padLeft(2, '0')}'}'
                : '기록을 자동으로 동기화하고 기기에 저장합니다.',
            style: TextStyle(color: colors.onPrimary.withValues(alpha: 0.9)),
          ),
          const SizedBox(height: 18),
          Row(
            children: [
              if (isLoading)
                SizedBox(
                  width: 18,
                  height: 18,
                  child: CircularProgressIndicator(
                    strokeWidth: 2,
                    color: colors.onPrimary,
                  ),
                )
              else
                Icon(Icons.check_circle_outline, color: colors.onPrimary),
              const SizedBox(width: 8),
              Text(
                isLoading
                    ? (hasLoaded ? '새 운동 기록 확인 중' : '삼성 헬스에 처음 연결 중')
                    : (hasLoaded ? '자동 동기화 완료' : '동기화 대기 중'),
                style: TextStyle(
                  color: colors.onPrimary,
                  fontWeight: FontWeight.w700,
                ),
              ),
            ],
          ),
        ],
      ),
    );
  }
}

class _AnalysisOptions extends StatelessWidget {
  const _AnalysisOptions({
    required this.inferIm100,
    required this.excludePaceOutliers,
    required this.finSwimmingIncluded,
    required this.birthYearController,
    required this.isBirthYearVisible,
    required this.maximumHeartRateBpm,
    required this.onInferIm100Changed,
    required this.onExcludePaceOutliersChanged,
    required this.onFinSwimmingIncludedChanged,
    required this.onBirthYearVisibilityChanged,
    required this.onBirthYearSubmitted,
  });

  final bool inferIm100;
  final bool excludePaceOutliers;
  final bool finSwimmingIncluded;
  final TextEditingController birthYearController;
  final bool isBirthYearVisible;
  final int? maximumHeartRateBpm;
  final ValueChanged<bool> onInferIm100Changed;
  final ValueChanged<bool> onExcludePaceOutliersChanged;
  final ValueChanged<bool> onFinSwimmingIncludedChanged;
  final ValueChanged<bool> onBirthYearVisibilityChanged;
  final Future<bool> Function(String) onBirthYearSubmitted;

  @override
  Widget build(BuildContext context) => Card(
    child: Padding(
      padding: const EdgeInsets.symmetric(vertical: 8),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Padding(
            padding: const EdgeInsets.fromLTRB(16, 8, 16, 4),
            child: Text(
              '분석 옵션',
              style: Theme.of(context).textTheme.titleSmall
                  ?.copyWith(fontWeight: FontWeight.w800),
            ),
          ),
          CheckboxListTile(
            value: inferIm100,
            onChanged: (value) => onInferIm100Changed(value ?? false),
            title: const Text('자·배·평·자를 IM100으로 추정'),
            subtitle: const Text('접영 구간이 자유형으로 기록된 IM을 찾아냅니다.'),
            controlAffinity: ListTileControlAffinity.leading,
            dense: true,
          ),
          Padding(
            padding: const EdgeInsets.fromLTRB(16, 0, 16, 10),
            child: TextField(
              controller: birthYearController,
              obscureText: !isBirthYearVisible,
              keyboardType: TextInputType.number,
              maxLength: 4,
              textInputAction: TextInputAction.done,
              onSubmitted: onBirthYearSubmitted,
              decoration: InputDecoration(
                labelText: '출생연도',
                hintText: '예: 1990',
                suffixText: '년',
                helperText: maximumHeartRateBpm == null
                    ? '출생연도로 심박 존 기준을 계산합니다.'
                    : '심박 존 기준 최대심박수 약 $maximumHeartRateBpm bpm',
                counterText: '',
                suffixIcon: Row(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    IconButton(
                      tooltip: isBirthYearVisible ? '출생연도 가리기' : '출생연도 확인',
                      onPressed: () =>
                          onBirthYearVisibilityChanged(!isBirthYearVisible),
                      icon: Icon(
                        isBirthYearVisible
                            ? Icons.visibility_off_outlined
                            : Icons.visibility_outlined,
                      ),
                    ),
                    IconButton(
                      tooltip: '출생연도 저장',
                      onPressed: () =>
                          onBirthYearSubmitted(birthYearController.text),
                      icon: const Icon(Icons.check_circle_outline),
                    ),
                  ],
                ),
              ),
            ),
          ),
          CheckboxListTile(
            value: !excludePaceOutliers,
            onChanged: (value) =>
                onExcludePaceOutliersChanged(!(value ?? false)),
            title: const Text('오계측 의심 랩을 페이스에서 제외하지 않음'),
            subtitle: const Text('긴 랩 기록도 평균 페이스 계산에 포함합니다.'),
            controlAffinity: ListTileControlAffinity.leading,
            dense: true,
          ),
          CheckboxListTile(
            value: finSwimmingIncluded,
            onChanged: (value) => onFinSwimmingIncludedChanged(value ?? false),
            title: const Text('핀수영 포함'),
            subtitle: const Text('오계측 의심 랩 판정 기준을 완화합니다.'),
            controlAffinity: ListTileControlAffinity.leading,
            dense: true,
          ),
        ],
      ),
    ),
  );
}

class _MonthlySummaryCard extends StatelessWidget {
  const _MonthlySummaryCard({required this.month, required this.sessions});

  final DateTime month;
  final List<SwimHealthSession> sessions;

  @override
  Widget build(BuildContext context) {
    final monthSessions = sessions
        .where(
          (session) =>
              session.startTime.year == month.year &&
              session.startTime.month == month.month,
        )
        .toList();
    final totalDistance = monthSessions.fold<int>(
      0,
      (total, session) => total + session.distanceForSummaryMeters,
    );
    final totalLaps = monthSessions.fold<int>(
      0,
      (total, session) => total + session.intervals.length,
    );
    final totalDuration = monthSessions.fold<double>(
      0,
      (total, session) => total + session.durationSeconds,
    );
    final trainingDays = monthSessions
        .map(
          (session) => DateTime(
            session.startTime.year,
            session.startTime.month,
            session.startTime.day,
          ),
        )
        .toSet()
        .length;
    final firstOffset = DateTime(month.year, month.month).weekday % 7;
    final dayCount = DateTime(month.year, month.month + 1, 0).day;
    final weekCount = (firstOffset + dayCount + 6) ~/ 7;
    final weeks = List<int>.filled(weekCount, 0);
    for (final session in monthSessions) {
      final weekIndex = (firstOffset + session.startTime.day - 1) ~/ 7;
      weeks[weekIndex] += session.distanceForSummaryMeters;
    }
    final sessionsByStart = monthSessions
      ..sort((first, second) => first.startTime.compareTo(second.startTime));
    final occurrenceByDate = <DateTime, int>{};
    final occurrenceBySession = <SwimHealthSession, int>{};
    for (final session in sessionsByStart) {
      final date = DateTime(
        session.startTime.year,
        session.startTime.month,
        session.startTime.day,
      );
      final occurrence = (occurrenceByDate[date] ?? 0) + 1;
      occurrenceByDate[date] = occurrence;
      occurrenceBySession[session] = occurrence;
    }
    final longestSession = monthSessions.isEmpty
        ? null
        : monthSessions.reduce(
            (longest, session) =>
                session.distanceForSummaryMeters >
                    longest.distanceForSummaryMeters
                ? session
                : longest,
          );
    final totalCalories = monthSessions
        .where((session) => session.calories != null)
        .fold<double>(0, (total, session) => total + session.calories!);

    return Card(
      child: Padding(
        padding: const EdgeInsets.all(16),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text(
              '${month.year}년 ${month.month}월 요약',
              style: Theme.of(context).textTheme.titleMedium
                  ?.copyWith(fontWeight: FontWeight.w800),
            ),
            const SizedBox(height: 12),
            Wrap(
              spacing: 10,
              runSpacing: 10,
              children: [
                _MonthMetric(label: '총 거리', value: '${totalDistance}m'),
                _MonthMetric(label: '운동 횟수', value: '${monthSessions.length}회'),
                _MonthMetric(label: '총 랩', value: '$totalLaps랩'),
                _MonthMetric(label: '운동한 날', value: '$trainingDays일'),
                _MonthMetric(
                  label: '운동 시간',
                  value: formatDuration(totalDuration),
                ),
                _MonthMetric(
                  label: '회당 평균 거리',
                  value: monthSessions.isEmpty
                      ? '—'
                      : '${(totalDistance / monthSessions.length).round()}m',
                ),
                if (longestSession != null)
                  _MonthMetric(
                    label: '최장거리 세션',
                    value:
                        '${longestSession.startTime.day}일 '
                        '${occurrenceBySession[longestSession]}회차: '
                        '${longestSession.distanceForSummaryMeters}m',
                    width: 170,
                  ),
                if (monthSessions.any((session) => session.calories != null))
                  _MonthMetric(
                    label: '총 소모 칼로리',
                    value: '${totalCalories.round()} kcal',
                  ),
              ],
            ),
            const SizedBox(height: 18),
            Text(
              '주차별 거리',
              style: Theme.of(context).textTheme.labelLarge
                  ?.copyWith(fontWeight: FontWeight.w700),
            ),
            const SizedBox(height: 8),
            _WeeklyDistanceChart(values: weeks),
          ],
        ),
      ),
    );
  }
}

class _MonthMetric extends StatelessWidget {
  const _MonthMetric({
    required this.label,
    required this.value,
    this.width = 100,
  });

  final String label;
  final String value;
  final double width;

  @override
  Widget build(BuildContext context) => SizedBox(
    width: width,
    child: Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(
          label,
          style: TextStyle(
            color: Theme.of(context).colorScheme.onSurfaceVariant,
            fontSize: 11,
          ),
        ),
        const SizedBox(height: 2),
        Text(
          value,
          style: const TextStyle(fontSize: 15, fontWeight: FontWeight.w800),
        ),
      ],
    ),
  );
}

class _WeeklyDistanceChart extends StatelessWidget {
  const _WeeklyDistanceChart({required this.values});

  final List<int> values;

  @override
  Widget build(BuildContext context) {
    final maximum = values.fold<int>(
      0,
      (max, value) => value > max ? value : max,
    );
    final colors = Theme.of(context).colorScheme;
    final maxIndexes = maximum == 0
        ? <int>{}
        : {
            for (var index = 0; index < values.length; index++)
              if (values[index] == maximum) index,
          };
    return SizedBox(
      height: 104,
      child: Row(
        crossAxisAlignment: CrossAxisAlignment.end,
        children: [
          for (var index = 0; index < values.length; index++)
            Expanded(
              child: Padding(
                padding: const EdgeInsets.symmetric(horizontal: 4),
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.end,
                  children: [
                    Text(
                      '${values[index]}m',
                      style: TextStyle(
                        color: colors.onSurfaceVariant,
                        fontSize: 9,
                      ),
                      maxLines: 1,
                      overflow: TextOverflow.ellipsis,
                    ),
                    const SizedBox(height: 4),
                    Container(
                      height: maximum == 0
                          ? 4
                          : 58 * (values[index] / maximum).clamp(0.08, 1),
                      decoration: BoxDecoration(
                        color: maxIndexes.contains(index)
                            ? colors.primary
                            : colors.primary.withValues(alpha: 0.38),
                        borderRadius: const BorderRadius.vertical(
                          top: Radius.circular(6),
                        ),
                      ),
                    ),
                    const SizedBox(height: 5),
                    Text(
                      '${index + 1}주',
                      style: TextStyle(
                        color: colors.onSurfaceVariant,
                        fontSize: 10,
                      ),
                    ),
                  ],
                ),
              ),
            ),
        ],
      ),
    );
  }
}

class _CalendarCard extends StatelessWidget {
  const _CalendarCard({
    required this.month,
    required this.selectedDate,
    required this.sessions,
    required this.onMonthChanged,
    required this.onDateSelected,
  });

  final DateTime month;
  final DateTime selectedDate;
  final List<SwimHealthSession> sessions;
  final ValueChanged<int> onMonthChanged;
  final ValueChanged<DateTime> onDateSelected;

  @override
  Widget build(BuildContext context) {
    final counts = <DateTime, int>{};
    final dailyDistances = <DateTime, int>{};
    final dailySessions = <DateTime, List<SwimHealthSession>>{};
    for (final session in sessions) {
      final date = DateTime(
        session.startTime.year,
        session.startTime.month,
        session.startTime.day,
      );
      counts.update(date, (count) => count + 1, ifAbsent: () => 1);
      dailyDistances.update(
        date,
        (distance) => distance + session.distanceForSummaryMeters,
        ifAbsent: () => session.distanceForSummaryMeters,
      );
      dailySessions.putIfAbsent(date, () => []).add(session);
    }
    final firstDay = DateTime(month.year, month.month);
    final dayCount = DateTime(month.year, month.month + 1, 0).day;
    final colors = Theme.of(context).colorScheme;

    return Card(
      child: Padding(
        padding: const EdgeInsets.fromLTRB(12, 12, 12, 14),
        child: Column(
          children: [
            Row(
              children: [
                IconButton(
                  tooltip: '이전 달',
                  onPressed: () => onMonthChanged(-1),
                  icon: const Icon(Icons.chevron_left_rounded),
                ),
                Expanded(
                  child: Text(
                    '${month.year}년 ${month.month}월',
                    textAlign: TextAlign.center,
                    style: Theme.of(context).textTheme.titleMedium
                        ?.copyWith(fontWeight: FontWeight.w800),
                  ),
                ),
                IconButton(
                  tooltip: '다음 달',
                  onPressed: () => onMonthChanged(1),
                  icon: const Icon(Icons.chevron_right_rounded),
                ),
              ],
            ),
            const SizedBox(height: 4),
            Row(
              children: List.generate(7, (index) {
                const weekdays = ['일', '월', '화', '수', '목', '금', '토'];
                return Expanded(
                  child: Center(
                    child: Padding(
                      padding: const EdgeInsets.symmetric(vertical: 7),
                      child: Text(
                        weekdays[index],
                        style: TextStyle(
                          color: index == 0
                              ? calendarWeekendColor(context, DateTime.sunday)
                              : index == 6
                              ? calendarWeekendColor(context, DateTime.saturday)
                              : colors.onSurfaceVariant,
                          fontSize: 12,
                          fontWeight: FontWeight.w700,
                        ),
                      ),
                    ),
                  ),
                );
              }),
            ),
            GridView.builder(
              shrinkWrap: true,
              physics: const NeverScrollableScrollPhysics(),
              itemCount: 42,
              gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                crossAxisCount: 7,
                childAspectRatio: 0.92,
              ),
              itemBuilder: (context, index) {
                final day = index - (firstDay.weekday % 7) + 1;
                if (day < 1 || day > dayCount) {
                  return const SizedBox.shrink();
                }
                final date = DateTime(month.year, month.month, day);
                final count = counts[date] ?? 0;
                final dailyDistance = dailyDistances[date] ?? 0;
                final sessionsForDate = dailySessions[date] ?? const [];
                final isSelected = _sameDay(date, selectedDate);
                final weekendColor = calendarWeekendColor(
                  context,
                  date.weekday,
                );
                return Padding(
                  padding: const EdgeInsets.all(2),
                  child: InkWell(
                    borderRadius: BorderRadius.circular(12),
                    onTap: () => onDateSelected(date),
                    child: AnimatedContainer(
                      duration: const Duration(milliseconds: 150),
                      decoration: BoxDecoration(
                        color: isSelected ? colors.primaryContainer : null,
                        borderRadius: BorderRadius.circular(12),
                        border: isSelected
                            ? Border.all(color: colors.primary, width: 1.4)
                            : null,
                      ),
                      child: Semantics(
                        label: count == 0
                            ? '$day일'
                            : '$day일, ${dailyDistance}m, $count회 운동',
                        child: Column(
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: [
                            Text(
                              '$day',
                              style: TextStyle(
                                color: weekendColor,
                                fontWeight: isSelected || count > 0
                                    ? FontWeight.w800
                                    : FontWeight.w500,
                              ),
                            ),
                            const SizedBox(height: 1),
                            if (count > 0) ...[
                              Text(
                                '${dailyDistance}m',
                                maxLines: 1,
                                overflow: TextOverflow.ellipsis,
                                style: TextStyle(
                                  color: colors.onSurfaceVariant,
                                  fontSize: 8,
                                  height: 1.1,
                                ),
                              ),
                              const SizedBox(height: 2),
                              Wrap(
                                spacing: 2,
                                children: [
                                  for (
                                    var marker = 0;
                                    marker < sessionsForDate.length &&
                                        marker < 4;
                                    marker++
                                  )
                                    Container(
                                      width: 4,
                                      height: 4,
                                      decoration: BoxDecoration(
                                        shape: BoxShape.circle,
                                        color: restAnalysisStatusColor(
                                          context,
                                          analyzed:
                                              sessionsForDate[marker]
                                                  .restAnalysis !=
                                              null,
                                          needsReview:
                                              sessionsForDate[marker]
                                                  .restAnalysis
                                                  ?.needsReview ??
                                              false,
                                        ),
                                      ),
                                    ),
                                  if (count > 4)
                                    Text(
                                      '+${count - 4}',
                                      style: TextStyle(
                                        color: colors.onSurfaceVariant,
                                        fontSize: 7,
                                        height: 0.7,
                                      ),
                                    ),
                                ],
                              ),
                            ] else
                              const SizedBox(height: 10),
                          ],
                        ),
                      ),
                    ),
                  ),
                );
              },
            ),
          ],
        ),
      ),
    );
  }
}

class _SelectedDaySection extends StatelessWidget {
  const _SelectedDaySection({
    required this.date,
    required this.sessions,
    required this.hasLoaded,
    required this.inferIm100,
    required this.excludePaceOutliers,
    required this.finSwimmingIncluded,
    required this.maximumHeartRateBpm,
    required this.onSessionChanged,
    required this.onPendingRestAnalysisChanged,
  });

  final DateTime date;
  final List<SwimHealthSession> sessions;
  final bool hasLoaded;
  final bool inferIm100;
  final bool excludePaceOutliers;
  final bool finSwimmingIncluded;
  final int? maximumHeartRateBpm;
  final Future<void> Function(SwimHealthSession) onSessionChanged;
  final Future<void> Function(DateTime?) onPendingRestAnalysisChanged;

  @override
  Widget build(BuildContext context) {
    final dateLabel = '${date.year}년 ${date.month}월 ${date.day}일';
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Padding(
          padding: const EdgeInsets.fromLTRB(4, 0, 4, 10),
          child: Row(
            children: [
              Expanded(
                child: Text(
                  dateLabel,
                  style: Theme.of(context).textTheme.titleMedium
                      ?.copyWith(fontWeight: FontWeight.w800),
                ),
              ),
              if (sessions.isNotEmpty)
                Text(
                  '${sessions.length}개 세션',
                  style: TextStyle(
                    color: Theme.of(context).colorScheme.primary,
                    fontWeight: FontWeight.w700,
                  ),
                ),
            ],
          ),
        ),
        if (sessions.isEmpty)
          Card(
            child: Padding(
              padding: const EdgeInsets.all(18),
              child: Row(
                children: [
                  const Icon(Icons.event_busy_rounded),
                  const SizedBox(width: 12),
                  Expanded(
                    child: Text(
                      hasLoaded
                          ? '선택한 날짜에 수영 기록이 없습니다.'
                          : '삼성 헬스 기록을 불러온 뒤 날짜별 세션을 확인할 수 있습니다.',
                    ),
                  ),
                ],
              ),
            ),
          )
        else
          for (var index = 0; index < sessions.length; index++)
            _SessionCard(
              session: sessions[index],
              occurrence: index + 1,
              inferIm100: inferIm100,
              excludePaceOutliers: excludePaceOutliers,
              finSwimmingIncluded: finSwimmingIncluded,
              maximumHeartRateBpm: maximumHeartRateBpm,
              onSessionChanged: onSessionChanged,
              onPendingRestAnalysisChanged: onPendingRestAnalysisChanged,
            ),
      ],
    );
  }
}

class _SessionCard extends StatefulWidget {
  const _SessionCard({
    required this.session,
    required this.occurrence,
    required this.inferIm100,
    required this.excludePaceOutliers,
    required this.finSwimmingIncluded,
    required this.maximumHeartRateBpm,
    required this.onSessionChanged,
    required this.onPendingRestAnalysisChanged,
  });

  final SwimHealthSession session;
  final int occurrence;
  final bool inferIm100;
  final bool excludePaceOutliers;
  final bool finSwimmingIncluded;
  final int? maximumHeartRateBpm;
  final Future<void> Function(SwimHealthSession) onSessionChanged;
  final Future<void> Function(DateTime?) onPendingRestAnalysisChanged;

  @override
  State<_SessionCard> createState() => _SessionCardState();
}

class _SessionCardState extends State<_SessionCard> {
  final _picker = ImagePicker();
  final _ocrService = SwimRestOcrService();
  bool _isAnalyzing = false;

  Future<void> _analyzeRestFromScreenshot() async {
    if (_isAnalyzing) return;
    setState(() => _isAnalyzing = true);
    var pendingSessionRecorded = false;
    try {
      await widget.onPendingRestAnalysisChanged(widget.session.startTime);
      pendingSessionRecorded = true;
      final image = await _picker.pickImage(
        source: ImageSource.gallery,
        imageQuality: 100,
      );
      if (image == null || !mounted) return;
      final analysis = await _ocrService.analyze(
        File(image.path),
        poolLengthMeters: widget.session.poolLengthMeters,
      );
      final updated = widget.session.withOcrRestAnalysis(analysis);
      await widget.onSessionChanged(updated);
      if (!mounted) return;
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(
          content: Text(
            updated.restAnalysis!.needsReview
                ? '랩 수 또는 기록 차이가 큽니다. 주황색 표시를 확인해 주세요.'
                : '랩별 휴식 구간을 분석하고 저장했습니다.',
          ),
        ),
      );
    } catch (error) {
      if (!mounted) return;
      ScaffoldMessenger.of(
        context,
      ).showSnackBar(SnackBar(content: Text(_restAnalysisErrorMessage(error))));
    } finally {
      if (pendingSessionRecorded) {
        try {
          await widget.onPendingRestAnalysisChanged(null);
        } catch (error) {
          if (mounted) {
            ScaffoldMessenger.of(context).showSnackBar(
              SnackBar(content: Text('휴식 분석 상태를 저장하지 못했습니다.\n$error')),
            );
          }
        }
      }
      if (mounted) setState(() => _isAnalyzing = false);
    }
  }

  Future<void> _restoreOriginalRestData() async {
    final confirmed = await showDialog<bool>(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('원본 데이터로 복구'),
        content: const Text('이 세션의 OCR 휴식 분석 결과와 랩별 심박 추정을 삭제할까요?'),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(context, false),
            child: const Text('취소'),
          ),
          FilledButton(
            onPressed: () => Navigator.pop(context, true),
            child: const Text('복구'),
          ),
        ],
      ),
    );
    if (confirmed != true || !mounted) return;
    try {
      await widget.onSessionChanged(widget.session.withRestAnalysis(null));
      if (!mounted) return;
      ScaffoldMessenger.of(context)
          .showSnackBar(const SnackBar(content: Text('삼성 헬스 원본 데이터로 복구했습니다.')));
    } catch (error) {
      if (!mounted) return;
      ScaffoldMessenger.of(context)
          .showSnackBar(SnackBar(content: Text('원본 데이터로 복구하지 못했습니다.\n$error')));
    }
  }

  @override
  Widget build(BuildContext context) {
    final session = widget.session;
    final time = TimeOfDay.fromDateTime(session.startTime).format(context);
    final distance = session.distanceMeters == null
        ? '거리 정보 없음'
        : '${session.distanceMeters!.round()}m';
    final restAnalysis = session.restAnalysis;
    final statusColor = restAnalysis == null
        ? Theme.of(context).colorScheme.onSurface
        : restAnalysisStatusColor(
            context,
            analyzed: true,
            needsReview: restAnalysis.needsReview,
          );
    return Card(
      margin: const EdgeInsets.only(bottom: 7),
      child: ListTile(
        dense: true,
        minVerticalPadding: 2,
        visualDensity: const VisualDensity(vertical: -2),
        contentPadding: const EdgeInsets.symmetric(horizontal: 14, vertical: 1),
        title: Text(
          '${widget.occurrence}회차 · $time',
          style: TextStyle(fontWeight: FontWeight.w800, color: statusColor),
        ),
        subtitle: Text(
          '${session.displayExerciseType} · $distance · '
          '${formatDuration(session.durationSeconds)} · ${session.strokeCountSummary}'
          '${restAnalysis == null
              ? ''
              : restAnalysis.needsReview
              ? ' · 점검 필요'
              : ' · 휴식분석 완료'}',
        ),
        trailing: Row(
          mainAxisSize: MainAxisSize.min,
          children: [
            if (restAnalysis != null)
              IconButton(
                tooltip: '원본 데이터로 복구',
                onPressed: _isAnalyzing ? null : _restoreOriginalRestData,
                icon: const Icon(Icons.restore_rounded),
                color: Theme.of(context).colorScheme.onSurfaceVariant,
                visualDensity: VisualDensity.compact,
              ),
            OutlinedButton.icon(
              onPressed: _isAnalyzing ? null : _analyzeRestFromScreenshot,
              icon: _isAnalyzing
                  ? const SizedBox(
                      width: 14,
                      height: 14,
                      child: CircularProgressIndicator(strokeWidth: 2),
                    )
                  : const Icon(Icons.document_scanner_outlined, size: 16),
              label: Text(
                _isAnalyzing
                    ? '분석 중'
                    : restAnalysis == null
                    ? '휴식 분석'
                    : '재분석',
                style: const TextStyle(fontSize: 11),
              ),
              style: OutlinedButton.styleFrom(
                foregroundColor: restAnalysis == null
                    ? Theme.of(context).colorScheme.primary
                    : statusColor,
                visualDensity: VisualDensity.compact,
                padding: const EdgeInsets.symmetric(horizontal: 8),
              ),
            ),
          ],
        ),
        onTap: () => Navigator.of(context).push(
          MaterialPageRoute<void>(
            builder: (_) => EvaluationPage(
              session: session,
              occurrence: widget.occurrence,
              inferIm100: widget.inferIm100,
              excludePaceOutliers: widget.excludePaceOutliers,
              finSwimmingIncluded: widget.finSwimmingIncluded,
              maximumHeartRateBpm: widget.maximumHeartRateBpm,
              onSessionChanged: widget.onSessionChanged,
            ),
          ),
        ),
      ),
    );
  }
}

String _restAnalysisErrorMessage(Object error) {
  if (error is FileSystemException) {
    return '선택한 사진을 불러올 수 없습니다. 사진에 접근할 수 있는지 확인한 뒤 다시 선택해 주세요.\n$error';
  }
  if (error is FormatException) {
    return '사진에서 랩 기록을 읽을 수 없습니다. 삼성 헬스 랩 목록 화면이 선명하게 보이는 사진을 선택해 주세요.\n${error.message}';
  }
  if (error is PlatformException) {
    return switch (error.code) {
      'photo_access_denied' || 'camera_access_denied' =>
        '사진 접근 권한이 없어 불러오지 못했습니다. 권한을 허용한 뒤 다시 시도해 주세요.',
      _ =>
        '사진을 불러오거나 분석하지 못했습니다. 다른 사진으로 다시 시도해 주세요.\n${error.message ?? error.code}',
    };
  }
  return '사진을 불러오거나 분석하지 못했습니다. 다른 사진으로 다시 시도해 주세요.\n$error';
}

class _ErrorCard extends StatelessWidget {
  const _ErrorCard({required this.message});

  final String message;

  @override
  Widget build(BuildContext context) {
    return Card(
      color: Theme.of(context).colorScheme.errorContainer,
      child: Padding(
        padding: const EdgeInsets.all(16),
        child: Text(
          message,
          style: TextStyle(
            color: Theme.of(context).colorScheme.onErrorContainer,
          ),
        ),
      ),
    );
  }
}

bool _sameDay(DateTime first, DateTime second) =>
    first.year == second.year &&
    first.month == second.month &&
    first.day == second.day;
