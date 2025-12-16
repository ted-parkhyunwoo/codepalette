package t09interface.interfaceex;

public class CompleteCalc extends Calculator{
    @Override
    public int mul(int a, int b) {
        return a * b;
    }

    @Override
    public int div(int a, int b) {
        return (int)(a / b);
    }

    public  void showInfo() {
        System.out.println("CompleteCalc ShowInfo()");
    }
}
