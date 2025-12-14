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
          // leading: Icon(Icons.star, color: Colors.white),
          title: Text("Random DICE", style: TextStyle(color: Colors.white)),
        ),

        body: BodyWidget.basic(),
      ),
    );
  }
}
