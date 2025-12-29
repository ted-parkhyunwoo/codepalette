import 'package:adv_basics/data/questions.dart';
import 'package:adv_basics/questions_summary/questions_summary.dart';
import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

// questions_screen 의 전체 래퍼 클래스.
// 퀴즈결과창 상단메세지(몇문제 맞췄는지), questions_summary, 재시작 버튼 3가지로 나누어짐
// 추가로, 골라진 답변들의 String을 토대로 summary할 Map<String, Object> 구성됨.

class ResultScreen extends StatelessWidget {
  final List<String> chosenAnswers;
  final void Function() restartQuiz;

  const ResultScreen({
    super.key,
    required this.chosenAnswers,
    required this.restartQuiz,
  });

  // 선택된 답변들의 List<String> chosenAnswers 을 토대로 맵핑
  // index, 질문String, 정답, 사용자답변, 정답여부를 Object타입으로 관리
  // Key 는 question_idx 처럼 String 기반으로 접근, value는 용도별로 로직 작성됨

  //! dart 문법: 멤버 메서드 getSummaryData() -> getter 사용으로 변경
  // 특징: 런타임에 결정될 변수 값을 지정할 수 있는 느낌으로 접근. (사용처는 그저 참조만 함)
  // 다른 언어는 메서드로 getter/setter를 사용하나, dart는 변수처럼 사용할 수 있음
  // 한번 정해진 변수는 변경되지 않으나 dart의 getter는 런타임에 결정됨.
  // 다른언어의 getter 메서드와 기능적으론 동일하나, dart의 getter는 메서드가 아니라 명백히 속성(멤버 변수) 임
  List<Map<String, Object>> get summaryData {
    final List<Map<String, Object>> summary = [];

    for (int i = 0; i < chosenAnswers.length; ++i) {
      summary.add({
        'question_idx': i,
        'question': questions[i].text,
        'correct_answer': questions[i].answers[0],
        'user_answer': chosenAnswers[i],
        'is_correctly': questions[i].answers[0] == chosenAnswers[i],
      });
    }

    return summary;
  }

  @override
  Widget build(BuildContext context) {
    //! getter 사용으로 인한 주석처리.
    // final summaryData = getSummaryData();
    // 상단 텍스트용 지역 변수처리: 정답갯수/모든문제갯수
    final int numTotalQuestions = questions.length;
    //! getter 사용으로 .으로 접근하며 참조만 할 뿐이고 필요시 연산은 getter가 그때 함
    //! dart 문법: 화살표 함수 처리.(이미 난 이렇게 작성함)
    final int numCorrectQuestions = summaryData
        .where((data) => data['user_answer'] == data['correct_answer'])
        .length;

    return SizedBox(
      width: double.infinity,
      child: Container(
        // 전체 마진이 과해서 40->35로 조정
        margin: const EdgeInsets.all(35),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // 상단 텍스트(몇문제 중 몇문제 맞췄습니다 표기)
            Text(
              "You answered $numCorrectQuestions out of $numTotalQuestions questions correctly!",
              style: GoogleFonts.lato(
                textStyle: TextStyle(
                  color: const Color.fromARGB(206, 210, 157, 241),
                  fontSize: 20,
                ),
                fontWeight: FontWeight.bold,
              ),
              textAlign: TextAlign.center,
            ),
            SizedBox(height: 30),

            // 위젯 분리: questions_summary.dart
            QuestionsSummary(summaryData: summaryData),
            SizedBox(height: 30),

            // 화면 갱신버튼
            TextButton.icon(
              onPressed: restartQuiz,
              label: Text(
                "Restart Quiz!",
                style: GoogleFonts.lato(fontWeight: FontWeight.bold),
              ),
              icon: Icon(Icons.restart_alt_rounded),
              style: IconButton.styleFrom(
                foregroundColor: Colors.white,
                iconSize: 22,
              ),
            ),
          ],
        ),
      ),
    );
  }
}
