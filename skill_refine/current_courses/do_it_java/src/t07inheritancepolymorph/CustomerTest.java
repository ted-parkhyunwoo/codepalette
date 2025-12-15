package t07inheritancepolymorph;

public class CustomerTest {
    public static void main(String[] args) {
        Customer a = new Customer();
        System.out.println();
        Customer b = new Customer("kim");
        System.out.println();
        VIPCustomer c = new VIPCustomer();
        System.out.println();
        VIPCustomer d = new VIPCustomer("park", 123);
        System.out.println();

        System.out.println(a);
        System.out.println(b);
        System.out.println(c);
        System.out.println(d);

        int bPrice = b.calcPrice(1000);
        int dPrice = d.calcPrice(1000);
        System.out.println(bPrice);
        System.out.println(dPrice);
        System.out.println(b);
        System.out.println(d);

        // 다형성: 인스턴스가 a라는 타입이기도 하면서 상속관계의 b라는 타입이기도 하는 성질
        // 형변환: 묵시적 업캐스팅
        Customer e = new VIPCustomer("Lee", 1234);
        int ePrice = e.calcPrice(1000); // ! 가상메서드를 참조하며, 선언된 타입이 아니라 인스턴스의 타입으로 호출됨. 따라서 선언된 타입과 다르게 실제 인스턴스의 멤버호출됨.
        System.out.println(ePrice);
        System.out.println(e);

        // cpp의 경우에는 동일한것을 구현하려면 기본클래스에서 virtual 함수로 선언하거나 virtual 함수() = 0 같은 순수가상함수로
        // 만든 후 (추상클래스, 인터페이스클래스화), 기본클래스* 로 참조선언하여야 하지만 java는 이런면에선 편리한듯

        // 따라서 java의 멤버는 자동으로 모두가 virtual 키워드 선언된 것이라 생각하면 됨.

        // 다운캐스팅(문제 없을시만 정상작동됨. cpp의 static_cast<타입> 같은 안전장치가 없음)
        VIPCustomer f = (VIPCustomer) e;

        // 타입점검방법
        System.out.println("getClass(). 클래스.class리터럴 활용");
        System.out.println(e.getClass());
        System.out.println(f.getClass());
        System.out.println(e.getClass() == VIPCustomer.class);

        System.out.println("instanceof 활용");
        System.out.println(e instanceof Customer);
        System.out.println(e instanceof VIPCustomer);
        System.out.println(f instanceof Customer);
        System.out.println(f instanceof VIPCustomer);
        System.out.println(a instanceof VIPCustomer);

        System.out.println("이런식으로도 인스턴스 타입 확인 가능");
        System.out.println(VIPCustomer.class.isInstance(e));
        System.out.println(Customer.class.isInstance(f));
        System.out.println(VIPCustomer.class.isInstance(a));

        // 형변환: 안전한 다운캐스팅 유의사항. static_cast가 없으니 직접 구현해서 써야함.
        VIPCustomer g;
        Customer target = a; //! a, c 등 기본타입과 상속타입을 테스트 해볼 것.
        if (target instanceof VIPCustomer vip) { // vip 생략가능하나 필요시 이렇게도 쓸수있음
            g = (VIPCustomer) target; // 캐스팅은 기본자료형과 동일하며 (int)3.14d처럼 작동
            g = vip; // 혹은 이렇게 사용가능
            System.out.println("다운캐스팅 성공");
            System.out.println(vip.calcPrice(100));
        } else {
            System.out.println("다운캐스팅 오류");
            g = new VIPCustomer();
        }

        System.out.println(g);
    }
}
