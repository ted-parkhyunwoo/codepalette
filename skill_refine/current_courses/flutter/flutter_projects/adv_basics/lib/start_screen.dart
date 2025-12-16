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
            Image.asset(
              "assets/images/quiz-logo.png",
              width: 300,
              color: Colors.white54, // 권장되는 투명도 설정
            ),

            // 이미지 투명효과 방법1 (비권장): Opacity로 랩핑.
            // Opacity(
            //   opacity: .5,
            //   child: Image.asset("assets/images/quiz-logo.png", width: 300),
            // ),
            Container(
              margin: EdgeInsets.fromLTRB(0, 80, 0, 30),
              child: const Text(
                "Learn Flutter the fun way!",
                style: TextStyle(color: Colors.white, fontSize: 24),
              ),
            ),
            OutlinedButton.icon(
              onPressed: () {},
              style: OutlinedButton.styleFrom(foregroundColor: Colors.white),
              icon: Icon(Icons.arrow_right_outlined),
              label: const Text("Start Quiz"),
            ),
          ],
        ),
      ),
    );
  }
}
