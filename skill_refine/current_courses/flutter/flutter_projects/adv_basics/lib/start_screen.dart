import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

// 시작화면을 띄우고 start quiz 버튼을 배치하는 위젯

class StartScreen extends StatelessWidget {
  final void Function() startQuiz; // QuestionsScreen으로 연결시킬 트리거 함수 포인터
  const StartScreen({super.key, required this.startQuiz});

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
