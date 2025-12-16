void main(List<String> args) {

  // List요소로 if문을 쓸 수 있음...
  List<int> test = [1, 2, if (true) 3 else 4];
  // add 로는 안됨.
  // test.add(if (true) 4 else 5);
  print(test);

  // if 문으로 변수 정의 안됨. 3항연산 사용
  // int test2 = if (true) 1 else 2;
  int test2 = true? 1 : 2;


  // List 요소로 3항연산도 사용가능
  List<int>test3 = [true? 1: 2];
  // add 도 가능
  test3.add(true? 2: 3);
  print(test3);


}