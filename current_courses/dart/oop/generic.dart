void main(List<String> args){
  GenericTest t1 = GenericTest(1234, "ted");
  GenericTest t2 = GenericTest("1242", "ted");

  t1.setName = ["hello", "world"];  // 다시 반복하지만, setter는 특이하다.
  t1.setName = false;
  t1.printIdType();
  t2.printIdType();

  // java처럼 모든 객체는 Object 를 extends 함.
  Object t3 = GenericTest(true, "ted");
  // GenericTest로 캐스팅(t3는 현재 printIdType()을 못쓰는 상태)
  GenericTest<bool> casted = t3 as GenericTest<bool>;
  casted.printIdType();

  // 이로써 T1 은 다이나믹 타입으로 처리됨을 알 수 있다.
  print(t1.runtimeType);
  print(t2.runtimeType);
  print(t3.runtimeType);
  print(casted.runtimeType);


  // +@ 함수제네릭
  printType(3);
  printType(["1"]);
  printType(t3);
  printType(true);
  printType<int>(3);  // 타입명시가 생략된 추론이라고 보면 된다. std::vector처럼.

}

// class generic은 그냥 typedef 없이 T 등을 삽입(여러개 가능)
class GenericTest<T> {
  final T id;
  dynamic name;

  GenericTest(this.id, this.name);

  void printIdType() {
    print("id: ${id.runtimeType}, name: ${name.runtimeType}");
  }

  // dynamic으로 선언됐는데, T로도 사용 가능하다. T -> dynamic 추론 된다고 보면 쉬움
  set setName(T name) { this.name = name; }
}


// generic methods
void printType<T>(T val) {
  print(val.runtimeType);
}