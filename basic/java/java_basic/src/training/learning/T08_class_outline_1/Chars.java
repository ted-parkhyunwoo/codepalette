package training.learning.T08_class_outline_1;

// 클래스 구조: 강의내용과 다르게 개인적으로 작성하던것을 첨삭하여 코드등록.

class Chars {   // 캐릭터(게임캐릭터를 의미.)
    // 멤버변수, 필드
    String name;
    char type;
    int hp;
    byte strength;
    // +@. 접근제어자 사용. (직접적인 변수변경 불가)
    private Boolean isAlive = true;

    // 기본생성자
    Chars() {
        this("unknown");        // this는 Chars()를 호출하는 느낌. cpp에서도 비슷한 트릭을 사용한 적이 있음.
    }

    // 파라미터생성자.
    Chars(String name) {
        this.name = name;
        type = 'F';
        hp = 100;
        strength = 10;
    }
    Chars(String name, char type, int hp, int strength) {
        this.name = name;
        this.type = type;
        this.hp = hp;
        this.strength = (byte)strength;
    }


    // 메서드
    void printStatus() {
        String res = "Status: " + (isAlive?"Alive":"Dead") + " Name: " + name + " Type: " + type + " HP: " + hp + " STRENGTH: " + strength;
        System.out.println(res);
    }
    void makeDead() {
        isAlive = false;
        hp = 0;
        strength = 0;
    }
    // 리턴타입 메서드
    String getName() {
        return this.name;
    }
    // 메서드의 파라미터
    void changeHP(int hp) {
        this.hp = hp;
    }

    // 메서드 오버로딩  (makeDead()실행 후 파라미터로 입력한 msg 출력.)
    void makeDead(String msg) {
        makeDead();
        System.out.println(msg);
    }

    // 참조형 파라미터: 참조로 받을수 있으며, 그것이 클래스 자기자신의 타입일수도 있음.
    void kill(Chars chr) {
        chr.makeDead(getName() + "이(가) " + chr.name + " 을(를) 죽였습니다.");
        changeHP(this.hp + 10);
        System.out.println("보상: HP 10 상승.");
    }
}
