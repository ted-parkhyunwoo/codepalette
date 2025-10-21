package training.learning.T19_collection_list;
import java.util.ArrayList;
import java.util.List;
import java.util.LinkedList;

/*
ArrayList: 전통적인 배열을 기반으로 추가(혹은 삽입), 삭제 시 새로운 객체 생성.
따라서 정보 접근속도가 매우 빠름. 단점으로는 추가, 삭제가 일어나면 새로운 객체 생성 때문에 시간이 많이듬.
순차적인 정보 처리에 용이함. 단순 데이터 조회에도 빠름.
비순차적인 정보로 추가/삭제가 잦다면 연결리스트를 사용함.(노드기반)
 */

// import java.util.ArrayList; or java.util.LinkedList;
// 선언: ArrayList<자료형> or LinkedList<자료형>
// 핵심 키워드: add(), get(), set(), remove(), claer()
public class ListUse {
    public static void main(String[] args) {

        // ArrayList, LinkedList는 List인터페이스의 구현클래스다. 따라서 각 메서드 강제구현되어 상호간 전환이 간편하다.
        // List<String> myList = new ArrayList<>();             // 어레이리스트의 선언.
        List<String> myList = new LinkedList<>();               // 링크드리스트 전환시.
        ArrayList<String> test = new ArrayList<>(myList);       // 복사생성 가능.
        System.out.println(test.toString());

        //! 삽입, 조회, 수정, 삭제의 핵심은 add, get, set, remove


        // 1. 추가 및 삽입 : add(data) or add(idx, data)
        myList.add(0, "Hello");
        myList.add(1, "Hi");
        myList.add("Hello");        // 중복 허용
        myList.add(0, "insert");    // 특정인덱스에 삽입
        System.out.println(myList);

        List<String> add_data = new ArrayList<>();
        add_data.add("hoho");   add_data.add("hehe");
        myList.addAll(add_data);        // 전부추가, index에 삽입 가능.
        System.out.println(myList);


        // 2. 정보 접근(조회) : get(idx)
        System.out.println(myList.contains("Hello"));   // 특정요소 포함여부: contains(객체:요소타입)
        ArrayList<String> tmp = new ArrayList<>();
        tmp.add("insert"); tmp.add("delete");
        System.out.println(myList.containsAll(tmp));    // 모든요소 포함여부: containsAll(객체=리스트 등)
        int sz = myList.size();         // 크기 리턴
        String firstElement = myList.get(0);        // 인덱스 접근: get()
        System.out.println(firstElement);
        // String secondElement = myList[1];        // 전통적 인덱스접근 사용불가
        System.out.println("hoho's idx: " + myList.indexOf("hoho")); // 특정요소의 인덱스 리턴: indexOf, lastIndexOf

        // get, size를 이용한 전통적 반복문 접근
        for (int i = 0; i < myList.size(); ++i) { System.out.println(i + ": " + myList.get(i)); }
        // advanced for문 접근
        for (String e : myList) { System.out.println(e); }


        // 3. 수정 : set(idx, new_data)
        myList.set(0, "HELLO");         //객체수정
        System.out.println(myList);


        // 4. 삭제 : remove(idx) or remove(data), removeAll(비교배열), clear()
        myList.remove(2);               // index기반 삭제
        myList.remove("Hello");         // 객체기반 삭제(다 지우진 않음)
        System.out.println(myList);
        myList.removeAll(add_data);     // 특정 배열에 포함된 데이터를 원본에서 모두 삭제
        System.out.println(myList);

        myList.clear();                 // 모두 삭제.
        System.out.println(myList);

    }
}
