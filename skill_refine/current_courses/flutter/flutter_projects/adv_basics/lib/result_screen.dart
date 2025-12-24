import 'package:flutter/material.dart';
import 'package:adv_basics/data/questions.dart';

class ResultScreen extends StatelessWidget {
  final List<String> chosenAnswers;
  const ResultScreen({super.key, required this.chosenAnswers});

  List<Map<String, Object>> getSummaryData() {
    final List<Map<String, Object>> summary = [];

    for (int i = 0; i < chosenAnswers.length; ++i) {
      summary.add({
        'question_idx': 1,
        'question': questions[i].text,
        'correct_answer': questions[i].answers[0],
        'user_answer': chosenAnswers[i],
      });
    }

    return summary;
  }

  @override
  Widget build(BuildContext context) {
    return SizedBox(
      width: double.infinity,
      child: Container(
        margin: const EdgeInsets.all(40),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text("dummy"),
            SizedBox(height: 30),
            Text("List of answers and questions..."),
            SizedBox(height: 30),
            TextButton(onPressed: () {}, child: Text("Restart Quiz")),
          ],
        ),
      ),
    );
  }
}
