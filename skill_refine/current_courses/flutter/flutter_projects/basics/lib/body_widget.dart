import 'package:flutter/material.dart';
import 'package:basics/dice_roller.dart';

// 바디 컨테이너 데코레이션 그라데이션 시작, 끝 위치 설정 변수
const Alignment decoStartAlignment = Alignment.topCenter;
const Alignment decoEndAlignment = Alignment.bottomCenter;

// 스캐폴드 바디 전용 커스텀 위젯 클래스
class BodyWidget extends StatelessWidget {
  final List<Color> colorList;
  const BodyWidget({super.key, required this.colorList});
  const BodyWidget.basic({super.key})
    : colorList = const [Colors.indigo, Colors.pinkAccent];

  @override
  Widget build(BuildContext context) {
    return Container(
      // container 속성중 상자(혹은 circle)의 그라데이션 설정 가능함
      decoration: BoxDecoration(
        gradient: LinearGradient(
          colors: colorList,
          begin: decoStartAlignment,
          end: decoEndAlignment,
        ),
      ),
      child: Center(child: DiceRoller()),
    );
  }
}
