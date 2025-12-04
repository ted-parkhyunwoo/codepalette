
void main(List<String> args) {

  print("----인터페이스,구현체 테스트----");
  MyInterface interfaceClass = MyImplementClass();
  interfaceClass.sayHello();
  interfaceClass.sayBye();


  // 다른 언어에서는 안되는데 이상함. 같은 파일 내에서만 사용가능 추정(다른파일이 아닌 다른 패키지로 import시 사용 불가로 추정)
  MyInterface interfaceClass2 = MyInterface();
  interfaceClass2.sayHello();
  interfaceClass2.sayBye();
}




// 맘대로작성됨. 

interface class MyInterface{
  void sayHello() { print("NULL"); }
  void sayBye() { print("NULL"); }
}

class MyImplementClass implements MyInterface {
  void sayHello() {
    print("hi");
  }
  void sayBye() {
    print("bye");
  }
}
