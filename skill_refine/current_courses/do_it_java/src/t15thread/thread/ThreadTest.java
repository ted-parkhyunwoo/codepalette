package t15thread.thread;

class MyThread extends Thread {
    public void run() {
        for (int i = 0; i < 200; ++i) {
            System.out.println(Thread.currentThread().getName() + ":" + i + "\t");
            try {
                // sleep은 try-catch로 감싸야 함
                sleep(10);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}

class MyRunnable implements Runnable {
    @Override
    public void run() {
        for (int i = 0; i < 200; ++i) {
            System.out.println(Thread.currentThread().getName() + ":" + i + "\t");
            try {
                // sleep을 Thread.sleep으로 써야함.
                Thread.sleep(10);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}

public class ThreadTest extends Thread {

    public static void main(String[] args) {
        System.out.println(Thread.currentThread().getName());

        // Thread 클래스(extends Thread) 로 실행
        MyThread t1 = new MyThread();
        MyThread t2 = new MyThread();

        t1.start();
        t2.start();
        System.out.println(Thread.currentThread().getName());

        // Runnable 구현체를 Thread객체로 생성후 실행
        Thread r1 = new Thread(new MyRunnable());
        Thread r2 = new Thread(new MyRunnable());
        r1.start();
        r2.start();


    }
}
