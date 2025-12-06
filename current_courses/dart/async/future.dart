void main(List<String> args) async {
  
  // 변수저장
  Future<int> num = Future.value(1);
  Future str = Future.value("Hello");

  // 변수사용- then 콜백
  str.then((s){print("s완료: ${s}");});   // .then은 자료가 들어오면 실행할 체이닝이며 콜백매개변수로 값을 담음
  // 변수사용- await
  int numVar = await num;
  String strVar = await str;
  print(numVar);
  print(strVar);

  // Future 콜백: 다른연산부터 실행해버림 (start, end출력 -> res출력)
  addNum(1, 2);

  // 절차 컨트롤(후속 콜백의 절차를 제어) : await걸어놓은건 대기하며 다른연산이 시작됨. 메인에서도 await를 걸수 있음.
  await awaitAddNum(1, 2);      // 쉽게 말해서 await 가 끝날 때 까지 다음 코드를 진행하지 않음.
  print("랄랄라");
  print("하하하");
  await awaitAddNum(3, 4);

  int res = await getSum(await getSum(1, 1), await getSum(2, 2));
  print(res);

}


void addNum(int a, int b) {
  print("start $a + $b");

  // Future.delayed는 얼마나 기다릴지, 이어서 실행할 콜백 2개의 매개변수를 받음
  // Duration은 2초간 대기시킴
  Future.delayed(Duration(seconds: 2), (){ print("res: ${a + b}");});
  print("end $a + $b");
}


Future<void> awaitAddNum(int a, int b) async {
  print("await start $a + $b");

  // Future.delayed는 얼마나 기다릴지, 이어서 실행할 콜백 2개의 매개변수를 받음
  // Duration은 2초간 대기시킴
  await Future.delayed(Duration(seconds: 2), (){ print("await res: ${a + b}");});
  print("await end $a + $b");
}

Future<int> getSum(int a, int b) async {
  print("getSum start $a + $b");
  await Future.delayed(Duration(seconds: 2), (){ print("getSum res: ${a + b}");});
  print("getSum start $a + $b");
  return a + b;
}