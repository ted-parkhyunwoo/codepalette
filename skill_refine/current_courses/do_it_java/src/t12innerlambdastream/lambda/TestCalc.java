package t12innerlambdastream.lambda;


// 원래 구현체는 이렇게 만들 수 있으나, 램다를 사용하면 메인함수 내 처럼 사용한다.
class Calc implements MyCalc {
    @Override
    public int getMax(int a, int b) {
        return a >= b ? a : b;
    }

    public int getMin(int a, int b) {
        return a >= b ? b : a;
    }
}


public class TestCalc {
    public static void main(String[] args) {

        // 램다로 임시구현체 활용
        // MyCalc 함수형 인터페이스의 메서드는 getMax 하나 뿐이라, 멤버를 컴파일러가 추론하여 임시 구현체를 만듬.
        MyCalc myCalc = (a, b) -> (a >= b) ? a : b;
        System.out.println(myCalc.getMax(3, 4));

        // 임시구현체 직접 구현
        MyCalc myCalc2 = new MyCalc() {
            @Override
            public int getMax(int a, int b) { return (a >= b) ? a : b; }
        };
        System.out.println(myCalc2.getMax(3, 4));

        // 직접 구현체를 사용
        MyCalc calc = new Calc();
        System.out.println(calc.getMax(3, 4));

        // 구현체 스타일로 하면 없던 기능을 추가할 수 있으나, 람다로는 불가.
        Calc calc2 = new Calc();       // 대신 타입이 Calc
        System.out.println(calc2.getMin(3, 4));

        // 혹은 다운캐스팅
        System.out.println(((Calc) calc).getMin(3, 4));

        //! +@ 주의.java는 람다 자체를 void*(cpp) 나 function(js, dart) 타입으로 저장할 수 없음
        // var test = (int a, int b) -> a + b;

        // 결론: java의 lambda 사용을 위해 함수형 인터페이스가 필요함.

    }
}
