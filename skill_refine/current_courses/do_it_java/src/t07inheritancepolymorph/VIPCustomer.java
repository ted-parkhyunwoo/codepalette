package t07inheritancepolymorph;

public class VIPCustomer extends Customer {
    // 상속클래스에서의 추가된 기능만 멤버로 추가.
    // 변경기능은 override 하는것이 핵심
    private int agentID; // 담당자ID명시가 추가됨
    double salesRatio; // 할인율이 추가됨

    // ! this, super 는 대개 똑같지만, 기본과 상속의 멤버(변수,함수) 이름이 같은 멤버가 존재한다면 호출되는 멤버가 달라짐!!

    VIPCustomer() {
        // ! java 이상하게도 super() 를 하지 않아도 묵시적인 호출 일어남.
        // cpp, python등에선 직접 기본클래스생성자 Base()나 __super()__ 등을 명시.
        super.customerGrade = "VIP";
        super.bonusRatio = 0.05;
        this.salesRatio = 0.1; // 10프로 할인율
        System.out.println("VIPCustomer 기본생성자 호출");
    }

    VIPCustomer(String customerName, int agentID) {
        this();
        this.customerName = customerName;
        this.agentID = agentID;
        System.out.println("VIPCustomer 이름, 담당자아이디 생성자 호출");
    }

    // 오버라이드(기능 변경시 재정의)
    @Override
    public int calcPrice(int price) {
        // 할인 적용
        return super.calcPrice(price) - (int) (price * salesRatio); // int다운캐스팅 명시
    }

    @Override
    public String toString() {
        return super.toString() + "\t Agent: " + this.agentID + "\t SalesRatio: " + salesRatio;
    }
}
