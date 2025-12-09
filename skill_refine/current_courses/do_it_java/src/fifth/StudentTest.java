package fifth;

public class StudentTest {
    public static void main(String[] args) {
        Student s1 = new Student();
        s1.studentName = "Park";
        System.out.println(s1.getStudentName());
        s1.showStudeontInfo();

        Student s2 = new Student();     // 인스턴스 생성
        s2.studentName = "Lee";         // 인스턴스 속성 부여(프로퍼티)
        s2.showStudeontInfo();          // 메서드
        System.out.println(s2.getStudentName());

        // heap address. (가상의 값이며 실제 주소는 아님)
        // 참조값.
        System.out.println(s1);
        System.out.println(s1.hashCode());  // +@ 위 주소가 10진수로 출력됨.
    }
}
