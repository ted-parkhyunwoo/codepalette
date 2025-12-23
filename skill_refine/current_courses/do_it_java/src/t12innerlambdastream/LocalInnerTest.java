package t12innerlambdastream;

class Outer {
    int outNum = 10;

    //! 지역 내부 클래스
    Runnable getRunnable(int i) {
        int num = 100;

        class MyRunnable implements Runnable {
            /*
            scope에 따라 final 처리되어 변경 불가
            +@ 자바 한계. 참조가 아니더라도 값변경 감지할땐 컴파일러 내부적으로 복사생성되도록 했어야한다고 생각함
            i = 200;
            num  = 200;
            outNum = 200;
             */

            @Override
            public void run() {
                System.out.println(i);
                System.out.println(num);
                System.out.println(outNum);
            }
        }
        return new MyRunnable();
    }


    //! 익명 내부 클래스 (객체선언없이 정의로 return) 가장많이 사용!
    Runnable getRunnable2(int i) {
        return new Runnable() {
            @Override
            public void run() { System.out.printf("익명내부클래스호출, i: %d\n", i); }
        };
    }

    //! +@ lambda로 리턴. run()이라는것을 직접 오버라이드 하지 않았는데도 작동...
    Runnable getRunnable3(int i) {
        return () -> System.out.printf("익명램다호출, i:%d\n", i);
    }


}



// test용 메인함수를 포함한 메인클래스
public class LocalInnerTest {
    public static void main(String[] args) {
        Outer outer = new Outer();

        // 지역 내부 클래스 예
        outer.getRunnable(1).run();
        // 익명 내부 클래스 예
        outer.getRunnable2(2).run();

        outer.getRunnable3(2).run();

    }

}
