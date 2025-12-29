import 'package:flutter/material.dart';

class WelcomeScreen extends StatelessWidget {
  final void Function() goToLogicScreen;
  const WelcomeScreen({super.key, required this.goToLogicScreen});

  @override
  Widget build(BuildContext context) {
    return Center(
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          Text(
            "Welcome to Lotto Generator.",
            style: TextStyle(color: Colors.white),
          ),
          TextButton(onPressed: goToLogicScreen, child: Text("Next", style: TextStyle(color: Colors.lightBlueAccent),)),
        ],
      ),
    );
  }
}
