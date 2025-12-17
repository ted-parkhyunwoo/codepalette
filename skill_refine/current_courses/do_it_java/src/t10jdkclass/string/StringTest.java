package t10jdkclass.string;

public class StringTest {
    public static void main(String[] args) {
        // 각각 힙에 선언되므로 엄연히 다른 참조
        String str1 = new String("abc");
        String str2 = new String("abc");

        System.out.println(str1 == str2);
        // 따라서 String 값비교는 equals를 사용하도록 함.
        System.out.println(str1.equals(str2));

        // 컴파일 타임에 모든 리터럴을 파악하므로 상수풀 선언된 리터럴을 동일 포인팅
        // 이후 참조 없으면 gc처리됨(java7 이후: 이전엔 재정의시 out of memory 문제 됐음. gc되지않음. 현재는 heap의 일부에 저장하여 gc)
        String str3 = "abc";
        String str4 = "abc";

        System.out.println(str3 == str4);
        System.out.println(str3.equals(str4));

        // 심지어 이거마저 동일해짐. (컴파일러가 "abc" 로 처리)
        String str5 = "ab" + "c";
        System.out.println(str3 == str5);
        System.out.println(str3.equals(str5));


        // java는 문자열이 불변성임. (잦은 + 합치는 연산등을 사용하지 않도록 권장)
        // 따라서 이런 사용을 자주 하면 한번만 쓰고 쌓이는 객체들이 너무 많이 생김.

        // c++참고: std::string 은 가변이지만 + 연산시 새로운 임시객체를 생성.
        // += 를 쓰거나 캐파를 미리 할당 str.reserve(100) 혹은 stringstream 활용
        String str6 = str1.concat(str2);    // 두개를 합쳐 새로운 객체로 만듬
        String str7 = str1 + str2;          // 마찬가지
        System.out.println(str6);
        System.out.println(str7);

        // 따라서 String builder(Single Thread), string buffer(Multi Thread) 를 사용.
    }
}
