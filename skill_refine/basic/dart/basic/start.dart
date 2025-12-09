// ignore_for_file: unnecessary_type_check

import 'dart:typed_data';
import 'dart:io';

// dart 설치: flutter SDK 설치시 포함.
// debian: 바이너리 디렉토리를 PATH 추가(export PATH="$PATH:$HOME/flutter/flutter/bin")
// 인터프리터처럼 즉시 실행: dart 파일명.dart
// 컴파일: dart compile exe 파일명.dart -o 파일명.out




void main(List<String> args) {  //! main함수의 관용표현.

  // 변수 선언과 사용
  print("\n변수선언과 사용:");
  var myFirstVar = "HelloWorld";  // 타입추론
  print(myFirstVar);              // 출력
  
  var myName = "ted";
  String helloStr = "Hello $myName";  // 리터럴 삽입
  print(helloStr);


  // 실수, 실수포매팅
  double pi = 3.14159265358979;   //! float가 없다고 함.
  print("pi.6f: (%.6f): ${pi.toStringAsFixed(6)}");
  

  //! 형변환(어떤 방향이든 명시해야함)
  print("\n형변환:");
  int piInt = pi.toInt();               // 소수점 이하 데이터 손상
  print("pi: $pi, piInt: $piInt");
  double piIntDouble = piInt.toDouble();   // 정보손상 우려 없는데도 명시해야함.
  print("piIntDouble: $piIntDouble");


  // 타입 확인은 is {type}
  print("\n타입확인: ");
  bool isInt = piInt is int;            //! 이렇게 사용할 것.
  bool isDouble = piIntDouble.runtimeType == 0.1.runtimeType; // 굳이 직접비교: String "double" 로는 안돼서 꼼수
  print("${isInt} ${isDouble}");


  // 상수선언
  print("\n상수: ");
  const int A = 3;                // 컴파일 타임 상수(자료형 int 생략시 타입 추론)
  print("A: $A");                 // 리터럴 출력

  final B = DateTime.now();       //! 런타임 상수: 한번만 런타임에 할당되면 변경불가.
  final DateTime C = DateTime.now();  // 런타임상수의 타입명시 (마찬가지로 생략시 타입 추론)
  print(B);
  print(C);


  // 시간 표현 상세화
  print("\n시간출력:");
  print('H: ${B.hour}, M: ${B.minute}, S: ${B.second}, MilliSecond: ${B.millisecond}, Microsecond: ${B.microsecond}');
  print(B.millisecondsSinceEpoch);    // 밀리초단위의 unixtime;
  print(B.microsecondsSinceEpoch);    // 마이크로초단위의 unixtime;


  // 진수전환
  print("\n진수표현:");
  int myHex = 0xFF;                 //! 다른표기법 사용시 16진수만 허용.
  print(myHex);
  int myBin = int.parse("1010", radix: 2);    // 다른진수입력 int.parse(string, radix: 진수);
  print(myBin);
  print(myBin.toRadixString(16));       // 다른진수로 출력
  

  // 비트연산
  print("\n비트연산:");
  int binTen = 10;      // 1010
  int binFifteen = 15;  // 1111
  print((binTen ^ binFifteen).toRadixString(2));    // 1010 ^ 1111 = 0101
  print(binTen << 1);   // 101010 = 20;


  //! 동적 타입: var는 추론이라 선언된 이후로 타입변경 불가, dynamic은 여러 자료형을 담을 수 있음.
  print("\ndynamic type: ");
  dynamic myDinamic = "string";
  print(myDinamic.runtimeType);
  myDinamic = 3;
  print(myDinamic.runtimeType);


  // nullable 에 관하여. 
  String? nullableStr = null; //! 원래 null로 선언될 수 없으나 ?를 붙이면 가능.
  print("\nnullable:");
  print(nullableStr);
  // print(nullableStr!);        //! 느낌표 !로 null이 아님을 명시함(null이라면 에러 나도록 표기하여 예외 처리 유도)
  // 예외없이 사용하는 ?.(null 반환), ?? (기본값 대체) 등의 안전한 다른방법들이 있다 함.
  nullableStr = nullableStr?? "NULL이여서 대체했습니다."; //! nullableStr ??= "문자열" 과 같은 동작
  print(nullableStr);


  // 배열: int[] 나 int val[] 등은 없음.
  print("\n배열:");
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
  int zeroIdx = myArray.indexOf(0);     // 인덱스 찾기   ->    0
  int twoIdx = myArray.indexOf(2);      // 없는값 찾기 시도    ->    -1
  print("zeroIdx: ${zeroIdx}\ttwoIdx: ${twoIdx}");

  myArray.insert(0, -1);                // 요소 삽입 (위치, 요소)
  myArray.insertAll(1, [0, 1, 2, 1]);   // 배열 삽입 (위치, 삽입배열)
  print("배열길이: ${myArray.length}"); // 계산 필요한 리터럴 삽입
  myArray.replaceRange(0, 2, [9, 8]);   // 배열 수정 (위치, 길이, 대체배열)
  print(myArray);
  myArray.clear();                      // clear.
  print(myArray);

  myArray = [1, 2, 3];                  // 덮어쓰기

  // 배열복사(setRange: 반복자기반, 자료형이 달라도 허용, sublist: 인덱스기반복사. 자료구조 다르면 사용안됨)
  print("\n배열복사: ");
  
  List<int> copyArray = List.filled(myArray.length, 0);       // 공간확보(이후 크기 변경불가) 안하면 복사 범위 예외발생
  copyArray.setRange(0, myArray.length, myArray);           

  List<int> copyArray1 = [0, 0, 0];                           // 혹은 공간 미리 확보 (copyArray1.length 를 바꿔도 런타임 범위 예외발생)
  copyArray1.setRange(0, myArray.length, myArray);      

  List<int> copyArray2 = myArray.sublist(0, myArray.length);  // 자료구조 + 인덱스카피 방식
  // Int32List copyArray3 = myArray.sublist(0, myArray.length);   // 오류: 자료구조 다름. 형변환 실패

  Int32List copyArray4 = Int32List(myArray.length);           // Int32List객체는 전통배열과 유사하여 객체 선언과 동시에 크기 할당.
  copyArray4.setRange(0, myArray.length, myArray);            // 반복자 방식이라 다른 자료구조에도 잘 들어감.

  Int32List copyArray5 = copyArray4.sublist(0, copyArray4.length);  // 성공: 자료구조 같음

  
  print(myArray);
  print(copyArray);
  print(copyArray1);
  print(copyArray2);
  // print(copyArray3);
  print(copyArray4);
  print(copyArray5);
  


  // 반복문
  print("\n반복문: ");
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

  // 제어문
  print("\n제어문:");
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


  // 삼항(조건) 연산자
  bool myBoolean = (1 < 3) ? true:  false;
  print(myBoolean);
  

  // Map
  print("\nMap:");
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
    print("key: ${key}\tval:${myMap[key]}");
  }

  // 내장 foreach
  myMap.forEach((k, v) {
    print("key: ${k}\tval:${v}");
  });


  // Set
  final Set<int> mySet = {1, 2, 3};   // final선언시 재할당만 안될 뿐, 추가/제거 가능.
  mySet.add(1);   // 중복허용 X
  mySet.remove(3);
  // 값 변경 불가
  print(mySet.contains(3));   // 포함여부 -> false
  print(mySet);


  // 클래스
  print("\n클래스: ");
  // static 키워드로 객체생성없이 호출(공통된 메모리공간 사전할당)
  // 클래스 정적변수
  print(Myclass.c);
  // 클래스 정적메서드 호출
  Myclass.sayHello("park");

  Myclass t = Myclass(1, 2);    // 클래스타입 선언

  print(t.a);     // 멤버변수 사용
  print(t.b);
  print(t.getHello());  // 멤버함수 호출


  //! enum 열거형 (String등으로도 같은기능을 구현할 수 있으나, 어떤 선택지가 있는지 명시 가능)
  print("\n열거체");
  Status myEnum = Status.busy;
  if (myEnum == Status.idle) {
    print("유휴");
  } else if (myEnum == Status.work) {
    print("작업중");
  } else {
    print("바쁨");
  }


  // function
  print("\n함수:");
  print(sum(1));                    //! 기본매개변수 설정
  print(sum(1, 2));
  print(sum(1, 2, 3));

  print(sum2(a: 1, b:2));           //! 기본매개변수 설정 가능
  print(sum2(a: 1, b: 2, c: 3));
  print(sum2(c: 2, a: 5, b: 3));    // 순서상관 X. 

  print(sum3(1, b:2, c:3));


  //! signature (void* 같은 역할, c, cpp에서 void*외 typedef로도 가능한데, typedef int (*Operation)(int a, int b); 로 사용.)
  Operation myOps = add;
  print(myOps(1, 2));
  print(calc(1, 2, sub));

}

typedef Operation = int Function(int a, int b);
int add(int a, int b) => a + b;
int sub(int a, int b) => a - b;
int calc(int a, int b, Operation oper) => oper(a, b);



//! 함수: 기본매개변수 설정은 [] 로 묶는다. 초기화가 필수. null을 이용해  int?로도 사용 가능하나 ??= 처럼 명시해야된다.
// optional parameter라고도 부름.
int sum(int a, [int b =0, int? c]) {
  return a + b + (c ??= 0);
}

//! named parameter: 매개변수를 map처럼 명시하여 넣는다. 마찬가지로 기본매개변수 설정 가능.(이땐 []가 필요 없음.)
int sum2({required int a, required int b, int c = 0}) {
  print("a: $a  b: $b  c: $c");
  return a + b + c;
}

// 파라미터 복합 사용, 화살표 리턴
int sum3(int a, {required int b, required int c}) => a + b + c;



// class 의 사용: 접근제어(간략한서술), 생성자, 멤버변수, 멤버함수, 정적멤버변수와 함수에 대한 설명
class Myclass {
  //! 접근제어자(public, private, protected) 는 없으며, class가 어떻게 선언되었나에 따라 권한이 다름. 
  // final class(상속/구현금지), base class(상속만 허용), interface class(구현만 허용), sealed class(동일 파일에서만 extends 하여 상속 혹은 implements 로 구현)
  int a = 0;
  int b = 0;
  static int c = 3;   // 정적 멤버변수 사용
  
  //! Myclass(this.a, this.b);   // 관용적 사용. 멤버변수 초기화 없이 사용 가능. 추천사용법.
  // 관용적 생성자를 사용하지 않고 전통적인 사용시 a, b초기값 할당 없이 선언만 할 수 없음. 
  //! 만약 멤버변수 Nullable 예외하려면 int? a;, int? b; 로 사용
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



// 열거체
enum Status{ idle, work, busy }