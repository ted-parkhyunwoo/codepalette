import 'package:flutter/material.dart';
import 'package:expense_tracker/widgets/expenses.dart';

// dart 관례: 전역변수는 k를 붙인다 함(사실확인 필요)
// ColorScheme() 로 지정하려면 꽤 많은것을 다 지정해야 하지만, fromSeed는 기본색상을 고르면 어느정도 틀을 만들어줌.
var kColorScheme = ColorScheme.fromSeed(seedColor: Colors.pink);

void main() {
  runApp(
    MaterialApp(
      theme: ThemeData().copyWith(
        // 기본테마 설정: 이것만으로도 미세하게 바뀜
        colorScheme: kColorScheme,
        //  앱바 테마
        appBarTheme: AppBarTheme().copyWith(
          backgroundColor: kColorScheme.onPrimaryContainer,
          foregroundColor: kColorScheme.primaryContainer,
        ),
        // Card의 테마: 강의와 다르게 CardTheme -> CardThemeData로 작성
        cardTheme: CardThemeData().copyWith(
          color: kColorScheme.secondaryContainer,
          margin: EdgeInsets.symmetric(horizontal: 16, vertical: 8),
        ),
        // + 버튼(새 가계부 추가) 후 Save Expense 의 배경색을 나타냄
        elevatedButtonTheme: ElevatedButtonThemeData(
          style: ElevatedButton.styleFrom(
            backgroundColor: kColorScheme.primaryContainer,
          ),
        ),

        // 텍스트설정
        textTheme: ThemeData().textTheme.copyWith(
          // 타이틀텍스트
          titleLarge: TextStyle(
            fontWeight: FontWeight.bold,
            //! 이렇게 설정해도 AppBar의 텍스트 *색상* 만큼은 AppBar의 색상테마를 우선 따름
            // expense_item.dart의 일부 텍스트 테마 설정을 titleLarge로 설정했으니, 그 텍스트는 이 theme 지침을 따름
            color: kColorScheme.onSecondaryContainer,
            fontSize: 16,
          ),

          // +@ 기본적인 텍스트
          // bodyMedium: TextStyle(
          //   color: kColorScheme.onPrimaryContainer,
          // ),
        ),
      ),

      home: Expenses(),
    ),
  );
}
