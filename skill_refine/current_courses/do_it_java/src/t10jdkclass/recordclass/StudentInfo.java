package t10jdkclass.recordclass;


import java.util.Objects;

// 모두 변경되지 않고 상수처리되는 데이터클래스를 쓸때.
// 웹개발에서 클라이언트의 요청 등을 객체화 할 때 많이 사용
public record StudentInfo(int id, String name) {

    // 원하면 오버라이딩 가능
    @Override
    public String toString() {
        return "ID: " + id + " NAME: " + name;
    }

    // equals 도 원하면 오버라이딩.
    // 기본 생성되는 equals와 기능은 동일(hashCode 검사 빼고)
    //! 원하는 필드만 검사하기 위해 id만 동일 검사하는 등의 기능으로 최적화 구현할 수 있음
    @Override
    public boolean equals(Object obj) {
        // 자신을 가리킨다면 true
        if (this == obj) return true;
        if (obj instanceof StudentInfo) {
            StudentInfo tmp = (StudentInfo) obj;
        // if (obj instanceof StudentInfo tmp) java 16부터 위 두 줄을 tmp로 바인딩 축약할 수 있음.
            return (this.id == tmp.id && name.equals(tmp.name)) ;
        }
        return false;
    }

    // hashCode 도 원하면 오버라이딩.
    // 마찬가지로 기본생성되는 hashCode() 와 기능상 동일
    @Override
    public int hashCode() {
        return Objects.hash(this.id, this.name);
    }


    public static void main(String[] args) {
        StudentInfo stdinfo = new StudentInfo(100, "김상철");
        StudentInfo stdinfo2 = new StudentInfo(100, "김상철");
        StudentInfo stdinfo3 = new StudentInfo(100, "박상철");

        System.out.println(stdinfo);
        // true
        System.out.println(stdinfo.equals(stdinfo2));
        // false
        System.out.println(stdinfo2.equals(stdinfo3));
    }
}
