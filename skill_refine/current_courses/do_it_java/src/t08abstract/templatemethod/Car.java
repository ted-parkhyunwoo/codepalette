package t08abstract.templatemethod;

public abstract class Car {
    public abstract void drive();

    public abstract void stop();

    public void startCar() {
        System.out.println("시동 켭니다");
    }

    public void turnOff() {
        System.out.println("시동 끕니다");
    }

    // 추상메서드도 아니고, 구현 의무도 없음. 다만, 필요에 따라 구체클래스에서 재정의 가능
    // 현재는 AICar에서만 자율로 세차장 가는 행동으로 재정의
    public void washCar() {
    }

    // 템플릿메서드 (시나리오를 정의하는것이고, 루틴은 바뀌지 않으므로 final : 재정의 불가선언)
    // 이런 과정은 framework 처럼 작동함(정해진 시나리오대로만 움직임)
    final public void run() {
        startCar();
        drive();
        stop();
        turnOff();
        washCar();
    }

}
