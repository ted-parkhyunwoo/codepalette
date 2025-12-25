package t13exception;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class ThrowsTest {
    // 예외를 사용쪽에서 처리하도록 미루기: throws
    public Class loadClass(String fileName, String className) throws FileNotFoundException, ClassNotFoundException {
        // file처리
        FileInputStream fis = new FileInputStream(fileName);
        // Class 이름을 동적로딩 하는 메서드
        Class c = Class.forName(className);
        return c;
    }

    public static void main(String[] args) {
        ThrowsTest throwsTest = new ThrowsTest();

        try {
            throwsTest.loadClass("test.txt", "aaa.bbb.CCC");
        } catch (FileNotFoundException | ClassNotFoundException e) {
            // 따로 작성도 되나, 위처럼 파이프라인으로 두가지 다 e로 받을 수 있음.
            System.out.println(e);
        } catch (Exception e) {
            // 이외 알수없는 예외는 최상위 예외클래스 사용: 당연히 맨 아래에 작성
            System.out.println(e);
        }

        System.out.println("finish");

    }
}
