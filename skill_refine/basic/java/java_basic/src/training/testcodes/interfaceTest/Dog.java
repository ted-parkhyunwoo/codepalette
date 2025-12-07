package training.testcodes.interfaceTest;

public class Dog extends SimpleUtil implements Animal { // 상속과 구현 모두하기. (구체클레스 이면서 구현클래스.)
    private String barkSound = "멍멍";
    private String moveStyle = "네발걷기";
    private String name = "unknown";

    Dog() {}
    Dog(String name) { this.name = name; }

    @Override
    public void bark() { SimpleUtil.printStr(barkSound); }
    @Override
    public void move() { SimpleUtil.printStr(moveStyle); }
    @Override
    public String getName() { return this.name; }
    @Override
    public void setName(String name) { this.name = name; }
}
