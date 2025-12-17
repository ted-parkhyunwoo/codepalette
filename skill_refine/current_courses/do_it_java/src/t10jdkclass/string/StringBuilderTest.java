package t10jdkclass.string;

public class StringBuilderTest {
    public static void main(String[] args) {
        // 리터럴을 연결하지 말고, string builder로 append하면 추가할때마다 매번 생성되는 임시객체 오버헤드를 피할 수 있다.

        String javaStr = new String("java");
        // System.identityHashCode() 는 객체 주소기반 해시코드(decimal) 리턴(같다면 같은 주소임)
        System.out.println(System.identityHashCode(javaStr));


        // stringstream 처럼 작동하는 stringbuilder.
        StringBuilder bf = new StringBuilder(javaStr);
        // +@ 사실, 정수 입력(케파서티 설정) 후 bf.append(javaStr) 하는게 더 효율이 좋음
        // +@ 더불어 영문위주로만 저장한다면 char[] 대신 byte[] 로 메모리 최적화 됨.
        System.out.println(System.identityHashCode(bf));
        bf.append(" and");
        bf.append(" android");
        bf.append(" programming is fun!!!");
        System.out.println(System.identityHashCode(bf));        // 동일

        javaStr = bf.toString();
        System.out.println(javaStr);
        System.out.println(System.identityHashCode(javaStr));   // 새로 할당됨.

    }
}
