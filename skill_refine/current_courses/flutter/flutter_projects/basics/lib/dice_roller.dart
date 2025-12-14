import 'dart:math';

import 'package:flutter/material.dart';
import 'package:basics/styled_text.dart';

// 유동적인 위젯 예제. 두가지로 분리. stateful 위젯과 코어 상태 위젯

// 래퍼클래스는 statufull 을 상속
class DiceRoller extends StatefulWidget {
  const DiceRoller({super.key});

  @override
  State<DiceRoller> createState() {
    return _DiceRollerState();
  }
}

// 코어 클래스. extends에 유의하며 build는 똑같음. 특정 상태변경 함수에서 setState()를 사용해 상태를 변경. 또한 외부 상속금지클래스를 뜻하는 언더스코어처리
class _DiceRollerState extends State<DiceRoller> {
  final Random randomInstance = Random(); // 인스턴스 한번만 생성하도록 외부구현

  // late는 런타임에 결정되도록 유도
  late int currentDice = randomInstance.nextInt(6) + 1;

  // 상태변경의 코어멤버. setState를 활용
  void rollDice() {
    setState(() {
      currentDice = randomInstance.nextInt(6) + 1;
    });
  }

  @override
  Widget build(context) {
    return Column(
      mainAxisSize: MainAxisSize.min,
      children: [
        Image.asset('assets/images/dice/dice-$currentDice.png', width: 200),
        SizedBox(height: 30), // 더미 사이즈(패딩 대안)
        TextButton(
          onPressed: rollDice,
          style: TextButton.styleFrom(backgroundColor: Colors.deepPurple),
          child: StyledText("Roll Dice"),
        ),
      ],
    );
  }
}
