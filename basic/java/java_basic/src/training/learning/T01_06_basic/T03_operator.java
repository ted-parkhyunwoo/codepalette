package training.learning.T01_06_basic;

public class T03_operator {
    public static void main(String[] args) {
        // 산술연산은 타입일치 필요.

        // 32bit미만은 int형으로 자동변환되므로 주의
        byte a = 12;
        byte b = 24;
        byte c = (byte)(a + b);
        System.out.println(c);


        // 큰 타입으로 형 변환: 여러 방법.
        int i1 = 100;
        long l1 = 200;
        // int res = i1 + (int)l1;
        // long res = i1 + l1;
        int res = (int)(i1 + l1);
        System.out.println(res);


        // 문자열의 + 는 결합연산.
        char gender = '남';
        int age = 10;
        String name = "김상철";
        String strRes = name + gender + age;
        System.out.println(strRes);
        // 주의: 예문처럼 문자열로 시작하는 +연산임. 순서가 바뀌면 (char + int + string) char + int의 정수값 + 스트링이 되어버림.
        strRes = gender + age + name;
        System.out.println(strRes);
        // 혼자 발견한 편법.
        strRes = "" + gender + age + name;
        System.out.println(strRes);

        // 대입연산자(=, +=, ...), 비교연산자(==, !=, ...) PASS...

        // 논리연산자(&, |, !, ^)
        boolean b1 = true & true;
        boolean b2 = false | true;
        System.out.println("b1:"+ b1 + "\nb2:" + b2);
        // & vs &&: 성능향상
        boolean b3 = false & true;  // 두번째 피연산자까지 검사
        boolean b4 = false && true; // 첫번째 피연산자에서 조건탈락.
        // | vs ||
        boolean b5 = true | false;      // 두번째 피연산자까지 검사
        boolean b6 = true || false;     // 첫번째만 봐도 답 나오니 통과

        // 증감연산(++, --) PASS...

    }
}