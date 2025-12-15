package t07inheritancepolymorph;

public class Customer {
    // 상속클래스가 멤버접근할 수 있게 protected로 선언됨.
    static private int customerBuffer = 1000; // ID부여 정적멤버는 Customer가 전적관리해서 private.
    protected int customerID;
    protected String customerName;
    protected String customerGrade;
    int bonusPoint; // 포인트
    double bonusRatio; // 적립율

    public Customer() {
        this.customerID = customerBuffer++;
        customerGrade = "SILVER";
        bonusRatio = 0.01;
        System.out.println("Customer 기본생성자 호출");

    }

    public Customer(String customerName) {
        this(); // +@ 첫문장에만 허용
        this.customerName = customerName;
        System.out.println("Customer 이름추가 생성자 호출");
    }

    public int calcPrice(int price) {
        bonusPoint += price * bonusRatio;
        return price; // 보너스 적립.(할인 없음)
    }

    @Override
    public String toString() {
        return "ID: " + customerID + "\tName: " + customerName + "\tGrade: " + customerGrade + "\tPoint: "
                + bonusPoint + "\tratio: " + bonusRatio;
    }
}