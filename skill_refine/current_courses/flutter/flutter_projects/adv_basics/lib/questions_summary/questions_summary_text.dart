import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

class QuestionsSummaryText extends StatelessWidget {
  final Map<String, Object> data;
  final List<Color> rightWrongColors;

  const QuestionsSummaryText({
    super.key,
    required this.data,
    required this.rightWrongColors,
  });

  @override
  Widget build(BuildContext context) {
    return Expanded(
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start, // 텍스트모음 좌측정렬유도
        children: [
          // 문제
          Text(
            data['question'] as String,
            textAlign: TextAlign.left,
            style: GoogleFonts.lato(
              color: Colors.white,
              fontSize: 16,
              fontWeight: FontWeight.w700,
            ),
          ),

          // 문제와 답변 사이공간
          SizedBox(height: 3),

          // User답변
          Text(
            data['user_answer'] as String,
            textAlign: TextAlign.left,
            style: GoogleFonts.lato(
              color:  rightWrongColors[1],
              fontSize: 12,
              fontWeight: FontWeight.w600,
            ),
          ),

          // 맞는답변
          Text(
            data['correct_answer'] as String,
            textAlign: TextAlign.left,
            style: GoogleFonts.lato(
              color: rightWrongColors[0],
              fontSize: 12,
              fontWeight: FontWeight.w600,
            ),
          ),

          // 문제간 공간
          SizedBox(height: 7),
        ],
      ),
    );
  }
}
