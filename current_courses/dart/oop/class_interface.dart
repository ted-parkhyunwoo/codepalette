
void main(List<String> args) {

  print("----인터페이스,구현체 테스트----");
  MyImplementClass interfaceClass = MyImplementClass("ted");
  interfaceClass.sayHello();
  interfaceClass.sayBye();
  interfaceClass.sayName();

  // 사용가능: 인터페이스타입 선언, 구현체타입 할당.
  MyInterface test = MyImplementClass("park");
  test.sayName();

  // +@ 좀더 인터페이스와 가까운 설계
  const Creature human = Human("Ted", true);
  const Creature human2 = Human("Lee", false);

  human.introduce();
  human2.introduce();


}

// interface 키워드 사용은 되나, abstract로 선언해야 객체선언을 막음.(실질적인 인터페이스 느낌)
// interface 키워드의 역할은 자신 외 라이브러리에서의 구현 implements을 막음.(상속은 허용: extends)
// TODO: 접근제한자(public, protected, private) 가 없는 dart에선 이런 키워드들이 접근제한역할을 하는데, 키워드별로 어떤지 정확히 알아볼 필요가 있음.
abstract interface class MyInterface {
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


// 강의랑은 다른 사실 더 적절한 인터페이스(사실은 추상클래스)와 구현체:
abstract interface class Creature {   // abstract: 인스턴스 생성금지. interface: 외부 구현 금지
//! 인터페이스 키워드가 오히려 구현을 외부에서 막는다는건 좀 이상함. 사용자단 친화적 언어 의 보안관련 특성인듯.
  // 추상클래스(중 특히 인터페이스) 는 보통 멤버변수를 가지지 않음. (dart에서는 강제되진 않음)
  // final String name;
  // final bool isMale;

  // 인터페이스는 행동에 대한 밑그림만 가짐.
  String get getName;
  String get getGender;
  void introduce();
}


// 위 추상클래스의 행동, 데이터를 구체화 하는것은 구현체.
final class Human implements Creature { // final로 더이상 구현, 상속, with을 거부
  final String name;
  final bool isMale;

  const Human(this.name, this.isMale);

  // 행동들을 구현하지 않으면 오류.
  String get getName    { return this.name; }
  String get getGender  { return isMale? "Male" : "Female"; }
  void introduce() { print("name: ${this.getName}. gender: ${this.getGender}");}
}


