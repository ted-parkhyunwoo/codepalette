package training.learning.T01_06_basic;

public class T02_type {
    public static void main(String[] args) {
        // 기본형 자료형.
        byte b1 = 127;      // 1bytes, 8bits
        int i1 = 999;       // 4bytes, 32bits
        short s1 = 3213;    // 2bytes, 16bits
        long l1 = 234234L;  // 8bytes, 64bits

        System.out.println(s1);
        System.out.println(l1);

        // 데이터를 담는 바이트수에 따라 형변환시 정보 손상가능성 있음

        byte b2 = (byte)i1; // 명시적 형변환, 정보 손상(알수 없는값)
        int i2 = b1;        // 묵시적 형변환

        System.out.println(b2);
        System.out.println(i2);

        float f1 = 3.14159265358979f;   // 4bytes, 약 7자리 소수
        double d1 = 3.14159265358979d;  // 8bytes, 약 15자리 소수

        float f2 = (float)d1;   // 정보 일부 손상(반올림)
        double d2  = f1;        // 정보 일부 손상(없는값이 채워짐)

        System.out.println(f2);
        System.out.println(d1);
        System.out.println(d2);

        boolean bool1 = true;
        bool1 = false;

        // 기본형 자료형중 불리언만 형변환 불가.
        // byte test = (byte) bool1;

        System.out.println(bool1);

        char c1 = 'A';
        int i3 = c1;    // 묵시적, 65
        System.out.println(i3);

        // 이외 자료형은 거의 모두다 참조형 자료형.
        String str = "Hello";
        System.out.println(str);


    }
}
