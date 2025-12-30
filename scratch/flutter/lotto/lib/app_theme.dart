import 'package:flutter/material.dart';

class AppTheme {
  static final mainBackgroundColor = Colors.blueGrey;

  // 커스텀 텍스트
  static Widget customText(String text, double size, Color color) => Text(
    text,
    style: TextStyle(fontSize: size, color: color),
  );

  // 커스텀 버튼
  static Widget customButton({
    required String text, // 표시될 글자
    required VoidCallback callBack, // 함수연결
    IconData? icon, // 아이콘 연결(비워지면 표시안되게 작성)
  }) {
    return ElevatedButton(
      style: ElevatedButton.styleFrom(
        minimumSize: Size(0, 35),
        backgroundColor: Colors.white,
      ),
      onPressed: callBack,
      child: Row(
        mainAxisAlignment: MainAxisAlignment.center,
        mainAxisSize: MainAxisSize.min,
        children: [
          if (icon != null) Icon(icon, color: Colors.black54),
          AppTheme.customText(text, 14, Colors.black54),
        ],
      ),
    );
  }
}
