package src.list;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class usingList {
    public static void main(String[] args) {
        // 전통배열 선언과 초기화
        String[] array = new String[] {"Hello", "World", "Welcome", "To", "Java"};
        
        // 각 콜렉션에 복사생성해보기. (ArrayList와 LinkedList는 List인터페이스의 구현클래스. 메서드들이 겹치며, 복사생성이 가능)
        List<String> array1 = new ArrayList<>(Arrays.asList(array));        // Arrays.asList를 통해 전통적인 배열을 List객체전환할 수 있다.
        List<String> array2 = new LinkedList<>(array1);
        // 전통배열선언과 초기화처럼 사용해볼때
        ArrayList<String> test = new ArrayList<>(Arrays.asList("Hello", "World", "Welcome", "To", "Java"));
        array1 = test;

        // 배열자체 문자열출력: List인터페이스는 toString()을 Override해서 자동으로 됨.
        System.out.println(Arrays.toString(array));
        System.out.println(array1);
        System.out.println(array2);


        // 정보접근.
        // 전통적인 배열은 추가/삭제가 불가능하다. (선언된 배열의 크기 변경(재할당) 불가.)
        array[0] = "hello";                     // 수정
        System.out.println(array[0]);           //조회


        //! List 콜렉션은 add, remove, get, set이 중심. '인덱스기반'에 더 효과적인 ArrayList와 궁합이 잘맞는다.
        array1.add("ted");                      // 요소추가
        array1.add(5, "안녕");                  // 특정 인덱스에 요소 삽입
        array1.addAll(7, Arrays.asList("만나서", "반갑습니다"));        // 특정 인덱스에 객체삽입.
        System.out.println(array1);             // [Hello, World, Welcome, To, Java, 안녕, ted, 하세요, 반갑습니다]

        array1.set(6, "Hyeree");                // 특정인덱스 요소 수정 : set(idx, 값)
        System.out.println(array1.get(6));      // 특정인덱스 요소 리턴 : get(idx)
        
        array1.remove(array1.size() - 1);       // 특정인덱스 요소 삭제, size() 활용
        array1.removeAll(Arrays.asList("만나서", "반갑습니다", "하하하"));        // 교집합요소 삭제
        System.out.println(array1);             // [Hello, World, Welcome, To, Java, 안녕, Hyeree]
        
        array1.clear();                         // 모두삭제
        System.out.println(array1);             // []
        array1 = array2;                        // 재할당
        System.out.println(array1);             // [Hello, World, Welcome, To, Java, 안녕, Hyeree]


    }
}
