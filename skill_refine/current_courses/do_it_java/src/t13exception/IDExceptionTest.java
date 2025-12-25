package t13exception;

public class IDExceptionTest {
    private String id;

    // 사용자 정의 예외 처리:
    // 예외클래스는 IDFormatException 처럼 정의만 해놓고, 행동은 메서드에서 처리(미루기)
    // 표준방식이며, 예외클래스에 setId등을 넣을 생각은 하지 않는게 좋음(클래스가 무거워짐)
    // 데이터 사용자(setId메서드), 전달자(예외클래스) 등의 책임 분리됨
    public void setId(String id) throws IDFormatException {
        if (id == null || id.equals("")) {
            throw new IDFormatException("id 가 null 입니다.");
        } else if (id.length() < 8 || id.length() > 20) {
            throw new IDFormatException("id는 8자 이상 20자 미만으로 사용하세요.");
        }

        this.id = id;
    }


    public static void main(String[] args) {
        IDExceptionTest test = new IDExceptionTest();

        // 미뤄진 행동을 try,catch에서 사용
        try {
            test.setId(null);       // null 예외 발생
            // test.setId("a");     // 8자미만 예외 발생
        } catch (IDFormatException e) {
            System.out.println(e);  // 예외 타입까지 출력
            System.out.println(e.getMessage()); // 메세지만 필요시
        }
    }
}
