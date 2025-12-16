package t09interface.interfaceex;

// 여러개 구현 가능(Calc, Runnable 등)
// 이유: 어차피 interface들만 상속처럼(정확히는 구현) 사용할 수 있고
// 정의는 안되어있는 상태기 때문에 애초에 같은 메서드명이 있더라도 행동은 여기서 구현해 모호성이 없어짐
public abstract class Calculator implements Calc{
    // 구현체 이지만, 일부만 구현시 마찬가지로 abstract 추상클래스가 됨.
    // 따라서 구현체 이면서 추상클래스임.
    @Override
    public int add(int a, int b) {
        return a + b;
    }

    @Override
    public int sub(int a, int b) {
        return a - b;
    }


}
