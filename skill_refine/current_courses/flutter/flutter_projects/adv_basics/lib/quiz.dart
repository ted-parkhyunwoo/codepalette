import 'package:adv_basics/questions_screen.dart';
import 'package:flutter/material.dart';
import 'package:adv_basics/start_screen.dart';

class Quiz extends StatefulWidget {
  const Quiz({super.key});

  @override
  State<Quiz> createState() {
    return _QuizState();
  }
}

class _QuizState extends State<Quiz> {
  // main -> quiz -> start_screen or questions_screen 을 호출함.

  // 문제: 초기엔 start_screen을 띄우고, stateless widget인 start_screen 에서의 OutlinedButton버튼을 누르면 stateful widget인 quiz에서 question_screen으로 전환.

  // 내가 원하는 방식으로 작성. switchScreen을 start_screen의 버튼 onPressed로 넘기기 위해 매개변수로 넘김. 또한 late처리 (이 시점엔 switchScreen을 알 수 없기 때문.)
  late Widget activeScreen = StartScreen(switchScreen);

  /* late 대신 강의내용을 따르려면: (현재 코드에는 없지만 강의에 추가로 string형태로 activeScreen을 다루는 3항연산, build 내 if문으로 분기 등이 안내되었음.)
   initState()는 초기화블록 처럼 한번만 실행됨
   반대로 소멸자는 dispose()에 넣은경우 실행됨.
  */

  // Widget? activeScreen;
  // @override
  // void initState() {
  //   activeScreen = StartScreen(switchScreen);
  //   super.initState();
  //   // override했으니, 원본 초기화블록도 호출해야 하는듯.
  // }

  void switchScreen() {
    // 스크린을 바꾸는 코어. setState가 위젯 변동사항을 다시 그리도록 유도.
    setState(() => activeScreen = const QuestionsScreen()
    );
  }

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
