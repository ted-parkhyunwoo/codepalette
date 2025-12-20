package t10jdkclass.enumclass;

// class와는 다른 enum의 주요 특성은 //!로 주석을 달았으니 참고
// 하나의 상수를 사용할땐 final을 쓰지만,
//! 다음과 같이 특성이 묶이는 경우의 상수 필요시 enum 사용
public enum GameLevel {
    //! 아래 문법으로 페어 정의
    BEGINNER_LEVEL(1, "초보자"),
    ADVANCED_LEVEL(2, "숙련자"),
    SUPER_LEVEL(3, "전문가");

    // 멤버변수
    final private int level;
    final private String name;

    //! 생성자의 인수로 정의한 페어를 넣으면 알아서 언팩됨
    GameLevel(int level, String name) {
        this.level = level;
        this.name = name;
    }

    // 필요시 getter 정의
    public int getLevel() { return this.level; }
    public String getName() { return this.name; }

    // toString() 등 원하면 오버라이딩 가능


    public static void main(String[] args) {
        //! enum으로 정의한 페어 접근시 . 으로 접근하여 정의
        GameLevel gamelevel = GameLevel.SUPER_LEVEL;
        // 아래와 같은 사전 페어 정의 없는 생성자 매개변수는 사용할 수 없으며, 위처럼 사용해야 알아서 언패킹
        // GameLevel gamelevel2 = GameLevel(3, "숙련자");

        //! 컴파일러 기본 toString()은 enum pair의 이름이 리턴됨
        System.out.println(gamelevel);
        // getter사용
        System.out.println(gamelevel.getLevel());
        System.out.println(gamelevel.getName());
    }

}
