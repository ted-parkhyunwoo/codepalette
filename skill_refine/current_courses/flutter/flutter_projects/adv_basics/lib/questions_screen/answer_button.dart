import 'package:flutter/material.dart';

class AnswerButton extends StatelessWidget {
  final String answerText;
  final void Function() onTap;
  const AnswerButton({
    super.key,
    required this.answerText,
    required this.onTap,
  });

  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
      child: ElevatedButton(
        onPressed: onTap,
        style: ElevatedButton.styleFrom(
          padding: EdgeInsets.symmetric(vertical: 10, horizontal: 20),
          backgroundColor: const Color.fromARGB(193, 58, 13, 116),
          foregroundColor: Colors.white,
          // 최근 플러터는 elevatedbutton이 다음과 같이 둥글게 이미 적용됨
          // shape: RoundedRectangleBorder(borderRadius: BorderRadiusGeometry.circular(40))
        ),
        child: Text(answerText, textAlign: TextAlign.center),
      ),
    );
  }
}
