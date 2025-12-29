import 'package:flutter/material.dart';
import 'package:lotto/logic_screen.dart';
import 'package:lotto/models/lotto_logic.dart';
import 'package:lotto/welcome_screen.dart';

class MainScreen extends StatefulWidget {
  const MainScreen({super.key});

  @override
  State<MainScreen> createState() => _MainScreenState();
}

class _MainScreenState extends State<MainScreen> {
  late Widget currentScreen = WelcomeScreen(goToLogicScreen: swapLogicScreen);
  final LottoLogic lottoLogic = LottoLogic();

  void swapLogicScreen() {
    setState(
      () => currentScreen = LogicScreen(restartGenerate: swapLogicScreen),
    );
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(home: Scaffold(body: currentScreen, backgroundColor: Colors.blueGrey,));
  }
}
