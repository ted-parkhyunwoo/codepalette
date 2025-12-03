import 'dart:io';

// dart 설치: flutter SDK 설치시 포함.
// debian: 바이너리 디렉토리를 PATH 추가(export PATH="$PATH:$HOME/flutter/flutter/bin")
// 인터프리터처럼 즉시 실행: dart 파일명.dart
// 컴파일: dart compile exe 파일명.dart -o 파일명.out

// class 의 사용
class Myclass {
  int a = 0;
  int b = 0;
  static int c = 3;   // 정적 멤버변수 사용
  
  // Myclass(this.a, this.b);   // 관용적 사용. 멤버변수 초기화 없이 사용 가능. 추천사용법.
  // 관용적 생성자를 사용하지 않고 전통적인 사용시 a, b초기값 할당 없이 선언만 할 수 없음. 
  // 만약 멤버변수 Nullable 예외하려면 int? a;, int? b; 로 사용
  Myclass(int a, int b){
    this.a = a;
    this.b = b;
  }

  // 멤버함수
  String getHello() {
    return "Hello";
  }

  // 정적 멤버 함수
  static void sayHello(String name) {
    print("Hello $name!!!");
  }
}


void main(List<String> args) {  // main함수의 관용표현.

  // 변수 선언과 사용
  var myFirstVar = "HelloWorld";  // 타입추론
  print(myFirstVar);              // 출력

  var myName = "ted";
  // 타입명시 가능
  String helloStr = "Hello $myName";  // 리터럴 삽입
  print(helloStr);
  // 상수선언
  const int A = 3;
  print("A: $A");                 // 리터럴 출력

  double pi = 3.14159265358979;   // float가 없다고 함.
  int piInt = pi.toInt();         // 형변환
  print("pi: $pi, piInt: $piInt");
  print("pi.6f: (%.6f): ${pi.toStringAsFixed(6)}");   // 실수 포맷팅

  print("진수표현:");
  int myHex = 0xFF;                 // 다른표기법 사용시 16진수만 허용.
  print(myHex);
  int myBin = int.parse("1010", radix: 2);    // 다른진수입력 int.parse(string, radix: 진수);
  print(myBin);
  print(myBin.toRadixString(16));       // 다른진수로 출력
  
  // 비트연산
  int binTen = 10;      // 1010
  int binFifteen = 15;  // 1111
  print((binTen ^ binFifteen).toRadixString(2));    // 1010 ^ 1111 = 0101
  print(binTen << 1);   // 101010 = 20;

  // 동적 타입: var는 추론이라 선언된 이후로 타입변경 불가, dynamic은 여러 자료형을 담을 수 있음.
  print("dynamic type: ");
  dynamic myDinamic = "string";
  print(myDinamic.runtimeType);
  myDinamic = 3;
  print(myDinamic.runtimeType);


  // 배열: int[] 나 int val[] 등은 없음.
  List<int> myArray = []; // [] 를 사용함
  myArray.add(1);         // 값 추가
  myArray.add(2);
  myArray.remove(2);      // 값기준 제거
  myArray.add(2);
  myArray.removeAt(1);    // index 기준 제거

  // 없는 값 제거 시도. 문제없이 실행
  myArray.remove(2);
  myArray.remove(2);
  myArray.remove(2);

  myArray[0] = 0;         // 값 수정

  // 배열 복합기능
  myArray.insert(0, -1);                // 요소 삽입 (위치, 요소)
  myArray.insertAll(1, [0, 1, 2, 1]);   // 배열 삽입 (위치, 삽입배열)
  print("배열길이: ${myArray.length}"); // 계산 필요한 리터럴 삽입
  myArray.replaceRange(0, 2, [9, 8]);   // 배열 수정 (위치, 길이, 대체배열)
  print(myArray);
  myArray.clear();                      // clear.
  print(myArray);

  myArray = [1, 2, 3];                  // 덮어쓰기

  // for-in 루프
  for (int e in myArray) 
    stdout.write(e);                    // 라인 변경없는 출력. import 'dart:io';
  print("");

  // 전통적인 for문 
  for (var i = 0; i < 10; ++i) 
    stdout.write('$i ');
  print("");

  // while문
  int j = 5;
  stdout.write("j: ");
  while (j > 0) {
    stdout.write("${--j}");             // 단항 증감연산
  }
  print("");

  // if 제어문
  if (5 < 3) {
    // pass
  } else if (5 < 4) {
    // pass
  } else {
    print("if문 else 도달");
  }


  // switch 제어문 : string 허용, //? dart는 break없이 작동하는듯
  switch ("안녕") {
    
    case "안": {
      // pass
      break;
    }
    case "녕": {
      // pass
      break;
    }
    case "안녕" :{
      stdout.write("break되지않고 pass됨\n");   // 도달
    }
    case "하세요" : {
      // 조건이 달라 도달하지않음
      stdout.write("다음 case도달\n");
    }
    default:  {
      // case에 도달했으므로 디폴트에 도달하지 않음
      print("switch문 default 도달\n");
    }
  }


  bool myBoolean = (1 < 3) ? true:  false;    // 삼항 연산(조건연산자)
  print(myBoolean);
  

  // static 키워드로 객체생성없이 호출(공통된 메모리공간 사전할당)
  // 클래스 정적변수
  print(Myclass.c);
  // 클래스 정적메서드 호출
  Myclass.sayHello("park");

  Myclass t = Myclass(1, 2);

  print(t.a);
  print(t.b);
  print(t.getHello());

  // Map
  Map<int, String> myMap = {};
  myMap[0] = "Hello";   //추가
  myMap[1] = "Dart";    
  myMap[1] = "World";   //수정
  myMap.remove(1);      //삭제
  myMap.addAll({5: "a", 6: "b"});   // 모두추가
  print(myMap);

  // map 요소순회

  // keys 를 이용한 for - in
  for (var key in myMap.keys) {
    print(myMap[key]);
  }

  // 내장 foreach
  myMap.forEach((k, v) {
    print("key: ${k}\tval:${v}");
  });

}