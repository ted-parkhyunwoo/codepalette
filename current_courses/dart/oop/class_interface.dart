
void main(List<String> args) {

  print("----인터페이스,구현체 테스트----");
  MyInterface interfaceClass = MyImplementClass("ted");
  interfaceClass.sayHello();
  interfaceClass.sayBye();
  interfaceClass.sayName();

  // 사용가능.
  MyInterface test = MyImplementClass("park");
  test.sayName();
}

// interface 키워드 사용은 되나, abstract로 선언해야 객체선언을 막음.(실질적인 인터페이스 느낌)
abstract class MyInterface {
  final String name;
  MyInterface(this.name);
  void sayHello() {}
  void sayBye() {}
  void sayName() {}
}

// 구현체: implements
class MyImplementClass implements MyInterface {
  final String name;
  MyImplementClass(this.name);

  void sayHello() {
    print("hi");
  }
  void sayBye() {
    print("bye");
  }
  void sayName() {
    print("My Name is ${this.name}");
  }
}
