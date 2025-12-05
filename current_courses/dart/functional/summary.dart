void main(List<String> args) {
  
  //! ---- 펑셔널 프로그래밍 ----

  // map 자료구조를 객체로 파싱
  // json(map)과 같은 형식은 불완전함: name 대신 엉뚱한 값이 있거나, key,value 등의 타입 등이 보증이 안되는 상태. 
  List<Map<String,String>> memberToObjectTest = [
    {
      "name" : "RM",
      "group" : "BTS"
    },
    {
      "name" : "J-HOPE",
      "group" : "BTS"
    },
    {
      "name" : "범규",
      "group" : "TXT"
    },
    {
      "name" : "연준",
      "group" : "TXT"
    }
  ];

  // 이렇게 객체화 시킨 자료를 다루는것이 일반적이고 안전함: 객체전환으로 확실한 값 보증 절차
  final parsed = memberToObjectTest.map(
    (x) => Person(x["name"]!, x["group"]!)    // 느낌표를 붙여서 값이 "NOT NULLABLE" 임을 명시해야 함(NULL일시  책임을 코드 작성자가 진다는 느낌)
  ).toList();

  print(parsed);

  // 이런 객체전환으로 p에 .을 찍으면 어떠한 멤버를 가지고 있는지 한눈에 알 수 있게됨
  // 불완전 데이터 -> 확실한 데이터 검증과정이라 생각하면 됨.
  for (Person p in parsed) {
    print(p.name);
    print(p.group);
    print(p.hashCode);
  }

  // 아래 필터도 당연히 작동 잘됨.
  final txt = parsed.where((x) => x.group == "TXT").toList();
  print(txt);


  //! 이렇게 연속적으로 사용하는 것이 함수형(체이닝) 프로그래밍
  final customMembersNameLengthTotal = 
  memberToObjectTest.map(                           // map으로 Person 객체를 따고
    (x) => Person(x["name"]!, x["group"]!)
  ).where(                                          // where로 BTS 만 필터하고
    (x) => x.group == "BTS"
  ). fold<int>(                                     // fold로 길이 합산
    0, (p, n) => p + n.name.length
  ).toString();                                     // int -> String

  print("BTS로 등록된 사람의 이름 길이 합은 " + customMembersNameLengthTotal + " 이다.");      // int가 아니라 String이라서 + 연산 가능.
}


class Person {
  final String name;
  final String group;

  Person(this.name, this.group);

  @override
  String toString() {
    return "name: $name, group: $group";
  }
}