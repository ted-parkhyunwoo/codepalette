package sixth;

public class Student {
    static int serialNumber = 1000;             // static변수(인스턴스 없이 사용가능)
    private int id;
    private String name;
    private int grade;
    private int money;

    Student(String name, int grade, int money) {
        this.name = name;                       // this 는 자기 자신을 참조.
        this.grade = grade;
        this.money = money;
        this.id = ++serialNumber;               // id는 serialNumber에서 1씩 더해 자동부여
    }

    // getter
    public int getId() { return this.id; }
    public String getName() { return this.name; }
    public int getGrade() { return this.grade; }
    public int getMoney() { return this.money; }
    // static 메서드
    public static int getSerialNumber() { return serialNumber; }

    // setter: 대체로 private 처리된 멤버는 setter를 사용하진 않으나, 예제임.
    // this가 현재 인스턴스를 가리킨다는 점을 이용해 return this를 통해 연속적인 함수형 setter 사용가능
    public Student setName(String name) { this.name = name; return this; }
    public Student setGrade(int grade) { this.grade = grade; return this; }
    public Student setMoney(int money) { this.money = money; return this; }


    // 다른 클래스와의 합동 연결성 예제(버스,지하철)
    public void takeBus(Bus bus) {
        if (this.money >= 1000) {
            this.money -= 1000;
            bus.take(1000);
        }
        else { System.out.println("check your money: " + this.money); }
    }

    public void takeSubway(Subway subway) {
        if (this.money >= 1500) {
            this.money -= 1500;
            subway.take(1500);
        }
        else { System.out.println("check your money: " + this.money); }
    }


    // 상태출력 메서드
    public void showStudentInfo() {
        String info = "name: " + getName() + ", grade: " + getGrade() + ", id: " + getId() + ", money: " + getMoney();
        System.out.println(info);
    }

}
