package t09interface.interfaceex2;

public class CustomerTest {
    public static void main(String[] args) {

        // 어떤 타입으로 선언되느냐에 따라 객체가 다르게 작동(buy, sell사용불가)

        // sell 은 호출 불가
        Buy buy = new Customer();
        buy.buy();
        buy.order();    // 오버라이드 돼서 디폴트가 아님!

        // buy 는 호출 불가
        Sell sell = new Customer();
        sell.sell();
        sell.order();   // 마찬가지로 디폴트가 아님


        // 모두사용시
        Customer customer = new Customer();
        customer.buy();
        customer.sell();
        customer.order();

    }
}
