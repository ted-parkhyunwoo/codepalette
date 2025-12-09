package sixth;

// this, getter setter, 여러 클래스간 연동, static멤버(변수와 메서드) 활용예제

public class Test {
    public static void main(String[] args) {

        System.out.println(Student.serialNumber);       // static변수의 사용은 인스턴스 없이 가능.
        System.out.println(Student.getSerialNumber());  // static멤버메서드도 마찬가지.

        Student studentLee = new Student("Lee", 1, 5000);
        Student studentPark = new Student("park", 2, 10000);
        studentPark.setName("Park").setGrade(3).setMoney(12000);        // setter의 연속사용
        Bus bus100 = new Bus(100);
        Subway green = new Subway("Green");

        // before
        System.out.println("Before: ");
        studentLee.showStudentInfo();
        studentPark.showStudentInfo();
        bus100.showInfo();
        green.showInfo();

        // 행동
        studentLee.takeBus(bus100);
        studentPark.takeSubway(green);


        // after
        System.out.println("\nAfter: ");
        studentLee.showStudentInfo();
        studentPark.showStudentInfo();
        bus100.showInfo();
        green.showInfo();


    }
}
