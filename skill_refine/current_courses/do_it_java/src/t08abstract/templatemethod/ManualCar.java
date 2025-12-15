package t08abstract.templatemethod;

public class ManualCar extends Car {
    @Override
    public void drive() {
        System.out.println("수동으로 운행");
        System.out.println("수동으로 방향전환");
    }

    @Override
    public void stop() {
        System.out.println("수동으로 멈춤");
    }
}
