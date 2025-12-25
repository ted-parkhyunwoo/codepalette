import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

class QuestionsSummaryNumber extends StatelessWidget {
  final Map<String, Object> data;
  final List<Color> rightWrongColors;

  const QuestionsSummaryNumber({
    super.key,
    required this.data,
    required this.rightWrongColors,
  });

  @override
  Widget build(BuildContext context) {
    return Container(
      // 정답/오답 별 컬러 원형 배치
      padding: EdgeInsets.all(10),
      decoration: BoxDecoration(
        shape: BoxShape.circle,
        color: (data['is_correctly'] == true)
            ? rightWrongColors[0]
            : rightWrongColors[1],
      ),
      // 문제번호 삽입
      child: Text(
        ((data['question_idx'] as int) + 1).toString(),
        style: GoogleFonts.lato(
          color: Colors.black87,
          fontWeight: FontWeight.bold,
        ),
      ),
    );
  }
}
