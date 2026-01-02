import 'package:flutter/material.dart';

// 이 클래스는 정수형 리스트 (6개) 를 초기화 하면 widgetsList 멤버로 원 형태의 컬러 위젯 리스트를 뱉음.

class DigitsWidget {
  final List<int> digits;

  DigitsWidget(this.digits)
    : assert(digits.length == 6, "digits 가 6개의 정수가 아님 ");

  // 숫자 크기 별로 색상을 가져옴
  Color getColor(int digit) {
    if (digit <= 10) {
      return Colors.yellowAccent;
    } else if (digit <= 20) {
      return Colors.blueAccent;
    } else if (digit <= 30) {
      return Colors.redAccent;
    } else if (digit <= 40) {
      return Colors.grey;
    } else {
      return Colors.greenAccent;
    }
  }

  // 원 안에 들어갈 텍스트 스타일 지정
  Text getInnerText(int digit) {
    return Text(
      digit.toString(),
      style: TextStyle(
        fontWeight: FontWeight.bold,
        fontSize: 18,
        color: Colors.black87,
      ),
    );
  }

  List<Widget> get widgetsList {
    return digits
        .map(
          (digit) => Container(
            decoration: BoxDecoration(
              color: getColor(digit),
              shape: BoxShape.circle,
            ),
            width: 35,
            height: 35,
            margin: EdgeInsets.all(7),
            child: Center(child: getInnerText(digit)),
          ),
        )
        .toList();
  }
}
