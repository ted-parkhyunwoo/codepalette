void main() {

  //! 1. dart의 문자를 정수형으로 혹은 정수를 문자로 전환
  // char 자료형이 없음. String으로 함
  List<String> testStringList = ['0', 'A', 'a'];  

  // for in 문법
  for (String element in testStringList) {
    // int형으로 전환시 : String 자료형이므로 0번인덱스로 지정
    int elementCharCode = element.codeUnitAt(0);  
    // int형을 다시 String으로 전환시 
    String fromCodeToChar = String.fromCharCode(elementCharCode); 
    print("char: $fromCodeToChar, code: $elementCharCode");
  }


  //! 1-1. 'A' 를 시작으로 +52까지 문자코드를 추가하여 List<String>로 저장 -> String 으로 join

  // 결과를 담을 리스트
  List<String> resultList = [];

  // 시작문자와 그 코드
  String startChar = 'A';
  int startCharCode = startChar.codeUnitAt(0);

  // 전통적인 for문
  for (int i = 0; i < 52; ++i) {
    int bfCharCode = startCharCode + (i % 26);
    String bfStr = String.fromCharCode(bfCharCode);
    resultList.add(bfStr);
  }

  print(resultList);

  // join 을 활용한 List 를 String 으로 ( resultList 를 String 자료형으로 전환)
  String resultString = resultList.join();
  print(resultString);


  // dart 의 List는 여러 자료형을 담을 수 있음.
  final testList = [1, 2, 3, 'a', ['String'], {'a': 97}];

  // join은 여러 자료형을 String으로 연결시킬 수 있음
  String testListStr = testList.join(' ');  // 공백으로 구분시켜 출력
  print(testListStr); 


  //! 1-2 List<String> 자료형 대신 StringBuffer를 활용(성능향상)
  // stringstream 과 유사하며, write(writeln, writeAll 등) 계열과 clear, toString 내장기능이 있음.

  StringBuffer sb = StringBuffer(); // 객체선언

  for (int i = 0; i < 52; ++i) {
    int bfCode = 'a'.codeUnitAt(0) + (i % 26);
    sb.write(String.fromCharCode(bfCode));
  }

  print(sb.toString());

  


  // 메인함수 종료.
}