import 'package:flutter/material.dart';

void main() {
  runApp(const Main());
}

class Main extends StatelessWidget {
  const Main({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(home: Scaffold(body: BodyWidget()));
  }
}

class BodyWidget extends StatelessWidget {
  const BodyWidget({super.key});

  @override
  Widget build(BuildContext context) {
    return Container(
      color: Colors.deepPurple,
      child: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Image.asset("assets/images/quiz-logo.png", width: 300),
            Container(
              margin: EdgeInsets.fromLTRB(0, 60, 0, 30),
              child: Text(
                "Learn Flutter the fun way!",
                style: TextStyle(color: Colors.white, fontSize: 20),
              ),
            ),
            OutlinedButton(
              onPressed: () {},
              style: OutlinedButton.styleFrom(
                side: BorderSide(color: Colors.black26),
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.all(Radius.circular(5.0)),
                ),
                foregroundColor: Colors.white,
              ),
              child: Text("Start Quiz"),
            ),
          ],
        ),
      ),
    );
  }
}
