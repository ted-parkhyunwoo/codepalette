package t09interface.interfaceex2;

// 여러 interface를 상속하려는데, 둘다 동일한 이름의 디폴트메서드가 있는경우
public class Customer implements Buy, Sell {

    // 각각 없는건 그냥 구현하면 되고
    @Override
    public void buy() {
        System.out.println("customer buy");
    }

    @Override
    public void sell() {
        System.out.println("customer sell");
    }

    // default order가 둘다 있어서 충돌된다면 그냥 override
    @Override
    public void order() {
        System.out.println("customer order");
    }
}
