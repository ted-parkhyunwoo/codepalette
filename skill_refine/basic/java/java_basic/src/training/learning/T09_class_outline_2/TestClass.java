package training.learning.T09_class_outline_2;
// 4. 패키지 선언은 하나만 선언됨: 회사도메인.프로젝트.특성(용도);
// 생략시 default package에 속하지만 이런 코드는 권장하지않음
// @+ src 내 .은 디렉토리별로 구분됨.


// 5. import: 참고로 java.lang 패키지는 자동 import.
import java.text.SimpleDateFormat;
import java.util.Date;


// 6. 일반적인 클래스 구조: 반드시 따를 필요는 없지만 관례.
// 파일구조: 패키지선언, 외부패키지(import), 클래스  순서.
// 클래스구조: class 선언, 멤버변수 선언, 초기화블록, 생성자, 메서드 순서.
// 협업용 모델링체계는 UML 클래스 다이어그램을 따름(구조설명과 기능묘사: cpp의 h헤더파일의 내용과 같은 느낌이며, 내용은 비슷하지만 사실 cpp의 헤더는 구조 설명이라기보단, 구현을 위한 문법적인 코드 요소임.)


public class TestClass {


    // 1. static 멤버변수: 인스턴스와 무관, 객체생성없이 접근/수정가능.
    static String name;
    int num;    // 일반멤버변수, 인스턴스변수.


    // 3. 초기화 블록(Initializer Blocks.) : 한번만 호출됨
    // 생성자호출 전에 실행되는 블록: +@ 컴파일 된 .class파일을 보면, 생성자 내부로 들어가도록 번역됨.
    // 인스턴스 초기화블록
    {
        System.out.println("Instance Initializer.");
        num = 0;
    }
    // 스태틱 초기화블록: 초기화블록에도 static 지정하여 객체 생성 없이도, 메모리의 클래스영역에서 다루어짐.
    static {
        System.out.println("Static Initializer.");
        name = "EMPTY";
    }

    public TestClass() {}
    public TestClass(int num) { this.num = num; }

    // 2. static 메서드 대표적인 예: main 함수, Math.함수
    // 특징: 인스턴스와 무관한 동작.
    static void sayHello() {
        System.out.println("Hello " + name);
    }

    // 일반멤버(인스턴스 메서드, 객체명.메서드 처럼 객체를 통해서 접근.)
    public void print() {
        System.out.println(name + " " + num);
    }


    public static void main(String[] args) {
        TestClass.sayHello();   // 초기화블록 출력 테스트.
        // static 키워드로 생성된 변수는 메모리(클래스영역)에 따로저장됨.
        TestClass.name = "park";  // 따라서 객체생성 없이 변경가능.

        TestClass a = new TestClass(2);
        // b는 초기화블록의 정상작동 덕에 num이 자동 초기화됨
        TestClass b = new TestClass();
        /* +@ 다양한 멤버변수의 초기화.
        클래스 내 int num = 0; 으로 선언과 동시에 초기화
        클래스 기본생성자에 { num = 0; } 으로 대입
        객체.num = 0; 으로 직접 대입
        클래스 내 { num = 0; } 으로 대입: 인스턴스 초기화블록.
         */

        // 하나만 바꿔도 모든 객체의 값이 동기화되어버림.
        a.name = "ted"; // 위와 다르게 권장되지 않는 사용방식.
        a.print();  // 일반멤버 호출.
        b.print();

        // 스태틱멤버 호출.
        TestClass.sayHello();


        // import 된 라이브러리 사용
        SimpleDateFormat sdf = new SimpleDateFormat();
        Date d = new Date();

    }
}