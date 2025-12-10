package t05class2;

// Bus와 거의 같음(lineNumber가 String, BusNumber가 int인점 빼고).
// Traffic 등으로 인터페이스화 시킬 수 있겠지만 학습이 그 단계는 아니라 따로 구현

public class Subway {
    String lineNumber;
    int passengerCount;
    int money;

    public Subway(String lineNumber) { this.lineNumber = lineNumber; }

    public void take(int money) {
        this.money += money;
        passengerCount++;
    }

    public void showInfo() {
        String info = "LineNumber: " + this.lineNumber + " Passengers: " + this.passengerCount + " money: " + money;
        System.out.println(info);
    }

}
