package training.learning.T15_abstract_class;

/*
    abstract class (추상 클래스):
    - 추상화 기술의 하나로, 일부 메서드는 구현되어 있고 일부는 구현되지 않은 상태로 남아 있음
    - 직접 인스턴스를 생성할 수 없음
    - 파생(구체) 클래스에서 미구현 메서드를 반드시 구현해야 함
    - 기본 클래스와 인터페이스 사이의 중간 개념
    - 주의: 인터페이스가 아님!
    - 일부 구현이 포함되어 있음
    - C++의 순수 가상 함수 (virtual ... = 0)와 유사한 개념

    사용 방식:
    - abstract 클래스는 extends로 상속하고, 파생 클래스에서 @Override로 메서드를 구현
    - interface는 implements로 구현

    참고:
    - 추상 클래스든 인터페이스든, 구현 클래스에서는 @Override를 명시하는 것이 좋음
*/

public class Main {
    public static void main(String[] args) {
        Parent[] family = {new Child(), new Child2()};

        for (Parent f : family) {
            f.fam();
            f.func();
            System.out.println(f.str());
        }
    }
}
