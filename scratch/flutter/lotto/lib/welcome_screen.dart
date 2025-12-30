import 'package:flutter/material.dart';
import 'package:lotto/app_theme.dart';

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
          ElevatedButton(
            style: ElevatedButton.styleFrom(fixedSize: Size(140, 10)),
            onPressed: goToLogicScreen,
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Icon(Icons.navigate_next, color: Colors.black54),
                AppTheme.customText("Generate", 14, Colors.black54),
              ],
            ),
          ),
        ],
      ),
    );
  }
}
