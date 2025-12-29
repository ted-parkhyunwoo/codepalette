import 'package:adv_basics/data/questions.dart';
import 'package:adv_basics/questions_screen/questions_screen.dart';
import 'package:adv_basics/result_screen.dart';
import 'package:flutter/material.dart';
import 'package:adv_basics/start_screen.dart';

// 앱의 코어 위젯(stateful)
// 크게 시작스크린, 문제풀이, 결과 출력으로 이어지며 결과출력->문제풀이로 되돌아갈 수 있음

class Quiz extends StatefulWidget {
  const Quiz({super.key});

  @override
  State<Quiz> createState() {
    return _QuizState();
  }
}

//! dart 문법: _로 private화.
class _QuizState extends State<Quiz> {
  // 마찬가지로 변수도 private처리 가능: 지역 메서드라는것을 명시하는 관례(외부접근 불가처리)
  final List<String> _selectedAnswers = [];

  //! 초기상태 처리: Widget? 로 선언하는 방식도 있지만, 개인적으로 late가 더 깔끔하여 이렇게 처리.
  late Widget activeScreen = StartScreen(startQuiz: switchScreen);

  // 초기상태 switchScreen -> QuizeScreen으로 전환(버튼클릭시)
  void switchScreen() {
    setState(
      () => activeScreen = QuestionsScreen(onSelectAnswer: chooseAnswer),
    );
  }

  // QuizeScreen에서 답변 선택시마다 selectedAnswers로 추가갱신하도록 하는 함수포인터
  // 모든 문제가 끝나면 ResultScreen으로 변경
  void chooseAnswer(String answer) {
    _selectedAnswers.add(answer);
    if (_selectedAnswers.length == questions.length) {
      setState(() {
        activeScreen = ResultScreen(
          chosenAnswers: _selectedAnswers,
          restartQuiz: restartQuiz,
        );
      });
    }
  }

  // QuestionScreen에서 restart 버튼 클릭시 재시작할 함수포인터
  // 클릭시 답변 기록을 지우고 다시 QuestionsScreen를 띄움
  void restartQuiz() {
    setState(() {
      _selectedAnswers.clear();
      activeScreen = QuestionsScreen(onSelectAnswer: chooseAnswer);
    });
  }

  // 전체적인 머테리얼앱 스캐폴드 스타일 지정. child를 setState로 갱신함
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        body: Container(
          decoration: BoxDecoration(
            gradient: LinearGradient(
              colors: const [
                Color.fromARGB(255, 78, 19, 181),
                Color.fromARGB(255, 128, 105, 167),
              ],
              begin: Alignment.topLeft,
              end: Alignment.bottomRight,
            ),
          ),
          child: activeScreen,
        ),
      ),
    );
  }
}
