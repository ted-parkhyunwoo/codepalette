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

        //! +@ java 특성상 선언된 타입(Buy, Sell) 에 따라 order() 가 다르게 작동하는것은 instance of 등으로는 불가: Sell이기도 하고 Buy 이기도 하고 Customer 이기도 하기 때문
        // 타입에 관한 힌트 멤버를 넣어 초기화 하면 Buy.super.order() 나 Sell.super.order() 등으로 강제로 사용은 가능

    }
}
