import 'dart:math';

final Random random = Random();

class LottoLogic {
  List<int> get randomSixDigits {
    final List<int> nums = List.generate(45, (i) => i + 1);
    nums.shuffle();

    final List<int> result = nums.sublist(0, 6);
    result.sort();

    return result;
  }
}
