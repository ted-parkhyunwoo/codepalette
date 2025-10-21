package training.learning.T17_generic_class;
import java.lang.reflect.Array;

// 제네릭: 타입을 컴파일타임에 결정하도록 함. 제네릭을 사용하지 않으면 여러 타입을 Object로 다루기 때문에 매번 타입점검과 그에 따른 형변환 필요.
// <타입명> 은 아무렇게 써도 되나, 관례가 있음. 메서드제네릭 예제에서 cpp에 쓰이는 Container로 썼지만 사실 <T>가 관례임. 
// 또는 User, Product등 특정 데이터를 다루는 자료구조 이름으로 쓰기도 함.

// 기본클래스
class NormalBox {
    private Object obj;
    public void setObj(Object obj) { this.obj = obj; }
    public Object getObj() { return this.obj; }
}

// 제네릭클래스 (+@실험결과 cpp template 처럼 다중매개변수 사용 가능. template<typename T1, typename T2> : <T1, T2> )
class GenericBox<T> {
    private T t;
    public void setT(T t) { this.t = t; }
    public T getT() { return this.t; }
}

// 제네릭클래스의 범위제한: Number로 상속받은 파생클래스(기본형 숫자타입)만 T로 정함. (Number 외 예외클래스, 열거형, 특정컬렉션 등으로 제한 가능.)
class NumberBox<T extends Number> {
    public void addNums(T... nums) {
        double res = 0d;
        for (T num : nums) {
            res += num.doubleValue();       // 주의. doubleValue(); 로 모든 참조형의 숫자->double기본자료형 형변환 필요.
            // double tmp = num;         // 자동 언박싱 안됨. 명시적 형변환 필요.
            // res += (double)num;       // 안타깝지만 캐스팅 익셉션 오류: Integer, Float등은 캐스팅 안됨.
        }
        System.out.println("RESULT: " + res);
    }
}


// +@함수에서의 제네릭 
// Container 타입(아직 결정되지 않은 타입)에 length 나 [] 같은 인덱스 접근은 거부되어, reflect Array 활용(import문 참고)
class ArrayUtil {   // java 23 이하 메서드 전역공간에 넣기 안돼서, 클래스내부에 넣음. 대신 초기화 필요없는 static메서드로 사용중.
    public static <Container> void printArray(Container c) {    // static 메서드 처리로 객체선언 없이 호출가능
        if (c == null) return;

        int size = Array.getLength(c);              // length 는 Array.getLength() 활용.
        StringBuilder sb = new StringBuilder();
        sb.append('[');
        if (size > 0) sb.append(Array.get(c, 0));   // c[0] 등 인덱스 접근은 Array.get() 활용.
        for (int i = 1; i < size; ++i) {
            sb.append(", ");
            sb.append(Array.get(c, i));
        }
        sb.append(']');
        System.out.println(sb.toString());
    }
}


public class GenericClass {
    public static void main(String[] args) {

        // Object클래스를 이용한 형변환의 불편성.
        NormalBox box1 = new NormalBox();
        box1.setObj("Hello Normal");
        Object obj1 = box1.getObj();
        System.out.println((String)obj1);   // 특정타입으로 쓰려면 타입캐스팅 필요.
        if (obj1 instanceof String) { System.out.println((String)obj1); } // 특정타입에 대한 조작은 instanceof로 검사후 실행해야함.

        // 제네릭클래스 활용
        GenericBox<String> box2 = new GenericBox<>();       // <명시>하거나, <>형태로 비우거나(권장), 생략 가능(권장x)
        box2.setT("Hello Generic");
        System.out.println(box2.getT());

        // 제네릭클래스의 타입제한: Number클래스 파생클래스(정수,실수형 등)만 받도록.
        NumberBox<Number> box3 = new NumberBox();           // 원시타입. 권장하지않음. <>를 넣을것.
        box3.addNums(1, 2, 3, 4, 5.5, 6.6);
        NumberBox<Integer> box4 = new NumberBox<Integer>();        // Number의 하위 파생클래스들도 가능.
        box4.addNums(1,2,3,4,5);


        // +@메서드제네릭 활용
        int[] arr = {1,2,3};
        ArrayUtil.printArray(arr);
        Character[] arr2 = {'J','A','V','A'};
        ArrayUtil.printArray(arr2);
        String arr3 = "HELLO";
        // ArrayUtil.printArray(arr3);  // java의 문자열은 배열이 아니라서 Array.getLength를 사용할 수 없다.

    }
}
