package t13exception;

public class AutoCloseObjTest {
    public static void main(String[] args) {
        AutoCloseObj obj = new AutoCloseObj();

        // 구현부가 아닌 try에도 쓸수 있나봄.
        try (AutoCloseObj obj2 = obj) {
        // try (obj) {          이런 문법은 java9부터 지원됨
            throw new Exception("강제로 던져진 익셉션");
        } catch (Exception e) {
            // 호출됨
            System.out.println("예외가 발생하였지만 아마 Close될겁니다");
            System.out.println(e);
        }
    }
}
