package t09interface.interfaceex;

public class CalcTest {
    public static void main(String[] args) {
        Calc calc = new CompleteCalc();
        CompleteCalc calculator = new CompleteCalc();
        int a = 3, b = 4;

        // 인터페이스타입으로 선언된 구현체 사용예.
        System.out.println(calc.add(a, b));
        System.out.println(calc.sub(a, b));
        System.out.println(calc.mul(a, b));
        System.out.println(calc.div(a, b));

        // showInfo() 는 CompleteCalc구체클래스 에만 선언/정의 되어있다.
        // 새로 정의된 메서드는 본래타입에 정의되어 있더라도 선언된 타입에 선언된 경우만 사용가능.
        calculator.showInfo();

        // 형변환을 사용하면 본래의 타입으로 캐스팅 하여 사용가능.
        CompleteCalc c = (CompleteCalc) calc;
        c.showInfo();
        // 혹은
        ((CompleteCalc) calc).showInfo();


        // 아래는 모두 interface에 추가된 디폴트,프라이빗,스태틱 메서드 기능
        // 디폴트메서드는 객체. 으로 접근
        // private 메서드는 디폴트메서드 내에서 호출됨
        calc.description();


        // 인터페이스 static 메서드는 객체.기능()이 아닌 타입.기능()
        // private static 메서드는 total() 내에 호출됨
        // 선택이 아님. 무조건 이렇게 써야함
        int[] arr = {1, 2, 3, 4, 5};
        int t = Calc.total(arr);
        System.out.println(t);


    }
}
