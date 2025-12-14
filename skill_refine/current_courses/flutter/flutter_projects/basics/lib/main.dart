import 'package:flutter/material.dart';
import 'package:basics/body_widget.dart';

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
          title: Text(
            "DICE",
            style: TextStyle(color: Colors.white, fontSize: 20),
          ),
        ),

        body: BodyWidget.basic(),
      ),
    );
  }
}
