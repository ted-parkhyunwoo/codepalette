package training.learning.T12_modifiers;

// 상태위주 클래스: 일반적으로 지금까지 써오던 형태.(데이터 구조체 스타일, 단순 데이터 객체)
// 기능위주의 클래스디자인: 객체를 하나만 가지도록 함.(여러 객체를 생성할 필요가 없음, 동작위주의 경우): 싱글톤

//  +@. 💡가 붙은 부분. 동작위주의 클래스에서도 메서드 뿐 아니라 변수(전역)선언 가능을 보여줌.: from google gemini
public class SingletonDesignPattern {
    // instance 는 private 접근제한자: 작성된 클래스 자체가 한개의 인스턴스만으로 전역적으로 적용됨.
    private static SingletonDesignPattern instance = new SingletonDesignPattern();

    // getter만 존재.(단 하나의 인스턴스 리턴)
    // setter는 존재하지않음(데이터클래스가 아님).
    public static SingletonDesignPattern getInstance() { return instance; }

    public int plus(int a, int b) { this.sharedStateCounter++; return a + b; }
    public int minus(int a, int b) { this.sharedStateCounter++; return a - b; }

    // 💡 추가된 상태 변수: 이 단일 인스턴스에 상태를 저장하며, 전역적으로 공유됩니다.
    private int sharedStateCounter = 0;
    public int getSharedStateCounter() { return this.sharedStateCounter; }

    public static void main(String[] args) {
        SingletonDesignPattern obj1 = getInstance();
        SingletonDesignPattern obj2 = getInstance();
        // obj1, obj2 는 다를 것 같지만 사실 전역객체를 가짐
        System.out.println(obj1 == obj2); // true

        System.out.println("plus(1, 2) 결과: " + obj1.plus(1, 2));
        System.out.println("minus(1, 2) 결과: " + obj2.minus(1, 2));

        // 💡 obj1이 연산을 호출하든, obj2가 연산을 호출하든,
        // 둘은 동일한 인스턴스를 공유하므로 상태 변수(sharedStateCounter)는 2가 됩니다.
        System.out.println("총 연산 횟수 (obj1 조회): " + obj1.getSharedStateCounter()); // 2
        System.out.println("총 연산 횟수 (obj2 조회): " + obj2.getSharedStateCounter()); // 2
    }
}