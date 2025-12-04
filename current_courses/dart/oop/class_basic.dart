void main(List<String> args) {

  Idol blackpink = Idol("블랙핑크", ["지수", "제니", "리사", "로제"]);    // new를 붙여도 되고 안붙여도 됨. dart는 자유
  blackpink.sayHello();
  blackpink.introduce();

  // const로 선언된 Idol 클래스(당연히! 다를것같지만, 같은 인스턴스임)
  Idol bts = const Idol("BTS", ["RM", "슈가", "진", "제이홉", "지민", "뷔", "정국"]);   // 컴파일타임에 정해질 수 있으므로, const 사용 가능(생성자에 const 표기해야 둘다쓸수있음)
  Idol bts2 = const Idol("BTS", ["RM", "슈가", "진", "제이홉", "지민", "뷔", "정국"]);
  
  print(bts == bts2);   //! const로 선언된 두개의 객체가 초기화 내용이 같다면 같은 인스턴스가 됨: 최적화와 관련된 것이라 추정(값 변경이 없으니 어차피 동일객체 처리해도 상관없으니)
  bts.sayHello();
  bts.introduce();

  // getter, setter 적용된 클래스
  Idol2 bp = Idol2("블랙핑크", ["지수", "제니", "리사", "로제"]);
  print(bp.firstMember);
  bp.firstMember = "수지";
  print(bp.firstMember);

  // private 처리 된 클래스
  _Idol test = _Idol("블랙핑크", ["지수", "제니", "리사", "로제"]);
  test._sayHello();
  test._introduce();


  // +@ 팩토리생성자
  Idol factoryConstructorUse = Idol.initDefault();
  factoryConstructorUse.sayHello();
  factoryConstructorUse.introduce();
}


class Idol {
  // final 로 immutable 프로그래밍 (생성자 호출 등으로 초기화 하면 변경 불가하도록 처리)
  final String name;
  final List<String> members;


  // 전통적인 c++스타일 이니셜라이즈(초기화) 리스트: 사용가능.
  // Idol(String name, List<String> members) : this.name = name, this.members = members {}    

  // const 생성자이면서 관용적으로 자주 쓰는 생성자(초기화) - const 키워드로 생성자를 만들면 인스턴스도 const로 만들 수 있으나, 런타임결정되는 이름,멤버면 사용불가
  const Idol(this.name, this.members); 

  // Named Constructor: 함수 오버로딩을 지원하지 않으므로, .fromList같은 방식을 사용(회피방법: 상속과 오버라이딩, 기본매개변수)
  Idol.fromList(List l) : this.name = l[0], this.members = l[1] {}    
  
  // +@. 팩토리생성자 + 화살표함수
  factory Idol.initDefault() => Idol.fromList(["default", ["One", "Two"]]);

  // 아래오류. 멤버변수 nullable전환 String?처럼 선언하거나, 멤버변수 할당 name="", members=[] 상태라면 실행됨(하지만 final 이라면 초기화리스트 사용해야함. c++, java와 동일한 느낌)
  // Idol.fromList2(List l) { this.name = l[0]; this.members = l[1]; } 

  void sayHello() { print("안녕하세요 ${this.name} 입니다."); }
  void introduce() { print("저희 멤버는 ${this.members}가 있습니다."); }
}


class Idol2 {
  String name;
  List<String> members;

  Idol2(this.name, this.members);
  Idol2.fromList(List l) : this.name = l[0], this.members = l[1] {}

  void sayHello() { print("안녕하세요 ${this.name} 입니다."); }
  void introduce() { print("저희 멤버는 ${this.members}가 있습니다."); }


  //! getter setter 사용이 좀 특이함: 전통적인 return, void방식이랑 기능이 동일하나, 뉘앙스 차이라 함. 간단한 멤버변수 변경등 사용. (복잡한건 함수로)
  String get firstMember { return this.members[0]; }

  // 매개변수 1개만 가능 (현대 프로그래밍엔 멤버변수 final 선언되는 특성상 잘 쓰진 않음.)
  set firstMember(String name) { this.members[0] = name; }
}


// _언더스코어로 시작하면 private처리되어 다른파일에서 불러와 쓸 수 없음.
// 클래스, 메서드, 변수에 모두 사용 가능
class _Idol {

  String name;
  List<String> members;

  _Idol(this.name, this.members);
  _Idol.fromList(List l) : this.name = l[0], this.members = l[1] {}

  void _sayHello() { print("안녕하세요 ${this.name} 입니다."); }
  void _introduce() { print("저희 멤버는 ${this.members}가 있습니다."); }

  String get firstMember{
    return this.members[0];
  }

  // 매개변수 1개만 가능
  set firstMember(String name) {
    this.members[0] = name;
  }
}