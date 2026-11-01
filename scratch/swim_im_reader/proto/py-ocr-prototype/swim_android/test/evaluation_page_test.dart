import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:swim_android/models/swim_health_session.dart';
import 'package:swim_android/pages/evaluation_page.dart';
import 'package:swim_android/swim_analysis.dart';

void main() {
  testWidgets(
    'keeps only each stroke best at top while interval details expand',
    (tester) async {
      final session = SwimHealthSession.fromMap({
        'startTimeMillis': DateTime(2026, 10, 30, 7).millisecondsSinceEpoch,
        'exerciseType': 'POOL_SWIMMING',
        'durationSeconds': 158,
        'distanceMeters': 400,
        'calories': 300,
        'averageHeartRateBpm': 145,
        'maximumHeartRateBpm': 160,
        'poolLengthMeters': 25,
        'heartRateSamples': [
          _heartRate(DateTime(2026, 10, 30, 7, 0, 10), 130),
          _heartRate(DateTime(2026, 10, 30, 7, 0, 45), 140),
          _heartRate(DateTime(2026, 10, 30, 7, 0, 50), 150),
          _heartRate(DateTime(2026, 10, 30, 7, 1, 20), 160),
        ],
        'intervals': [
          _interval(40, 'FREESTYLE'),
          _interval(30, 'FREESTYLE'),
          _interval(32, 'BACKSTROKE'),
          _interval(36, 'BREASTSTROKE'),
        ],
      });

      await tester.pumpWidget(
        MaterialApp(
          home: EvaluationPage(
            session: session,
            occurrence: 1,
            inferIm100: false,
            excludePaceOutliers: true,
            finSwimmingIncluded: false,
            onSessionChanged: (_) async {},
          ),
        ),
      );

      expect(find.text('영법별 최고 기록'), findsOneWidget);
      expect(find.textContaining('실내수영'), findsOneWidget);
      expect(find.text('운동시간'), findsOneWidget);
      expect(find.text('전체 휴식 추정'), findsOneWidget);
      expect(find.text('평균 심박수'), findsOneWidget);
      expect(find.text('145 bpm'), findsOneWidget);
      expect(find.text('최고 심박수'), findsOneWidget);
      expect(find.text('160 bpm'), findsOneWidget);
      expect(find.text('0:20.0'), findsOneWidget);
      expect(find.text('2랩'), findsOneWidget);
      expect(find.text('3랩'), findsOneWidget);
      expect(find.text('4랩'), findsOneWidget);
      expect(find.text('1랩'), findsNothing);
      expect(find.text('0:40.0'), findsNothing);

      await tester.tap(find.text('펼쳐보기'));
      await tester.pumpAndSettle();

      expect(find.text('2랩'), findsOneWidget);
      expect(find.text('3랩'), findsOneWidget);
      expect(find.text('4랩'), findsOneWidget);
      expect(find.text('0:40.0'), findsOneWidget);
      expect(find.text('전체 휴식 추정'), findsOneWidget);
      expect(find.text('심박'), findsNothing);
      expect(find.text('130 bpm'), findsNothing);

      final bestLapTime = tester.widget<Text>(
        find.descendant(
          of: find.byType(DataTable),
          matching: find.text('0:30.0'),
        ),
      );
      expect(bestLapTime.style?.color, Colors.green.shade700);
    },
  );

  testWidgets('shows lap heart rate only after confirmed OCR rest analysis', (
    tester,
  ) async {
    final session = SwimHealthSession.fromMap({
      'startTimeMillis': DateTime(2026, 10, 30, 7).millisecondsSinceEpoch,
      'exerciseType': 'POOL_SWIMMING',
      'durationSeconds': 150,
      'distanceMeters': 100,
      'poolLengthMeters': 25,
      'averageHeartRateBpm': 140,
      'maximumHeartRateBpm': 150,
      'heartRateSamples': [
        _heartRate(DateTime(2026, 10, 30, 7, 0, 10), 130),
        _heartRate(DateTime(2026, 10, 30, 7, 0, 35), 140),
        _heartRate(DateTime(2026, 10, 30, 7, 0, 50), 150),
      ],
      'intervals': [
        _interval(30, 'BUTTERFLY'),
        _interval(32, 'BACKSTROKE'),
        _interval(35, 'BREASTSTROKE'),
        _interval(28, 'FREESTYLE'),
      ],
    }).withEditedRestSeconds([8, 5, 0, 0]);

    await tester.pumpWidget(
      MaterialApp(
        home: EvaluationPage(
          session: session,
          occurrence: 1,
          inferIm100: false,
          excludePaceOutliers: true,
          finSwimmingIncluded: false,
          onSessionChanged: (_) async {},
        ),
      ),
    );

    expect(find.textContaining('휴식구간 분석 완료'), findsOneWidget);
    expect(find.text('140 bpm'), findsOneWidget);
    expect(find.text('150 bpm'), findsWidgets);
    await tester.scrollUntilVisible(
      find.text('펼쳐보기'),
      300,
      scrollable: find.byType(Scrollable).first,
    );
    await tester.pumpAndSettle();
    await tester.tap(find.text('펼쳐보기'));
    await tester.pumpAndSettle();
    expect(find.text('심박'), findsOneWidget);
    expect(find.text('135 bpm'), findsOneWidget);
    expect(find.text('150 bpm'), findsWidgets);
    await tester.scrollUntilVisible(
      find.textContaining('혼영세션 1 ·'),
      300,
      scrollable: find.byType(Scrollable).first,
    );
    await tester.pumpAndSettle();
    expect(_findRichTextContaining('접영 (휴식: 8초)'), findsOneWidget);
    expect(_findRichTextContaining('배영 (휴식: 5초)'), findsOneWidget);
    expect(_findRichTextContaining('평영 (휴식:'), findsNothing);
  });

  testWidgets('shows saved per-lap heart rate without raw samples', (
    tester,
  ) async {
    final session =
        SwimHealthSession.fromMap({
          'startTimeMillis': DateTime(2026, 10, 30, 7).millisecondsSinceEpoch,
          'durationSeconds': 30,
          'intervals': [_interval(30, 'FREESTYLE')],
        }).withRestAnalysis(
          const SwimRestAnalysis(
            restSecondsByLap: [0],
            recognizedLapCount: 1,
            needsReview: false,
            averageHeartRateByLap: [138],
            maximumHeartRateByLap: [146],
          ),
        );

    await tester.pumpWidget(
      MaterialApp(
        home: EvaluationPage(
          session: session,
          occurrence: 1,
          inferIm100: false,
          excludePaceOutliers: true,
          finSwimmingIncluded: false,
          onSessionChanged: (_) async {},
        ),
      ),
    );

    await tester.scrollUntilVisible(
      find.text('펼쳐보기'),
      300,
      scrollable: find.byType(Scrollable).first,
    );
    await tester.pumpAndSettle();
    await tester.tap(find.text('펼쳐보기'));
    await tester.pumpAndSettle();
    expect(find.text('심박'), findsOneWidget);
    expect(find.text('138 bpm'), findsOneWidget);
  });

  testWidgets('hides lap heart rate when OCR analysis needs review', (
    tester,
  ) async {
    final startTime = DateTime(2026, 10, 30, 7);
    final session = SwimHealthSession.fromMap({
      'startTimeMillis': startTime.millisecondsSinceEpoch,
      'durationSeconds': 80,
      'intervals': [_interval(30, 'BUTTERFLY'), _interval(30, 'BACKSTROKE')],
      'heartRateSamples': [
        _heartRate(startTime.add(const Duration(seconds: 10)), 130),
        _heartRate(startTime.add(const Duration(seconds: 65)), 150),
      ],
    }).withOcrRestAnalysis(analyzeSwimText('1 접영 0:30'));

    await tester.pumpWidget(
      MaterialApp(
        home: EvaluationPage(
          session: session,
          occurrence: 1,
          inferIm100: false,
          excludePaceOutliers: true,
          finSwimmingIncluded: false,
          onSessionChanged: (_) async {},
        ),
      ),
    );

    await tester.tap(find.text('펼쳐보기'));
    await tester.pumpAndSettle();
    expect(find.text('심박'), findsNothing);
    expect(find.text('130 bpm'), findsNothing);
    expect(find.text('심박수 곡선'), findsNothing);
  });

  testWidgets('shows colored heart-rate curve only for analyzed sessions', (
    tester,
  ) async {
    final startTime = DateTime(2026, 10, 30, 7);
    final session = SwimHealthSession.fromMap({
      'startTimeMillis': startTime.millisecondsSinceEpoch,
      'durationSeconds': 60,
      'intervals': [_interval(60, 'FREESTYLE')],
      'heartRateSamples': [
        _heartRate(startTime.add(const Duration(seconds: 5)), 110),
        _heartRate(startTime.add(const Duration(seconds: 15)), 130),
        _heartRate(startTime.add(const Duration(seconds: 25)), 150),
        _heartRate(startTime.add(const Duration(seconds: 35)), 170),
        _heartRate(startTime.add(const Duration(seconds: 50)), 190),
      ],
    }).withEditedRestSeconds([0]);

    await tester.pumpWidget(
      MaterialApp(
        home: EvaluationPage(
          session: session,
          occurrence: 1,
          inferIm100: false,
          excludePaceOutliers: true,
          finSwimmingIncluded: false,
          maximumHeartRateBpm: 200,
          onSessionChanged: (_) async {},
        ),
      ),
    );

    expect(find.text('심박수 곡선'), findsOneWidget);
    for (var zone = 1; zone <= 5; zone++) {
      expect(find.textContaining('Zone$zone'), findsOneWidget);
    }
    expect(find.byType(CustomPaint), findsWidgets);
  });
}

Map<String, int> _heartRate(DateTime timestamp, int bpm) => {
  'timestampMillis': timestamp.millisecondsSinceEpoch,
  'heartRateBpm': bpm,
};

Finder _findRichTextContaining(String text) => find.byWidgetPredicate(
  (widget) => widget is RichText && widget.text.toPlainText().contains(text),
);

Map<String, Object> _interval(double durationSeconds, String strokeType) => {
  'durationSeconds': durationSeconds,
  'strokeType': strokeType,
  'strokeCount': 20,
};
