package training.learning.T10_inheritance;

public class SpiderMan extends Person {

    // move()는 Person과 Spider클래스가 서로 중복되고, fireweb은 갖고싶으니,
    // java는 단일상속만 가능하므로 Person을 is a 관계로 받고 나머진 has a관계로 받아 사용.

    // 멤버변수로 거미객체를 받아 쓰기.
    Spider spider = new Spider();
    void fireweb() {
        spider.fireweb();
    }

    // 상속클래스가 부모클래스의 생성자를 호출
    public SpiderMan() {
        super();
    }
    public SpiderMan(String name) {
        super(name);
    }

}
