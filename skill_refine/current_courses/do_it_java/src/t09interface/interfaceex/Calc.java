package t09interface.interfaceex;

public interface Calc {
    // 접근제한자, abstract 생략가능
    int add(int a, int b);
    int sub(int a, int b);
    int mul(int a, int b);
    int div(int a, int b);


    // 아래는 최신 jdk에 추가됨
    // 디폴트 메서드: 일부 기본기능 구현
    default void description() {
        System.out.println("정수 계산기를 구현합니다.");
        myMethod();
    }

    // 정적메서드. 인스턴스 없이 사용가능
    static int total(int[] arr) {
        int total = 0;
        for (int i : arr) {
            total += i;
        }
        myStaticMethod();   // 이건 사용가능
        return total;
    }


    // 인터페이스 내부적으로만 사용할 때 private, private static metohd
    private void myMethod() {
        System.out.println("private method");
    }

    private static void myStaticMethod() {
        System.out.println("private static method");

    }

}
