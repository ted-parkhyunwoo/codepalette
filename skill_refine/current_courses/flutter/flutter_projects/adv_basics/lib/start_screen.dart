import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

class StartScreen extends StatelessWidget {
  // quiz의 switchScreen 을 startQuiz로 변수저장.
  final void Function() startQuiz;
  const StartScreen(this.startQuiz, {super.key});

  @override
  Widget build(BuildContext context) {
    return Center(
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
            child: Text(
              "Learn Flutter the fun way!",
              style: GoogleFonts.lato(
                textStyle: TextStyle(color: Colors.white, fontSize: 24),
              ),
            ),
          ),

          OutlinedButton.icon(
            onPressed: startQuiz,
            style: OutlinedButton.styleFrom(foregroundColor: Colors.white),
            icon: Icon(Icons.arrow_right_outlined),
            label: const Text("Start Quiz"),
          ),
        ],
      ),
    );
  }
}
