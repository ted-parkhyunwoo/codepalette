package t15thread.sync;

//! 공유자원에 대해 synchronized 하는 3가지 예.
// 이것을 하지 않으면 금액이 꼬임.
// 가령 setMoney(m + save) 중에 다른쓰레드에서 m을 바꿔버린다면 꼬일 수 있음.

class Bank {

    private int money;
    public Bank() { this.money = 10000;}
    protected void setMoney(int money) { this.money = money; }
    protected int getMoney() { return this.money; }

    //! synchronized 안하면 변수 꼬임. 작업이 끝날 때 까지 공유자원 lock 걸음.
    public synchronized void saveMoney(int save) {
        int m = this.getMoney();

        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        setMoney(m + save);
    }

    //! 혹은 이렇게 범위로 지정할 수 있음
    public void minusMoney(int minus) {
        synchronized (this) {
            int m = this.getMoney();

            try {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

            setMoney(m - minus);
        }
    }
}

class Park extends Thread {
    public void run() {
        System.out.println("예금 작업을 시작합니다.");
        SyncMainTest.myBank.saveMoney(3000);
        System.out.println("잔액: " + SyncMainTest.myBank.getMoney());
    }
}

class ParkWife extends Thread {
    public void run() {
        //! 이렇게 사용위치에서도 적용 가능.
        synchronized (SyncMainTest.myBank) {
            System.out.println("출금 작업을 시작합니다.");
            SyncMainTest.myBank.minusMoney(1000);
            System.out.println("잔액: " + SyncMainTest.myBank.getMoney());
        }
    }
}

public class SyncMainTest {
    // Park, ParkWife가 사용할 공유 객체 myBank
    public static Bank myBank = new Bank();

    // Main Test
    public static void main(String[] args) {
        Park park = new Park();
        ParkWife parkWife = new ParkWife();
        park.start();
        try {
            Thread.sleep(200);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        parkWife.start();


    }
}

