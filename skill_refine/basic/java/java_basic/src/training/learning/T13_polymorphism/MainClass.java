package training.learning.T13_polymorphism;

// 다형성(Polymorphism): 클래스 기본 구조는 testcodes의 classtest를 가져옴.
// ParentClass 는 이름, 나이를 담는 데이터클래스이며 기본클래스.
// ChildClass 는 ParentClass 기능에 키(height)를 담는기능을 덧붙인 확장클래스이며 파생클래스. sayHello메서드도 확장추가됨

public class MainClass {

    public static void main(String[] args) {
        // 파생클래스만 사용: 이름, 나이, 키 출력됨.
        ChildClass haha = new ChildClass(42, "haha", 172.323f);
        System.out.println(haha);

        // 기본클래스만 사용: 이름, 나이만 출력됨.
        ParentClass haha1 = new ParentClass(27, "haha1");
        System.out.println(haha1);


        // 1. 다형성 기초.
        // ParentClass타입에 ChildClass타입을 초기화(참조됨. 얕은복사. 원치않으면 복사생성자 작성과 사용 필요)
        // cpp와 다르게 slicing(자식기능의 상실)이 일어나지 않음. 원형 그대로 메모리를 참조하기 때문. cpp에서 구현하려면 가상함수와 참조(*, &) 처리 필요.
        // java는 파생객체를 기본타입으로 생성했는데도 불구하고 원래 기능을 유지하는 성질이 있음(명시적 형변환 필요.)
        ParentClass haha2 = haha;    // 참조됨. 얕은복사처리, 묵시적(암묵적) 형변환.
        ParentClass haha3 = new ChildClass(33, "haha3", 159.4f);    // 새로 할당됨. 암묵적 형변환.
        Object haha4 = new ChildClass();    // Object도 가능.(java의 최고 조상클래스)
        haha2.setAge(56);
        haha2.setName("haha2");
        // haha2.setHeight(170.1f);     // haha2의 setHeight, getHeight접근 안됨. 하지만 메모리에는 있어서  toString()으론 height를 불러올 수 있음.
        System.out.println(haha2);      // 기본객체가 동적바인딩(Override)로 인한 파생클래스의 Override를 따름.
        System.out.println(haha3);
        System.out.println(haha4);


        // 2. 명시적 형변환.
        // setHeight(), sayHello()는 파생클래스 기능으로, 메모리에는 존재하는 상태.
        ((ChildClass)haha3).setHeight(165.f);   // 명시적 형변환 필요.
        ((ChildClass)haha3).sayHello();
        // 모호성: cpp의 추상클래스처럼 java의 Object클래스에선 모든메서드가 virtual로 선언된 가상메서드이고, 아주 적극적으로 동적바인딩을 유도함. Ovject 클래스에서  toString()을 그저 참조하고있기때문에(가상함수포인팅), 기본클래스 override된 toString() 사용이 안되고, 객체의 본질타입(파생클래스)의 override를 따름.
        System.out.println(haha3.toString());

        // 명시적 형변환 주의사항: 파생선언에 기본생성 사용 자제.
        ParentClass Parent = new ParentClass();
        // ChildClass fakeChild = (ChildClass) Parent; // 클래스 캐스트 익셉션 오류!
        // 해결: instanceof 연산자 활용(객체의 실제타입을 비교하는 연산)
        if (Parent instanceof ChildClass) {
            ChildClass fakeChild = (ChildClass) Parent;
            fakeChild.sayHello();
        } else { System.out.println("형변환 실패"); }

        // 배열: 다형성은 상위타입이라면 다 됨. Object 타입으로도 가능함.
        ParentClass[] array = new ParentClass[5];
        array[0] = haha;
        array[1] = haha2;
        array[2] = haha3;
        array[3] = new ChildClass();
        // array[4] = haha4;   // 상속관계 반대로는 안들어감.(자식 <- 부모 허용x)
        // 마찬가지로 파생클래스에만 있는 기능을 사용시 명시적 형변환 필요.
        ((ChildClass)array[2]).sayHello();


        // 3. Wrapper Class: 기본형을 객체형으로 변환; Object형으로 사용가능해짐.
        Integer i = (int)3;     // boxing이라 함.
        Character c = (char)'C';
        String s = "String";    // 이미 참조자료형
        int I = i;  // unboxing이라 함.

        // 따라서 어떤 자료형이든 Object로 관리가능 - 권장하지않음.
        Object[] ObjArray = new Object[5];
        ObjArray[0] = i;
        ObjArray[1] = c;
        ObjArray[2] = s;
        ObjArray[3] = haha;
        ObjArray[4] = (Integer)I;
        System.out.println(ObjArray[4]);
        /*
        ObjArray[4] 의 인스턴스 객체는 null로 지정하면 메모리 해제됨.
        모든 Object 객체는 참조자료형이고 heap에 올라감.
        java는 가비지콜렉터가 알아서 정리함.
        참고로, 전통적배열 int[] 스타일도 heap에 올라감.
        */
    }
}
