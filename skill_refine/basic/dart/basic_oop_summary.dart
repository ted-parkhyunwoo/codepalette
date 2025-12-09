// 라이브러리 호출
// ignore_for_file: unused_local_variable, unnecessary_type_check

import 'dart:ffi';
import 'dart:math';
import 'dart:io';


// 메인함수의 기본형식(c와 유사)
void main(List<String> args) {

  // 변수 타입
  var var1 = 3;       // 타입추론 가능
  dynamic var2 = 2;   // 동적타입 선언 가능
  var2 = "string";
  
  const double var3 = 3.141592;     // 나머진 비슷함.
  String var4 = "HelloWorld";
  final int var5 = 48327984;        //! const는 컴파일타임상수, final은 런타임상수

  // 없음. cffi 용이므로 나중에 추가서술 (drat:ffi, package:ffi/ffi.dart 등 필요)
  Uint8 var6;
  Char var7;


  // new는 생략 가능한 인스턴스생성
  Random random = Random(); 
  int randnum = random.nextInt(10);
  

  // 리터럴 출력방식 (js와 유사)
  String name = "park";
  print("안녕 내 이름은 $name. 단독 변수가 아닌경우 중괄호를 써야함 ${3 + 1}");
  stdout.write("한줄 출력은 import 'dart:io'; 가 필요\n"); 

  // 클래스 테스트
  MyClass test = new MyClass(2);      // 기본클래스.
  test.printAB();

  MyClass2 extended = MyClass2(3);    // 상속객체는 기능추가
  extended.printAB();
  print(extended + test);             //! + 연산자 오버로딩, toString 오버로딩


  //! 타입확인
  print(test.runtimeType);
  print(test is MyClass);


  // 다양한 함수 사용
  print(sum(1, 2));
  print( ((a, b) => a + b) (1, 2) );    // 즉시실행 램다 (화살표 표현)
  print( (a, b) {                       // 즉시실행 램다 (함수표현식)
    stdout.write("a + b = ");
    return a + b; 
    } (1, 2));
}


//! 함수선언의 여러 방식
Function sum = (a, b) => a + b;
int subs(int a, int b) => a - b;
int mul(int a, int b) { return a * b; }
int div(int a, int b) { return (a / b).toInt(); }


// class 정의
class MyClass {
  int a;  //! 엥간하면 nullable하게 하면 안됨
  int? b; //! nullable 강제하기. 이경우 생성자에서 뺄 수 있음
  final int c = 3;    // 멤버 정의시 할당된 경우에도 생성자에서 제외 가능

  //! 생성자는 다음처럼 쓰는 것이 관례.
  MyClass(this.a);

  void printAB() {
    b = 0;                // b가 초기화 되지 않아 예외발생하므로 추가
    print("$a, ${b!}");  //! 느낌표로 널이 아님을 명시가능
  }
}

class MyClass2 extends MyClass {
  // 멤버는 생략가능(abstract 클래스랑은 다르게도 생략가능)

  // 상속클래스의 생성자 형태. this대신 부모생성자 호출 이니셜라이저.
  MyClass2(super.a);        //! 이렇게 써도됨
  // MyClass2(int a) : super(a);

  //! 부모클래스의 함수 기능을 변조 오버라이딩
  @override
  void printAB() {
    b = 0;
    print("상속클래스에서 실행됨: $a, ${b!}");
  }

  //! cpp처럼 연산자오버로딩 됨
  MyClass2 operator +(MyClass obj) {
    return MyClass2(super.a + obj.a);
  }

  // Object 클래스의 toString 오버로딩
  @override
  String toString() {
    return "${super.a}";
  }
  
}