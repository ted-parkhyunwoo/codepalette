import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:swim_ocr_android/pages/results_pages.dart';
import 'package:swim_ocr_android/swim_data.dart';

void main() {
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
}
