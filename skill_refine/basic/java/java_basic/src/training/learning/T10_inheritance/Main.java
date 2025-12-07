package training.learning.T10_inheritance;

public class Main {
    public static void main(String[] args) {

        /*
        Person과 Spider는 각각 독립 클래스.
        SpiderMan은 Person을 상속하며, Spider의 일부 속성을 사용하기 위해 내부에 Spider 객체 생성.

        SpiderMan 은 Person을 is a관계로 상속받고,
        Spider의 fireweb()만 내부객체생성하여 사용. (has a 관계)
        이유는 move()가 양쪽 클래스에 중복되고(모호성), java의 class는 단일상속만 가능하므로.

        +@. python과 cpp는 다중상속 가능: 재점검해볼것.
        python: MRO와 super()를 따라 호출순서 지정
        cpp: 가상상속으(virtual inheritance)로 충돌방지
        java: interface로 우회함(나중에 학습)
         */

        SpiderMan sman= new SpiderMan("Ted");
        sman.move();
        sman.fireweb();
        System.out.println(sman.name);

    }
}
