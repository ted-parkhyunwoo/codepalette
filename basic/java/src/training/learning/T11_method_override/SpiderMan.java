package training.learning.T11_method_override;

public class SpiderMan extends Person {

    Spider spider = new Spider();
    boolean isSpider;
    void fireweb() {
        spider.fireweb();
    }

    // move 재정의(override): 참고-overloading 이랑 다름에 주의.
    @Override   // 재정의문법 점검: 애너테이션사용. override실패시 오류출력하도록 명시.
    void move() {
        if (isSpider) {
            spider.move();
        } else {
            // 부모클래스의 멤버접근시 super키워드. (Person의 move())
            super.move();
        }
    }

    // Person에서 재정의한 오브젝트클래스 멤버함수(toString())를 다시 재정의
    @Override
    public String toString(){
        return super.toString() + ", [Spiderman] isSpider?" + this.isSpider;
    }

    public SpiderMan() {
        super();
    }
    public SpiderMan(String name) {
        super(name);
    }

}
