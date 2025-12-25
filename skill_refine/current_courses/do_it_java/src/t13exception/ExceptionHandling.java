package t13exception;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class ExceptionHandling {

    public static void main(String[] args) {
        //1. main 에서 throws 하면 JVM으로 넘어감(사용쪽으로 미루기) -> JVM 시스템다운...
        FileInputStream fis = null;


        // 2. try catch로 제어
        try {
            fis = new FileInputStream("a.txt");
        } catch (FileNotFoundException e) {
            System.out.println(e);
            // 아래처럼 하면 또 JVM 으로 throw됨. jvm 에서 발생하면 강제종료로
            // 컨트롤 못하므로 throw 쓸 위치를 잘 생각할 것: ThrowsTest 참고
            // throw new RuntimeException(e);
        } finally {
            // 어쨌든 도달함. 보통 자원해제시 씀


            // 직접 자원 해제시 close 시도로 try 작성 또 해야됨:
            //! java7 부터 try-with-resources: 파일, 네트워크, 데이터베이스 관련 클래스들까지 묵시적 close()됨
            // 직접구현 클래스는 AutoCloseable 를 implements 하여 close() 를 @Override 해야함.
            // AutoCloseObj, AutoCloseObjTest 참고
            // 따라서 다음과 같은 명시적 close() 행동은 하지 않아도 됨.
            try {
                fis.close();
            } catch (Exception ee){
                System.out.println(ee); // fis is null
            }

            System.out.println("finally");
        }

        // catch문 이후 종료되지않고 진행됨
        // a.txt파일이 있는 상태라면 catch도달 없이 finish
        System.out.println("finish");


    }
}
