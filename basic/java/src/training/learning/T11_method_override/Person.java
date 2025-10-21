package training.learning.T11_method_override;

public class Person {
    String name;
    void move(){
        System.out.println("사람이동");
    }

    public Person() {
        this.name = "Empty";
    }

    public Person(String name) {
        this.name = name;
    }

    // java.lang.Object 클래스 오버라이드: 참고- Object클래스는 java의 모든클래스의 부모클래스. toString은 Object클래스의 멤버메서드
    @Override
    public String toString() {
        return "[person]name:" + this.name;
    }
}

