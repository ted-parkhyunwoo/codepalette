import 'package:flutter/material.dart';
import 'package:lotto/app_theme.dart';
import 'package:lotto/models/digits_widget.dart';
import 'package:lotto/models/lotto_logic.dart';

// welcome_screen 다음으로 연결되는 코어 스크린.
// lotto_logic 에서 생성한 무작위 정수 6개 리스트를 main_screen로부터 생성자 매개변수로 받아
// 이곳에서 digits_widget 을 통해 위젯 리스트로 변환하여
// generate(재생성) 버튼 과 함께 출력

// 추가시도 할만한 사항: 현재화면 캡쳐 후 사진 저장버튼 (가능하면 Row 위젯으로 해야하나, 이러려면 뽑아놓은 번호 저장이 필요할듯)

class LogicScreen extends StatelessWidget {
  final void Function() restartGenerate;
  final List<List<int>> resultDigits; // 번호생성은 main_screen에서 관리함. 6*5 2차원배열
  LogicScreen({
    super.key,
    required this.restartGenerate,
    required this.resultDigits,
  });

  final LottoLogic lottoLogic = LottoLogic();

  // widgets 생성은 내부에서 관리함
  List<List<Widget>> get resultWidgets {
    List<List<Widget>> res = [];
    for (List<int> list in resultDigits) {
      res.add(DigitsWidget(list).widgetsList);
    }
    return res;
  }

  @override
  Widget build(BuildContext context) {
    return Center(
      child: SingleChildScrollView(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,

          children: [
            // +@ widget도 for문 지원함...
            for (List<Widget> wlist in resultWidgets)
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [...wlist],
              ),

            const SizedBox(height: 40), // 번호와 버튼간 공백

            AppTheme.customButton(
              text: "Generate",
              callBack: restartGenerate,
              icon: Icons.navigate_next,
            ),
          ],
        ),
      ),
    );
  }
}
