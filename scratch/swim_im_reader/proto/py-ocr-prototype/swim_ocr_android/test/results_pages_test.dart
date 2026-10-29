import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:swim_ocr_android/pages/results_pages.dart';
import 'package:swim_ocr_android/pages/upload_page.dart';
import 'package:swim_ocr_android/swim_data.dart';

void main() {
  testWidgets('main screen exposes Android-only analysis checkboxes',
      (tester) async {
    await tester.pumpWidget(
      const MaterialApp(home: UploadPage()),
    );

    expect(find.text('분석 옵션 · Android 전용'), findsOneWidget);
    expect(find.text('IM100 추론 사용 안 함'), findsOneWidget);
    expect(find.text('오계측 의심 랩을 페이스에서 제외하지 않음'), findsOneWidget);
    final finSwimmingOption = find.widgetWithText(
      CheckboxListTile,
      '핀수영 포함',
    );
    expect(finSwimmingOption, findsOneWidget);
    expect(
      tester.widget<CheckboxListTile>(finSwimmingOption).value,
      isFalse,
    );
    await tester.tap(finSwimmingOption);
    await tester.pumpAndSettle();
    expect(
      tester.widget<CheckboxListTile>(finSwimmingOption).value,
      isTrue,
    );
  });

  testWidgets('IM view names 100m and shows rests for each stroke transition',
      (tester) async {
    final analysis = analyzeSwimText(
      '구간(25m)\n'
      '1 접영 0:30.0\n휴식 0:05.0\n'
      '2 배영 0:32.0\n휴식 0:06.0\n'
      '3 평영 0:35.0\n휴식 0:07.0\n'
      '4 자유형 0:28.0\n휴식 0:99.0',
    );

    await tester.pumpWidget(
      MaterialApp(home: ImEvaluationPage(analysis: analysis)),
    );
    await tester.pumpAndSettle();

    expect(find.text('IM 100 찾기'), findsOneWidget);
    expect(find.text('1회'), findsNWidgets(2));
    expect(find.textContaining('접·배 0:05.0'), findsOneWidget);
    expect(find.textContaining('배·평 0:06.0'), findsOneWidget);
    expect(find.textContaining('평·자 0:07.0'), findsOneWidget);
    expect(find.textContaining('0:99.0'), findsNothing);
    expect(find.text('좌우로 밀어 보기'), findsOneWidget);
  });

  testWidgets('all records view reports recognized laps and distance',
      (tester) async {
    final analysis = analyzeSwimText('구간(50m)\n1 자유형 0:30.0\n2 평영 0:35.0');

    await tester.pumpWidget(
      MaterialApp(home: AllRecordsPage(analysis: analysis)),
    );
    await tester.pumpAndSettle();

    expect(find.text('전체 기록'), findsOneWidget);
    expect(find.text('2랩 · 100m'), findsOneWidget);
    expect(find.text('좌우로 밀어 보기'), findsOneWidget);
  });

  testWidgets('stroke evaluation reports laps omitted from pace averages',
      (tester) async {
    final seconds = [10, 10, 30, 30, 30, 30, 30, 30, 75, 75, 75, 75];
    final analysis = analyzeSwimText(List.generate(
      seconds.length,
      (index) =>
          '${index + 1} 자유형 ${seconds[index] ~/ 60}:${(seconds[index] % 60).toString().padLeft(2, '0')}',
    ).join('\n'));

    await tester.pumpWidget(
      MaterialApp(home: StrokeEvaluationPage(analysis: analysis)),
    );
    await tester.pumpAndSettle();

    expect(
      find.textContaining('평균 페이스에서 4개 랩 (9랩, 10랩, 11랩, 12랩)을 제외'),
      findsOneWidget,
    );
    expect(find.text('1:15.0'), findsNothing);
  });

  testWidgets('all records view retains the original outlier lap time',
      (tester) async {
    final seconds = [10, 10, 30, 30, 30, 30, 30, 30, 75, 75, 75, 75];
    final analysis = analyzeSwimText(List.generate(
      seconds.length,
      (index) =>
          '${index + 1} 자유형 ${seconds[index] ~/ 60}:${(seconds[index] % 60).toString().padLeft(2, '0')}',
    ).join('\n'));

    await tester.pumpWidget(
      MaterialApp(home: AllRecordsPage(analysis: analysis)),
    );
    await tester.pumpAndSettle();

    expect(find.text('1:15.0'), findsNWidgets(4));
  });

  testWidgets('inferred IM sessions are identified as butterfly estimates',
      (tester) async {
    final analysis = analyzeSwimText(
      '1 자유형 0:30.0\n'
      '2 배영 0:32.0\n'
      '3 평영 0:35.0\n'
      '4 자유형 0:28.0',
    );

    await tester.pumpWidget(
      MaterialApp(home: ImEvaluationPage(analysis: analysis)),
    );
    await tester.pumpAndSettle();

    expect(find.textContaining('접영 추정'), findsWidgets);
  });
}
