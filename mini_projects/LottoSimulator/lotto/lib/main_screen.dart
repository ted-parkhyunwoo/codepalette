import 'package:flutter/material.dart';
import 'package:lotto/app_theme.dart';
import 'package:lotto/logic_screen.dart';
import 'package:lotto/models/lotto_logic.dart';
import 'package:lotto/welcome_screen.dart';

// stateful 메인 스크린이며, 이곳에서 머테리얼, 스캐폴드 관리됨.
// 스캐폴드의 body 부분이 swapLogicScreen() 호출을 통해 기본 웰컴스크린에서 로직스크린으로 화면 변경되도록 유도함

class MainScreen extends StatefulWidget {
  const MainScreen({super.key});

  @override
  State<MainScreen> createState() => _MainScreenState();
}

class _MainScreenState extends State<MainScreen> {
  late Widget currentScreen = WelcomeScreen(goToLogicScreen: swapLogicScreen);
  final LottoLogic lottoLogic = LottoLogic();

  // 2차원 배열: 무작위 번호생성(6 * 5) 는 main_screen에서 관리.
  // LogicScreen 전환시 매개변수로 넘겨짐(getter를 이용해 런타임시마다 새로갱신하는 변수화)
  List<List<int>> get resultDigits {
    final List<List<int>> res = [];
    for (int i = 0; i < 5; ++i) {
      res.add(lottoLogic.randomSixDigits);
    }
    return res;
  }

  // 초기화면 전환 트리거
  void swapLogicScreen() {
    setState(
      () => currentScreen = LogicScreen(
        restartGenerate: swapLogicScreen, // 전환하자마자 초기에 한번은 생성하도록 유도
        resultDigits: resultDigits,
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          leading: Icon(Icons.calculate, color: Colors.white, size: 30),
          title: AppTheme.customText("Lotto Generator", 20, Colors.white),
          backgroundColor: Colors.blueGrey[700],
        ),
        body: currentScreen,
        backgroundColor: AppTheme.mainBackgroundColor,
      ),
    );
  }
}
