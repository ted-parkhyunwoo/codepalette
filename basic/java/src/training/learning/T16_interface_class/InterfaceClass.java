package training.learning.T16_interface_class;

// class와 다르게 interface는 파생 interface와 다중상속 가능.(이름이 같은 메서드가 있어도 인터페이스에서는 구현이 안돼서 모호성이 없음. 구현클래스에서 할 일.)

interface ifc {     // class 대신 interface로 선언. 멤버 접근제한자는 생략하여도 모두 통일됨. 변수- 전역상수처리. 메서드- 추상메서드
    // 모든 멤버변수는 public static final임(생략가능) - 런타임 상수처리 개념: ifc객체를 직접 생성할수 없고 한번만 선언가능: 인스턴스화 불가. 상수는 한번만 메모리 로드되어 공유됨.
    public static final int MEMBER1 = 100;
    int MEMBER2 = 200;

    // 모든 일반 멤버메서드는 추상메서드이며 public abstract임. (생략가능)
    public abstract void method1();
    void method2();
}

// 아래 상속과 구현 관계가 복잡할 수 있으므로 정리.
// ifc2 -> ifc 상속             // ifc2의 구현클래스를 작성한다면 method1,2,3 사용 가능 (class Tmp impements ifc2{})
// Parent -> ifc4 구현          // method5만 사용 가능
// Child -> Parent 상속(ifc4구현됨), ifc2(ifc상속), ifc3 구현. 1~5 모두 사용가능. 다만 method5는 override 하지 않는이상 Parent를 따름.


// 이와같이 선언만 해서 더미로 활용하면 모듈별 병렬개발 가능 -> 개발시간 단축.
interface ifc2 extends ifc { void method3(); }
interface ifc3 { void method4(); }
interface ifc4 { void method5(); }

// 인터페이스 상속은 implements 키워드. (다중상속 가능.)
class Parent implements ifc4 {  // implement 는 구현을 뜻함: ifc4의 선언을 구현한다는 뜻.
    public void method5() { System.out.println("Method5"); }
}

// 파생클래스는 조상클래스(여기선 인터페이스) 의 접근제한자 범위보다 넓어야 함.
// 따라서 인터페이스클래스(인터페이스)의 멤버메서드는 항상 public이므로, 구현클래스(Parent, Child)에서는 모두 public으로 선언되어야 함.
class Child extends Parent implements ifc2, ifc3 {
    public void method1() { System.out.println("Method1"); }
    public void method2() { System.out.println("Method2"); }
    public void method3() { System.out.println("Method3"); }
    public void method4() { System.out.println("Method4"); }
    @Override
    public void method5() { System.out.println("Override: Method5"); }
}

public class InterfaceClass {
    public static void main(String[] args) {
        // 여러타입으로 캐스팅해보기(형변환)

        // child의 기본클래스. ifc4만 상속받음.(method5)
        Parent p = new Child();
        p.method5();        // Child에서 override됨.
        Parent p2 = new Parent();
        p2.method5();       // Parent객체는 override되지 않음.

        // static 멤버는 전체로 공유됨. 따라서 어떤 클래스든 MEMBER1은 한가지 값으로 통일. 해당타입으로 인스턴스 생성 안해도 이미 사용가능(싱글톤학습내용 참고)
        System.out.println(ifc.MEMBER1); 
        // 인터페이스 타입으로 "참조"선언;업캐스팅.(method1, method2처럼 상속된 내용만 따름.)
        ifc i = (ifc)p;
        i.method1();
        i.method2();
        // i.method3(); 3~5번 메서드 직접호출 불가.
        System.out.println(i.MEMBER2); // 위처럼 스태틱변수는 ifc.MEMBER2로 사용 권장.

        // 마찬가지로 p객체는 사실 메모리에 모든 정보가 있기 때문에, 본질타입인 Child로 타입캐스팅하면 모든기능이 사용됨.
        Child c = (Child)p;
        c.method1();
        c.method2();
        c.method3();
        c.method4();
        c.method5();
    }
}