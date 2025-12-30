import 'package:flutter/material.dart';
import 'package:lotto/app_theme.dart';

// 초기 화면임. 현재 단순구조.(환영메세지, 생성버튼)

class WelcomeScreen extends StatelessWidget {
  final void Function() goToLogicScreen;

  const WelcomeScreen({super.key, required this.goToLogicScreen});

  @override
  Widget build(BuildContext context) {
    return Center(
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          AppTheme.customText("Welcome to Lotto Generator", 17, Colors.white),
          SizedBox(height: 50),
          AppTheme.customButton(
            text: "Start Generate",
            callBack: goToLogicScreen,
          ),
        ],
      ),
    );
  }
}
