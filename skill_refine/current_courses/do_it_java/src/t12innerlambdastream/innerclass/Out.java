package t12innerlambdastream.innerclass;


// 클래스 내부의 클래스들과 그 멤버들
// 아래 코드는 static과 일반멤버 두가지가 섞여서 복잡해 보일 뿐이지, 클래스 내부의 클래스, 각각의 멤버일 뿐이다.

public class Out {
    // In 혹은 SIn 에서 사용해볼 외부클래스 멤버
    private int num = 1;
    private static int sNum = 2;

    // In을 사용할 수 있도록 in 멤버 초기화: 물론 in멤버 없이도 초기화 가능함: out.new In();
    private In in;
    public Out() { in = new In(); }


    //! 인스턴스 내부클래스
    public class In {
        int inNum = 100;
        static int sInNum = 200;

        void inTest() { System.out.printf("인스턴스 내부멤버 inTest호출: %d %d %d %d\n", num, sNum, inNum, sInNum); }
        static void inSTest() { System.out.println("인스턴스 내부클래스의 멤버: 정적메서드 inSTest 호출"); }
    }

    //! static 정적 내부클래스: static을 붙임으로 Out의 멤버를 참조 않겠다는 의도의 키워드로 주로 쓰인다
    static class SIn {
        int sInNum = 10;
        static int sInsNum = 20;

        // sInTest() 에서 num은 사용할 수 없다
        // 아래에도 서술되지만, 내부 static class 는 외부클래스에 종속받지 않고 생성 가능하므로 메모리를 공유하지 않음.
        void sInTest() { System.out.printf("정적 내부클래스: %d %d %d\n", sNum, sInNum, sInsNum); }
        static void sInSTest() { System.out.println("정적 내부 클래스의 멤버: 정적 메서드 sInSTest 호출"); }
    }


    //! 지역내부 클래스로, 분리하여 구현할 예정(복잡도 증가)
    public void func() {
        class Local {
            // 지역내부클래스
            //! 필요시 위 보다는 익명내부클래스를 더 많이 씀
        }
    }


    //! TEST main method
    public static void main(String[] args) {

        // 1. 내부클래스 혹은 정적내부 클래스의 멤버가 static이면 다음과같이 호출.
        Out.In.inSTest();
        Out.SIn.sInSTest();
        // 결론: 외부 내부클래스가 정적이든 어떻든 멤버메서드가 static이면 인스턴스 없이 호출가능함을 알 수 있다.


        // 2. 정적 내부 클래스의 멤버호출: 인스턴스를 생성해야함. 대신 Out에 구애받지않음, num 멤버사용불가
        // Out.SIn.sInTest();       //! 잘못된 호출
        SIn sin = new Out.SIn();
        sin.sInTest();              // 올바른 호출
        // 결론: 위와 반대로 static클래스여도 멤버 메서드가 static이 아니면 인스턴스를 만들어야 한다.
        // 또한 static클래스는 Out에 종속받지 않아 new Out.SIn(); 과 같은 형태로 정의 가능하다
        // 외부클래스의 멤버 num을 참조할 수 없으므로, 이 특성을 고려하여 static 클래스로 만들지 일반 내부클래스로 만들지 잘 정해야 함


        // 3. 내부클래스 타입으로 선언: Out에 종속받는 성질. num 멤버 사용가능
        Out out = new Out();
        out.in.inTest();

        // In을 생성: Out을 종속하기때문에, 다음과같이 선언해야한다.
        In in = out.in;             // 이렇게 Aliasing 하거나... (멤버로 in을 갖고있다. private지만 가능)
        In in2 = out.new In();      // 이렇게도 생성할 수 있음.


        // 선언 불가한 예:
        // In in3 = Out.new In();
        // In in4 = new Out.In();
    }

}

