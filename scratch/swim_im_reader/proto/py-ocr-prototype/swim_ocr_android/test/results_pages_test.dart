import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:swim_ocr_android/pages/results_pages.dart';
import 'package:swim_ocr_android/pages/upload_page.dart';
import 'package:swim_ocr_android/swim_data.dart';

void main() {
  testWidgets(
      'main screen exposes analysis checkboxes and default 25m pool',
      (tester) async {
    await tester.pumpWidget(
      const MaterialApp(home: UploadPage()),
    );

    expect(find.text('분석 옵션'), findsOneWidget);
    expect(find.textContaining('Android 전용'), findsNothing);
    expect(find.text('IM100 추론 사용 안 함'), findsOneWidget);
    expect(find.text('오계측 의심 랩을 페이스에서 제외하지 않음'), findsOneWidget);
    final poolLengthOption = find.widgetWithText(
      CheckboxListTile,
      '50m 풀장으로 분석',
    );
    expect(poolLengthOption, findsOneWidget);
    expect(tester.widget<CheckboxListTile>(poolLengthOption).value,
        isFalse);
    expect(
      find.text('선택하지 않으면 기본 25m 풀장으로 분석합니다.'),
      findsOneWidget,
    );
    await tester.tap(poolLengthOption);
    await tester.pumpAndSettle();
    expect(tester.widget<CheckboxListTile>(poolLengthOption).value,
        isTrue);
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

  testWidgets(
      'IM view names 100m and shows rests for each stroke transition',
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
    expect(find.text('1'), findsNWidgets(2));
    expect(find.text('1회'), findsNothing);
    expect(find.text('정상 인식'), findsOneWidget);
    expect(find.text('추정 구간'), findsOneWidget);
    expect(find.text('세션별 기록 (빠른순 정렬)'), findsOneWidget);
    expect(
      tester.getCenter(find.text('랩')).dx,
      greaterThan(tester.getCenter(find.text('영법별 기록')).dx),
    );
    expect(find.textContaining('접·배 0:05.0'), findsOneWidget);
    expect(find.textContaining('배·평 0:06.0'), findsOneWidget);
    expect(find.textContaining('평·자 0:07.0'), findsOneWidget);
    expect(find.textContaining('0:99.0'), findsNothing);
    expect(find.textContaining('접영 추정'), findsNothing);
    expect(find.textContaining('30.0 / 32.0'), findsOneWidget);
    expect(find.byType(Scrollbar), findsWidgets);
  });

  testWidgets(
      'all records view shows pool summary without distance column',
      (tester) async {
    final analysis =
        analyzeSwimText('구간(50m)\n1 자유형 0:30.0\n2 평영 0:35.0');

    await tester.pumpWidget(
      MaterialApp(home: AllRecordsPage(analysis: analysis)),
    );
    await tester.pumpAndSettle();

    expect(find.text('모든 기록'), findsOneWidget);
    expect(find.text('전체 기록'), findsNothing);
    expect(find.text('50m 풀 · 2랩 · 100m'), findsOneWidget);
    expect(find.text('거리'), findsNothing);
    expect(find.text('30.0'), findsOneWidget);
    expect(find.text('좌우로 밀어 보기'), findsNothing);
  });

  testWidgets(
      'stroke evaluation reports laps omitted from pace averages',
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

  testWidgets(
      'all records view retains the original outlier lap time',
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

  testWidgets(
      'all records highlights excluded and fastest paces in the table',
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

    final exclusionNote = tester.widget<Text>(
      find.byWidgetPredicate(
        (widget) =>
            widget is Text &&
            widget.textSpan?.toPlainText() ==
                '빨간색 기록은 페이스 계산에서 제외됩니다.',
      ),
    );
    final noteSpans = exclusionNote.textSpan! as TextSpan;
    expect((noteSpans.children!.first as TextSpan).style?.color,
        Colors.red);
    expect(noteSpans.children!.last.style?.color, isNull);
    final fastestNote = tester.widget<Text>(
      find.byWidgetPredicate(
        (widget) =>
            widget is Text &&
            widget.textSpan?.toPlainText() ==
                '초록색 기록은 영법별 최고 기록입니다.',
      ),
    );
    final fastestSpans = fastestNote.textSpan! as TextSpan;
    expect((fastestSpans.children!.first as TextSpan).style?.color,
        Colors.green);
    expect(fastestSpans.children!.last.style?.color, isNull);
    expect(find.text('100m 페이스'), findsOneWidget);

    final excludedColor = Colors.red;
    expect(
        tester.widget<Text>(find.text('9')).style?.color,
        Theme.of(tester.element(find.text('9')))
            .colorScheme
            .onSurface);
    expect(
        tester.widget<Text>(find.text('1:15.0').first).style?.color,
        excludedColor);
    expect(
        tester.widget<Text>(find.text('5:00.0').first).style?.color,
        Theme.of(tester.element(find.text('5:00.0').first))
            .colorScheme
            .onSurface);
    expect(
        tester
            .widget<Text>(find.text('자유', skipOffstage: false).last)
            .style
            ?.color,
        Colors.teal.shade800);
    expect(tester.widget<Text>(find.text('1')).style?.color,
        isNot(excludedColor));
    expect(find.text('0:40.0'), findsNWidgets(2));
    expect(
      tester.widget<Text>(find.text('0:10.0').first).style?.color,
      Colors.green,
    );
    expect(
      tester.widget<Text>(find.text('0:40.0').first).style?.color,
      Theme.of(tester.element(find.text('0:40.0').first))
          .colorScheme
          .onSurface,
    );
  });

  testWidgets(
      'inferred IM sessions do not expose OCR estimate wording',
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

    expect(find.textContaining('접영 추정'), findsNothing);
    expect(find.text('1'), findsOneWidget);
    expect(find.text('추정 구간'), findsOneWidget);
    expect(find.textContaining('1(추정)'), findsOneWidget);
  });

  testWidgets(
      'IM chart sorts by time while session table keeps source order',
      (tester) async {
    final analysis = analyzeSwimText(
      '1 접영 0:50.0\n'
      '2 배영 0:50.0\n'
      '3 평영 0:50.0\n'
      '4 자유형 0:50.0\n'
      '5 자유형 0:20.0\n'
      '6 배영 0:20.0\n'
      '7 평영 0:20.0\n'
      '8 자유형 0:20.0',
    );

    await tester.pumpWidget(
      MaterialApp(home: ImEvaluationPage(analysis: analysis)),
    );
    await tester.pumpAndSettle();

    expect(tester.getTopLeft(find.text('2').first).dx,
        lessThan(tester.getTopLeft(find.text('1').first).dx));
    expect(tester.getTopLeft(find.text('1').last).dy,
        lessThan(tester.getTopLeft(find.textContaining('2(추정)')).dy));
    expect(tester.getTopLeft(find.text('추정 구간')).dx,
        greaterThan(tester.getTopLeft(find.text('정상 인식')).dx));
  });

  testWidgets(
      'stroke evaluation sorts by pace with total first and matching colors',
      (tester) async {
    final analysis = analyzeSwimText(
      '1 자유형 0:10.0\n'
      '2 접영 0:30.0\n'
      '3 자유형 0:10.0\n'
      '4 접영 0:30.0\n'
      '5 접영 0:30.0',
    );

    await tester.pumpWidget(
      MaterialApp(home: StrokeEvaluationPage(analysis: analysis)),
    );
    await tester.pumpAndSettle();

    final butterfly = find.text('접영');
    final freestyle = find.text('자유');
    expect(tester.getTopLeft(freestyle.first).dx,
        lessThan(tester.getTopLeft(butterfly.first).dx));
    expect(tester.getTopLeft(freestyle.last).dy,
        lessThan(tester.getTopLeft(butterfly.last).dy));
    expect(tester.getTopLeft(find.text('전체')).dy,
        lessThan(tester.getTopLeft(freestyle.last).dy));

    expect(
      tester.widget<Text>(butterfly.at(0)).style?.color,
      tester.widget<Text>(butterfly.at(1)).style?.color,
    );
    expect(
      tester.widget<Text>(freestyle.at(0)).style?.color,
      tester.widget<Text>(freestyle.at(1)).style?.color,
    );
    expect(find.text('휴식 시간'), findsNothing);
    expect(find.text('0:00.0(0회)'), findsNWidgets(3));
  });

  testWidgets(
      'backstroke color matches in all records and stroke evaluation',
      (tester) async {
    final analysis = analyzeSwimText(
      '1 자유형 0:30.0\n'
      '2 배영 0:35.0\n'
      '3 자유형 0:32.0\n',
    );
    const expectedBackstrokeColor = Color(0xFF1976D2);

    await tester.pumpWidget(
      MaterialApp(home: AllRecordsPage(analysis: analysis)),
    );
    await tester.pumpAndSettle();
    expect(tester.widget<Text>(find.text('배영')).style?.color,
        expectedBackstrokeColor);

    await tester.pumpWidget(
      MaterialApp(home: StrokeEvaluationPage(analysis: analysis)),
    );
    await tester.pumpAndSettle();
    expect(tester.widget<Text>(find.text('배영').first).style?.color,
        expectedBackstrokeColor);
    expect(tester.widget<Text>(find.text('배영').last).style?.color,
        expectedBackstrokeColor);
  });
}
