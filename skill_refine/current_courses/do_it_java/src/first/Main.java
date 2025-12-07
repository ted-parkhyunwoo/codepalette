package first;

public class Main {
 
    @SuppressWarnings("unused")
    public static void main(String[] args) {

        System.out.println("hi");


        // test결과 C도 똑같음
        int num = 10;
        int bNum = 0B1010;  // 2.   0B로 표기
        int oNum = 012;     // 8    0으로시작
        int hNum = 0xa;     // 16   0x로 시작

        System.out.println(num);
        System.out.println(bNum);
        System.out.println(oNum);
        System.out.println(hNum);


        // 실수
        long num1 = 12345678900L;   // L을 안써주면 정수로 핸들링되어 안들어감
        int level = 10;
        float pi = 3.14F;           // 실수는 기본이 double이지만 float로 강제지정 가능
        float pi2 = (float)3.14;    //  혹은 타입 캐스팅
        System.out.printf("num1: %d \tnum2: %d \tpi: %f \tpi2: %.2f\n", num1, level, pi, pi2);


        // 문자(UNICODE)의 인코딩('A'->65),디코딩(65->'A')
        char char1 = 65;    // A    
        char char2 = 66;    // B
        char char3 = 'C';
        System.out.println("" + char1 + char2 + char3);


        // 타입추론 : cpp 의 auto보다 구림. 사용자제
        // var로 타입 추론 가능(기본자료형 한정) 컴파일 타임에 적절한 변수명으로 바뀜. 지역변수에 한정됨
        var a = 3;
        var b = 3.14;
        var c = 'c';
        var d = "hello";
        System.out.println("" + a + b + c + d);


        // 상수: 대문자 사용. 열거형 상수도 있음(클래스처럼 묶어서 사용.나중에 변경불가)
        final double PI = 3.14;


        // 리터럴: 365, 'a', true, 같은 값(value)을 뜻함.
        // 구체적으로 정수리터럴, 문자리터럴, 불리언(논리)리터럴, 실수 리터럴, 문자열 리터럴 등으로 부름
        int days = 365; // 키워드(타입), 변수 = 리터럴


        // 형변환
        long longNum = 3;           // 묵시적 형변환. int3은 long보다 작은데이터라서 명시하지 않아도 됨.
        long longNum2 = 3L;         // 타입명시

        double dNum = 3.14;
        int iNum = (int)dNum;       // 명시(정보유실 가능성 있는경우 -> 버림처리)
        System.out.println(iNum);

    }
}
