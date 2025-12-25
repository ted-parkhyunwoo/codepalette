import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

class QuestionsSummary extends StatelessWidget {
  final List<Map<String, Object>> summaryData;

  const QuestionsSummary({super.key, required this.summaryData});

  @override
  Widget build(BuildContext context) {
    const Color wrongColor = Color.fromARGB(230, 248, 82, 124);
    const Color rightColor = Color.fromARGB(230, 80, 189, 252);

    return SizedBox(
      //! 기기 세로 크기별로 사이즈 정하도록 변경함
      height: MediaQuery.of(context).size.height * 0.40,
      child: SingleChildScrollView(
        child: Column(
          children: summaryData.map((data) {
            return Row(
              crossAxisAlignment: CrossAxisAlignment.start, // 좌측문제버튼 상단정렬유도
              children: [
                //! 좌측 문제번호 원형 컬러표기
                Container(
                  // 정답/오답 별 컬러 원형 배치
                  padding: EdgeInsets.all(10),
                  decoration: BoxDecoration(
                    shape: BoxShape.circle,
                    color: (data['is_correctly'] == true)
                        ? rightColor
                        : wrongColor,
                  ),
                  // 문제번호 삽입
                  child: Text(
                    ((data['question_idx'] as int) + 1).toString(),
                    style: GoogleFonts.lato(
                      color: Colors.black87,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ),

                //! 번호, 결과텍스트모음 사이 공간
                SizedBox(width: 15),

                //! 결과 텍스트 모음
                Expanded(
                  child: Column(
                    crossAxisAlignment:
                        CrossAxisAlignment.start, // 텍스트모음 좌측정렬유도
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
                          color: wrongColor,
                          fontSize: 12,
                          fontWeight: FontWeight.w600,
                        ),
                      ),

                      // 맞는답변
                      Text(
                        data['correct_answer'] as String,
                        textAlign: TextAlign.left,
                        style: GoogleFonts.lato(
                          color: rightColor,
                          fontSize: 12,
                          fontWeight: FontWeight.w600,
                        ),
                      ),

                      // 문제간 공간
                      SizedBox(height: 7),
                    ],
                  ),
                ),
              ],
            );
          }).toList(),
        ),
      ),
    );
  }
}
