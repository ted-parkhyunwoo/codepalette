import 'package:flutter/material.dart';

class StartScreen extends StatelessWidget {
  const StartScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: BoxDecoration(
        gradient: LinearGradient(
          colors: [
            const Color.fromARGB(255, 78, 19, 181),
            const Color.fromARGB(255, 128, 105, 167),
          ],
          begin: Alignment.topLeft,
          end: Alignment.bottomRight,
        ),
      ),
      child: Center(
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            Image.asset("assets/images/quiz-logo.png", width: 300),
            Container(
              margin: EdgeInsets.fromLTRB(0, 80, 0, 30),
              child: const Text(
                "Learn Flutter the fun way!",
                style: TextStyle(color: Colors.white, fontSize: 24),
              ),
            ),
            OutlinedButton(
              onPressed: () {},
              style: OutlinedButton.styleFrom(foregroundColor: Colors.white),
              child: const Text("Start Quiz"),
            ),
          ],
        ),
      ),
    );
  }
}
