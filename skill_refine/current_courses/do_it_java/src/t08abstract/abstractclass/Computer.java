package t08abstract.abstractclass;

// 추상클래스: 반대개념은 구체클래스(concrete class)
// 일부만 구현하거나 일부만 재정의 하거나, 모두 시그니처 선언만 하거나 자유임.
public abstract class Computer {

    // 추상메서드 포함 가능:
    // 없어도 abstract class선언 가능: 상속용으로만 쓸 수 있으므로, new 를 못하는건 똑같음.
    // 이런것들을 시그니처, 정확히는 메서드 시그니처 라고 함.
    public abstract void display();

    public abstract void typing();


    // 일부 메서드는 구현: 보통 공유하는 메서드
    public void turnOn() {
        System.out.println("Turn on");
    }

    public void turnOff() {
        System.out.println("Turn off");
    }
}
