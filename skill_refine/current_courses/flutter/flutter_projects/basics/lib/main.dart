import 'package:flutter/material.dart';

void main() {
  runApp(MyApp());
}

List<Color> colorList = [Colors.indigo, Colors.pinkAccent];

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          backgroundColor: colorList[0],
          // leading: Icon(Icons.star, color: Colors.white),
          title: Text("Welcome", style: TextStyle(color: Colors.white)),
        ),

        body: BodyWidget(),

        bottomNavigationBar: BottomAppBar(
          height: 40,
          color: colorList[1],
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceAround,
            children: [
              Icon(Icons.add_circle, color: Colors.white),
              Icon(Icons.star, color: Colors.white),
              Icon(Icons.stop, color: Colors.white),
              Icon(Icons.play_arrow, color: Colors.white), 
              Icon(Icons.backspace_sharp, color: Colors.white),
            ],
          ),
        ),
      ),
    );
  }
}

// 스캐폴드 바디 전용 커스텀 위젯 클래스
class BodyWidget extends StatelessWidget {
  const BodyWidget({super.key});

  @override
  Widget build(BuildContext context) {
    return Container(
      // container 속성중 상자(혹은 circle)의 그라데이션 설정 가능함
      decoration: BoxDecoration(
        gradient: LinearGradient(
          colors: [colorList[0], colorList[1]],
          begin: Alignment.topCenter,
          end: Alignment.bottomCenter,
        ),
      ),
      child: Center(
        // center는 그냥 가운데 놓는 래퍼일 뿐이며, Text 속성은 style지정 가능
        child: Text(
          "Hello World!",
          style: TextStyle(color: Colors.white, fontSize: 28),
        ),
      ),
    );
  }
}
