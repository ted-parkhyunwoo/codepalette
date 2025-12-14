import 'package:flutter/material.dart';

class StyledText extends StatelessWidget {
  final String string;
  static const Color color = Colors.white;
  static const double size = 28;

  // 불변 객체임을 const로 명시
  const StyledText(this.string, {super.key});

  @override
  Widget build(BuildContext context) {
    return Text(
      string,
      style: TextStyle(color: color, fontSize: size),
    );
  }
}
