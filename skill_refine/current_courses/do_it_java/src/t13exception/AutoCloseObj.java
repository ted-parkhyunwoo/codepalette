package t13exception;


//! cpp의 소멸자, 거의 비슷한건 dart 의 dispose() 처럼, close를 override하여 사용
// finalize() 라는 소멸자개념이 있었으나, 성능/안정성 문제로 폐기수순이며 거의 금지된 방법

public class AutoCloseObj implements AutoCloseable{
    @Override
    // 이외 발생할지도 모르는 또 다른 예외는 throws
    public void close() throws Exception {
        // 이곳에 자원 회수를 위한 코드를 적음
        System.out.println("Auto Close obj");
    }
}
