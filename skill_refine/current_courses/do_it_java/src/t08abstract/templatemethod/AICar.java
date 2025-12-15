package t08abstract.templatemethod;

public class AICar extends Car {

    // 구체화
    @Override
    public void drive() {
        System.out.println("자율주행 시작");
        System.out.println("자율로 방향전환");
    }

    // 구체화
    @Override
    public void stop() {
        System.out.println("자율주행으로 멈춤");
    }

    // 재정의
    @Override
    public void washCar() {
        System.out.println("스스로 세차장에 감");
    }
}
