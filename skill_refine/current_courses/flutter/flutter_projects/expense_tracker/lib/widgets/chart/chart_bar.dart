import 'package:flutter/material.dart';

class ChartBar extends StatelessWidget {
  const ChartBar({
    super.key,
    required this.fill,
  });

  final double fill;

  @override
  Widget build(BuildContext context) {
    //! 다크모드 여부 따지지 않게 조정되어 주석처리
    // final isDarkMode =
        // MediaQuery.of(context).platformBrightness == Brightness.dark;
    return Expanded(
      child: Padding(
        padding: const EdgeInsets.symmetric(horizontal: 4),
        child: FractionallySizedBox(
          // 0 ~ 1 까지의 double 로 높이를 설정하는 FractionallySizedBox의 속성
          heightFactor: fill,   
          child: DecoratedBox(
            decoration: BoxDecoration(
              shape: BoxShape.rectangle,
              borderRadius:
                  const BorderRadius.vertical(top: Radius.circular(8)),
              //! 차트막대 색상: 삼항연산 -> onSurface 통일 조정됨
              color: Theme.of(context).colorScheme.onSurface.withValues(alpha: 0.8),
                  
            ),
          ),
        ),
      ),
    );
  }
}
