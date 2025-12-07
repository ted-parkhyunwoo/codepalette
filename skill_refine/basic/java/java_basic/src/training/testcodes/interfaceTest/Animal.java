package training.testcodes.interfaceTest;

public interface Animal {
    // 멤버변수는 public static final 이라 런타임 상수개념으로만 갖고있음. 상수 외 변수개념 X.
    boolean isAnimal = true;    // 현재 코드 구조에선 의미없는 변수.

    // 생성자 및 복사생성자 등 구현 강요할 수 없음.

    // 멤버메서드는 모두 public abstract. 틀만 제공하고 구현은 각자 알아서.
    void bark();
    void move();
    void setName(String name);
    String getName();
}
