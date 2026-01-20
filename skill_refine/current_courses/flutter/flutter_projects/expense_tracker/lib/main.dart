import 'package:flutter/material.dart';
import 'package:expense_tracker/widgets/expenses.dart';
import 'package:flutter/services.dart';

//! dart 관례: 전역변수는 k접두사를 붙인다 함
// ColorScheme() 로 지정하려면 꽤 많은것을 다 지정해야 하지만, fromSeed는 기본색상을 고르면 어느정도 틀을 만들어줌.
var kColorScheme = ColorScheme.fromSeed(seedColor: Colors.pink);
// 다크모드 사용 컬러스: 밝기 설정을 안바꿔주면, 기본 시드가 라이트모드용으로 생성됨
var kDarkColorScheme = ColorScheme.fromSeed(
  brightness: Brightness.dark,
  seedColor: Colors.pink,
);

void main() {
  // 세로고정을 사용하지 않고 가로모드/세로모드 별 UI를 다르게 조정할 것이므로 세로고정 주석처리

  //! 정확한 원리는 모르지만, SystemChrome 으로 방향을 세로고정 하려면 runApp이 바인딩 자동초기화 해주던 것을 이제는 직접 명시해서 초기화 해야한다고 함. 안하면 오류날 수 있으며, 나같은 경우는 앱 실행이 안됨
  // WidgetsFlutterBinding.ensureInitialized();

  // 세로고정. runApp부분이 then(fn {안에}) 들어감 services.dart 필요.
  // SystemChrome.setPreferredOrientations([
  //   DeviceOrientation.portraitUp,
  // ]).then((fn) {
  //  이곳에 runApp 전체를 붙여넣음
  // });

  runApp(
    MaterialApp(
      // darkTheme: ThemeData.dark(),  // 기본으로 사용시...
      darkTheme: ThemeData.dark().copyWith(
        colorScheme: kDarkColorScheme,
      ),
      theme: ThemeData().copyWith(
        // 기본테마 설정: 이것만 써도 전체적으로 바뀜. 이후는 직접 커스텀 지
        colorScheme: kColorScheme,

        //  앱바 테마
        appBarTheme: AppBarTheme().copyWith(
          backgroundColor: kColorScheme.onPrimaryContainer,
          foregroundColor: kColorScheme.primaryContainer,
        ),

        // Card테마: 강의와 다르게 CardTheme -> CardThemeData로 작성해야 정상작동
        cardTheme: CardThemeData().copyWith(
          color: kColorScheme.secondaryContainer,
          margin: EdgeInsets.symmetric(horizontal: 16, vertical: 8),
        ),

        // 버튼테마: + 버튼(새 가계부 추가) 후 Save Expense 의 배경색을 나타냄
        elevatedButtonTheme: ElevatedButtonThemeData(
          style: ElevatedButton.styleFrom(
            backgroundColor: kColorScheme.primaryContainer,
          ),
        ),

        // 텍스트테마:
        textTheme: ThemeData().textTheme.copyWith(
          // 타이틀텍스트: 이렇게 설정해도 AppBar의 텍스트(titleLarge지만) *색상* 만큼은 AppBar 테마를 우선 따름 - 우선순위를 고려할
          titleLarge: TextStyle(
            fontWeight: FontWeight.bold,
            // expense_item.dart의 일부 텍스트 테마 설정(Text style)을 titleLarge로 설정했으니, 그 텍스트는 이 theme 지침을 따름
            color: kColorScheme.onSecondaryContainer,
            fontSize: 16,
          ),

          // +@ 기본적인 텍스트
          // bodyMedium: TextStyle(
          //   color: kColorScheme.onPrimaryContainer,
          // ),
        ),
      ),
      // themeMode: ThemeMode.system,   // 기본값임.
      home: Expenses(),
    ),
  );
}
