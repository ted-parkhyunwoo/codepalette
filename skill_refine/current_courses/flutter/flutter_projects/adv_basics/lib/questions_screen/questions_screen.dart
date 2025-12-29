import 'package:flutter/material.dart';
import 'package:adv_basics/questions_screen/answer_button.dart';
import 'package:adv_basics/data/questions.dart';
import 'package:google_fonts/google_fonts.dart';

// start_screen 이후 스타트시 바로 연결되는 문제풀이 위젯
// data로 부터 models의 로직에 따라 답변을 뒤섞고, answer_button으로 할당하여 표기
// 답변 선택시마다 quiz.dart 의 selectedAnswers 로 갱신

class QuestionsScreen extends StatefulWidget {
  final void Function(String answer) onSelectAnswer;
  const QuestionsScreen({super.key, required this.onSelectAnswer});

  @override
  State<QuestionsScreen> createState() {
    return _QuestionScreen();
  }
}

class _QuestionScreen extends State<QuestionsScreen> {
  var currentQuestionIdx = 0;

  void answerQuestion(String selectedAnswer) {
    widget.onSelectAnswer(selectedAnswer);
    setState(() {
      currentQuestionIdx++;
    });
  }

  @override
  Widget build(BuildContext context) {
    final currentQuestion = questions[currentQuestionIdx];
    return SizedBox(
      width: double.infinity,
      child: Container(
        margin: EdgeInsets.all(40),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            // 질문 메세지. 설치: https://pub.dev/packages/google_fonts 폰트조회: https://fonts.google.com
            Text(
              currentQuestion.text,
              style: GoogleFonts.lato(
                textStyle: TextStyle(
                  color: const Color.fromARGB(206, 210, 157, 241),
                  fontSize: 24,
                ),
                fontWeight: FontWeight.bold,
              ),
              textAlign: TextAlign.center,
            ),

            // 질문 답변 갭
            SizedBox(height: 30),

            // 답변 버튼
            //! 질문 갯수가 같다면 문제없지만, data의 answers가 여러개일 경우를 대비한 패턴
            // 아래는 List이므로 스프레드 연산자 ...을 통해 Widget타입으로 수동 열거해야함
            // map() 만 쓰면 매개변수를 재가공한 리스트로 만듬.(String -> Widget)
            // +@ 버튼 갭 조절을 위해 Column으로 래핑하고 sizedbox 추가
            ...currentQuestion.shuffledAnswers.map((answer) {
              return Column(
                crossAxisAlignment: CrossAxisAlignment.stretch,
                children: [
                  AnswerButton(
                    answerText: answer,
                    onTap: () {
                      answerQuestion(answer);
                    },
                  ),
                  SizedBox(height: 5,)
                ],
              );
            }),
          ],
        ),
      ),
    );
  }
}
