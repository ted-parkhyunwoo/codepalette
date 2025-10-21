package training.learning.T14_dynamic_bind;

import java.util.Arrays;

// T13에 나온 동적바인딩(런타임에 타입 결정)을 구체화한 코드.

public class Main {
    public static void main(String[] args) {
        Parent p = new Child();
        // 기본클래스로 선언된 파생객체는 java에선 무조건 참조처리되기때문에 의도적으로 slicing을 할 수 없음. 
        // 굳이 원한다면 복사생성자를 활용하거나, 파생클래스에서 기본타입의 객체로 return받는 함수화 필요.
        System.out.println(p.str());

        // 기본타입(Parent) 로 기본과 파생객체를 다룰 시.
        Parent[] ps = { new Parent(), new Child() };
        for (Parent e : ps) {
            System.out.print("func()호출: ");
            e.func();
            if (e instanceof Child) {
                System.out.print("Child 타입의 강제 형변환 및 Slicing시도: ");  
                ((Parent)e).func();     // 실패. 선언 혹은 캐스팅된 타입에 상관 없이 상관없이, 객체의 본질타입의 func()를 따름.
            }
        }

        // Object로 관리시 모든 참조자료형을 넣을 수 있음.
        Object[] objs = new Object[5];
        objs[0] = new Child();
        objs[1] = new Parent();
        objs[2] = "abcdefg";
        int[] arr = new int[5];         // 원칙상 전통적배열도 참조자로형이라 Object로 관리 가능.
        for (int i = 0; i < 5; i++) arr[i] = i;
        objs[3] = arr;
        objs[4] = (Character)'C';       // 래퍼클래스 (Boxing): 기본자료형char -> 참조자료형 Character
 
        // Object 요소 출력.
        System.out.println(((Child)objs[0]).str());
        System.out.println(((Parent)objs[1]).str());
        System.out.println(((String)objs[2]));
        System.out.println(Arrays.toString((int[])objs[3]));    // int[] 캐스팅 후 Arrays.toString
        System.out.println((char)objs[4]);
    }
}
