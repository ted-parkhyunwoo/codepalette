import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:swim_android/main.dart';
import 'package:swim_android/theme/swim_colors.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  testWidgets('colors 99 percent OCR agreement as confirmed', (tester) async {
    late Color confirmedColor;
    late Color reviewColor;
    await tester.pumpWidget(
      MaterialApp(
        home: Builder(
          builder: (context) {
            confirmedColor = ocrAccuracyColor(context, 99);
            reviewColor = ocrAccuracyColor(context, 98.9);
            return const SizedBox.shrink();
          },
        ),
      ),
    );

    expect(confirmedColor, Colors.green.shade700);
    expect(reviewColor, Colors.orange.shade800);
  });

  testWidgets('shows analysis options below the calendar', (tester) async {
    SharedPreferences.setMockInitialValues({'swim_health_birth_year': 1990});
    await tester.pumpWidget(const SwimAndroidApp());

    expect(find.text('삼성 헬스 수영 기록'), findsOneWidget);
    expect(find.text('50m 풀장으로 분석'), findsNothing);
    expect(find.textContaining('월 요약'), findsOneWidget);
    await tester.drag(find.byType(ListView).first, const Offset(0, -900));
    await tester.pumpAndSettle();
    expect(find.text('일'), findsOneWidget);
    expect(find.text('토'), findsOneWidget);
  });

  testWidgets('asks for birth year on first launch and stores the answer', (
    tester,
  ) async {
    SharedPreferences.setMockInitialValues({});
    await tester.pumpWidget(const SwimAndroidApp());
    await tester.pumpAndSettle();

    expect(find.text('출생연도 입력'), findsOneWidget);
    await tester.enterText(find.byType(TextField).first, '1990');
    await tester.tap(find.text('저장'));
    await tester.pump();
    await tester.pump(const Duration(milliseconds: 500));

    final preferences = await SharedPreferences.getInstance();
    expect(preferences.getInt('swim_health_birth_year'), 1990);
    await tester.drag(find.byType(ListView).first, const Offset(0, -900));
    await tester.pump(const Duration(milliseconds: 300));
    expect(find.textContaining('심박 존 기준 최대심박수 약'), findsOneWidget);
    final birthYearField = find.byType(TextField).last;
    expect(tester.widget<TextField>(birthYearField).obscureText, isTrue);
    await tester.tap(find.byTooltip('출생연도 확인'));
    await tester.pump();
    expect(tester.widget<TextField>(birthYearField).obscureText, isFalse);
    await tester.tap(find.byTooltip('출생연도 가리기'));
    await tester.pump();
    expect(tester.widget<TextField>(birthYearField).obscureText, isTrue);
  });
}
