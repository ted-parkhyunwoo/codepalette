import 'package:adv_basics/questions_summary/questions_summary_number.dart';
import 'package:adv_basics/questions_summary/questions_summary_text.dart';
import 'package:flutter/material.dart';

class QuestionsSummary extends StatelessWidget {
  final List<Map<String, Object>> summaryData;

  const QuestionsSummary({super.key, required this.summaryData});

  @override
  Widget build(BuildContext context) {
    // 정답 오답 표기 색상 정의
    const List<Color> rightWrongColors = [
      Color.fromARGB(230, 80, 189, 252),
      Color.fromARGB(230, 248, 82, 124),
    ];

    return SizedBox(
      height:
          MediaQuery.of(context).size.height * 0.40, //! 디스플레이 크기별로 퍼센티지 높이 할당
      child: SingleChildScrollView(
        child: Column(
          children: summaryData.map((data) {
            return Row(
              crossAxisAlignment: CrossAxisAlignment.start, // 좌측문제버튼 상단정렬유도
              children: [
                QuestionsSummaryNumber(
                  data: data,
                  rightWrongColors: rightWrongColors,
                ), // 분리: 좌측 문제번호 원형 컬러표기
                SizedBox(width: 15), // 번호, 결과텍스트모음 사이 공간
                QuestionsSummaryText(
                  data: data,
                  rightWrongColors: rightWrongColors,
                ), // 분리: 결과 텍스트 모음
              ],
            );
          }).toList(),
        ),
      ),
    );
  }
}
