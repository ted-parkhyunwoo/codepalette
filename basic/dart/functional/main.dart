void main(List<String> args) {

  // ---- 자료구조간 전환 ----
  List<String> bts = ["RM", "제이홉", "진", "지민", "슈가", "뷔", "정국", "정국"];

  final asmap = bts.asMap();
  Set<String> toset = bts.toSet();    // 타입명시 가능. 중복요소 삭제됨
  final tolist = toset.toList();

  print(bts);
  print(asmap);
  print(toset);
  print(tolist);
  bts.removeAt(bts.length -1);  // 다음 테스트를 위해 중복요소 삭제

  // ---- map 순회: 반복자로 요소 수정 및 조건부 수정 ----

  // map으로 List 요소별 램다 적용. map은 함수를 매개변수로 받는다.
  final bts2 = bts.map(
    //! return type: 값
    (name) => "BTS $name"
  );

  // 보다시피 모든 요소를 순회하면서 조건을 걸면 값만 바꿈(이터러블 자체로는 메모리 오버헤드 증가가 없으리라 추정. 할당시 2배 증가)
  final sugarfree = bts.map(
    // (name) { if (name != "슈가") { return name; } return "솔트"; }   아래로 간소화.
    (name) => name == "슈가"?  "솔트" : name
  );

  print(bts2);
  print(sugarfree);

  // String split하여 List로 각문자 배열로 전환후 map으로 수정하고 나온 이터러블자료형을 다시 list로 리턴.
  String num = "13579";
  final fileNames = num.split('').map((char) => "$char.jpg").toList();  
  print(fileNames);


  // Map을 map으로 순회 (MapEntry를 적용하며, 매개변수를 두개 사용)
  Map<int, String> btsMap = bts.asMap();
  final btsMap2 = btsMap.map(
    (key, value) => MapEntry(
      "BTS Member ${key + 1}", 
      value
    )
  );

  print(btsMap2);


  // ---- where 순회: 조건부 필터링 ----

  List<Map<String, String>> member = [
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

  String wantToFilterGroupName = "BTS";
  // 리턴타입: condition(boolean). 조건식.
  final filtered = member.where(
    (x) => x["group"] == wantToFilterGroupName
  );

  print(member);
  print(filtered.toList());

  List dynamicList = [0, "0", 1, true, "abc", 3.14, 1592];
  final filteredList = dynamicList.where((x) => x is int).toList();
  print(filteredList);


  // ---- reduce: 단하나의 값을 리턴하는 조건부 순회결과. ---- 
  //! 만약 요소가 1개 뿐이라면 램다 진입 없이 그대로 리턴됨.
  //! 첫번째 요소와 리턴타입이 같아야만 함: 다른타입을 받으려면 fold<>사용

  List<int> reduceTest = [1, 3, 5, 7, 9];   
  final res = reduceTest.reduce((prev, next) {
    print("$prev $next");
    return prev + next;
  });
  print(res);

  // 문자열 합치기
  List<String> helloWorld = ["Hello", "World", "!!!"];
  final resStr = helloWorld.reduce((p, v) =>  p + " " + v);
  print(resStr);

  print(helloWorld.join(" ")); // 사실 이것의 재발명...

  // ---- fold: reduce의 확장판 ----
  // 배열<문자열> 의 문자열 길이 총 합산 구하는 함수.
  print(helloWorld.fold<int>(0, (p, n) => p + n.length)); // 타입, 초기값에 주의. 리턴에도 p.length가 아님을 주의(p는 무조건 정수.)


  // cascading operator (...) : 스프레드연산자
  List<int> evenNums = [2,4,6,8];
  List<int> oddNums = [1,3,5,7];
  print([evenNums, oddNums]);       // 리스트내 두개 리스트로 표현됨
  print([...evenNums, ...oddNums]); // 언패킹처럼 풀어서 넣음.

}