import 'package:flutter/material.dart';

class AppTheme {
  static final mainBackgroundColor = Colors.blueGrey;
  static final textColor = Colors.lightBlueAccent;

  static Widget defaultText(String text, double size) => Text(
    text,
    style: TextStyle(fontSize: size, color: textColor),
  );

  static Widget customText(String text, double size, Color color) => Text(
    text,
    style: TextStyle(fontSize: size, color: color),
  );
}
