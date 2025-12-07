package training.testcodes.interfaceTest;

public class Chicken implements Animal {    // 구현클래스
    private String barkSound = "꼬끼오";
    private String moveStyle = "날기 혹은 두다리걷기";
    private String name = "unknown";


    public void setName(String name) { this.name = name; }
    public String getName() { return this.name; }
    Chicken() {}
    Chicken(String name) { setName(name); }
    Chicken(Animal o) { setName("유전자 복제 "+ o.getName()); } // 복사생성자.

    public void bark() { System.out.println(barkSound); }
    public void move() { System.out.println(moveStyle); }
    
}
