package sixth;

public class Bus {
    int busNumber;
    int passengerCount;
    int money;

    public Bus(int busNumber) { this.busNumber = busNumber; }

    // int money 대신 객체의 타입 검사와 Student의 setMoney()를 통해 가격부여를 할 수 있겠지만, 그 단계는 아니라 간단하게 구현
    // 그렇게 된다면 Student 대신 Human 같은 추상클래스나 인터페이스가 필요할 듯.
    public void take(int money) {
        this.money += money;
        passengerCount++;
    }

    // 상태출력 메서드
    public void showInfo() {
        String info = "BusNumber: " + this.busNumber + ", Passengers: " + this.passengerCount + ", money: " + money;
        System.out.println(info);
    }
}
