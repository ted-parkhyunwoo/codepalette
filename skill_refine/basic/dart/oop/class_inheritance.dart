import 'dart:io';

void main(List<String> args) {

  print(Child.pi);  // 인스턴스 생성 없이 사용 가능한 정적멤버변수(혹은 메서드). 
  Child.pi = 3.141592;
  Child.printPi();


  print("----상속 테스트----");
  Parent p = Parent("kim", 50);
  p.printStatus();

  Child c = Child(name: "park", age: 30);
  c.printStatus();

  // overide 된 메서드는 선언타입이 아니라, 인스턴스 타입 멤버를 따름.
  Parent test = new Child(name: "lee", age: 25);   // new키워드는 자유. 기능 동일
  test.printStatus();
  
  // 하지만 Parent로 선언되고 Child 로 할당된 test는 추가구현된 sayHello()를 쓸 수 없음.
  // test.sayHello();

  c.sayHello();

}


class Parent {
  final String name;
  int age;

  Parent(this.name, this.age){}
  Parent.empty() : this.name = "", this.age = 0;

  void printStatus() {
    print("name: $name, age: $age");
  }
}


class Child extends Parent {
  
  // 정적멤버 변수
  static double pi = 3.14;

  Child({ required String name, required int age}) : super(name, age);

  // 오버라이드: 안해도 작동은 정상으로 됨. 명시용.
  @override
  void printStatus() {
    stdout.write("CHILD ");
    super.printStatus();
  }

  // 기능추가
  void sayHello() {
    print("CHILD ${super.name} said: HELLO!");    // super로 명시해도 됨. (상속클래스이므로, this대신 super.)
  }

  // 정적 메서드.
  static void printPi(){
    print(pi);
  }
}

