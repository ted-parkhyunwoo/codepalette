// import 'dart:io';
import 'package:flutter/material.dart';
import 'package:lotto/app_theme.dart';
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
            width: 40,
            height: 40,
            margin: EdgeInsets.all(8),
            child: Center(
              child: AppTheme.customText(digit.toString(), 18, Colors.black87),
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
          SizedBox(height: 30),

          ElevatedButton(
            style: ElevatedButton.styleFrom(fixedSize: Size(140, 10)),
            onPressed: restartGenerate,
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Icon(Icons.navigate_next, color: Colors.black54),
                AppTheme.customText("Generate", 14, Colors.black54),
              ],
            ),
          ),
          // TextButton(onPressed: () => exit(0), child: Text("EXIT")),
        ],
      ),
    );
  }
}
