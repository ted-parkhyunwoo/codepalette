package t13exception;

public class AutoCloseObj implements AutoCloseable{
    @Override
    // 또 다른 예외는 throws함.
    public void close() throws Exception {
        System.out.println("Auto Close obj");
    }
}
