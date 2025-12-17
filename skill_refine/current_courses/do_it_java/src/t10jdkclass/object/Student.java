package t10jdkclass.object;


// 모든 객체는 Object 클래스를 extends 함.
public class Student {
    int studentId;
    String studentName;

    public Student(int studentId, String studentName) {
        this.studentId = studentId;
        this.studentName = studentName;
    }


    // Object 클래스의 기본기능을 재정의
    // toString, hashCode, equals 는 자주 사용됨.

    @Override
    public String toString() {
        return studentId + ", " + studentName;
    }

    @Override
    public int hashCode() {
        return studentId;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Student) {
            Student student = (Student) obj;
            return this.studentId == student.studentId;
        }
        return false;
    }

    public static void main(String[] args) {
        Student student1 = new Student(100, "김유신");
        Student student2 = new Student(100, "김유신");

        System.out.println(student1);
        System.out.println(student2);

        // 정수형 해시코드는 그 값 자체를 리턴하는게 스탠다드.
        System.out.println(student1.hashCode());
        System.out.println(student2.hashCode());

        // equlas를 재정의
        System.out.println(student1.equals(student2));
    }

}
