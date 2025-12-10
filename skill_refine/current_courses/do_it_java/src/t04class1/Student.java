package t04class1;

// 네이밍 관례
// 패키지명: 소문자로만.
// 클래스명: 대문자로 시작
// 메서드: 카멜표기

public class Student {
    int studentID;
    String studentName;

    public void showStudeontInfo() {
        System.out.println("ID: " + studentID + " name: " +studentName + "\n");
    }

    public String getStudentName() {
        return studentName;
    }

}
