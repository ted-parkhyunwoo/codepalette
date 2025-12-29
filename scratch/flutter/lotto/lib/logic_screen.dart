// import 'dart:io';
import 'package:flutter/material.dart';
import 'package:lotto/models/lotto_logic.dart';

class LogicScreen extends StatelessWidget {
  final void Function() restartGenerate;
  LogicScreen({super.key, required this.restartGenerate});

  final LottoLogic lottoLogic = LottoLogic();

  List<int> get resultDigits => lottoLogic.randomSixDigits;

  String get resultString {
    return resultDigits.toString();
  }

  List<Widget> getNumsWidgets() {
    return resultDigits
        .map(
          (digit) => Container(
            decoration: BoxDecoration(
              color: Colors.greenAccent,
              shape: BoxShape.circle,
            ),
            width: 25,
            height: 25,
            margin: EdgeInsets.all(10),
            child: Center(
              child: Text(
                digit.toString(),
                textAlign: TextAlign.center,
                style: TextStyle(color: Colors.black),
              ),
            ),
          ),
        )
        .toList();
  }

  @override
  Widget build(BuildContext context) {
    return Center(
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,

        children: [
          // Text(resultString),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [...getNumsWidgets()],
          ),
          SizedBox(height: 20),

          TextButton(
            onPressed: restartGenerate,
            child: Text(
              "restart",
              style: TextStyle(color: Colors.lightBlueAccent),
            ),
          ),
          // TextButton(onPressed: () => exit(0), child: Text("EXIT")),
        ],
      ),
    );
  }
}
