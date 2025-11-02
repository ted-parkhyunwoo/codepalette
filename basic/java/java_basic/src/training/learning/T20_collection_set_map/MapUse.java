package training.learning.T20_collection_set_map;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;


public class MapUse {
    public static void main(String[] args) {
        // 선언. int가 들어가지 않음. 참조자료형만 가능한듯.
        HashMap<String, Integer> map = new HashMap<>();

        // 추가/수정이 같음.
        map.put("김상철", "김상철".hashCode());
        System.out.println(map);
        map.put("김상철", 1234);        // 수정
        System.out.println(map);

        HashMap<String, Integer> map2 = new HashMap<>();
        map2.put("고인돌", 4324);
        map2.put("우주인", 1234);
        map.putAll(map2);               // 모두 추가.
        System.out.println(map);

        // 조회: 조회기능이 많음.
        // containsKey(Object key),  containsValue(Object value)  -> return boolean
        System.out.println(map.containsKey("김상철"));      // 키 포함여부 - true
        System.out.println(map.containsValue(1234));        // 값 포함여부 - true

        // entrySet()
        // System.out.println(entrySet());  //??

        // 키, value 의 set형태와 배열형태(value) 리턴
        // KeySet(), values(). values()는 중복도 같이 표시됨.
        System.out.println(map.keySet());               // hashmap 자체가 애초에 키를 중복 할 수 없는 구조.
        System.out.println(map.keySet().getClass());    // class java.util.HashMap$KeySet :set 스타일.중복허용X
        System.out.println(map.values());               // 1234는 두 번 포함되므로 두개가 출력됨.
        System.out.println(map.values().getClass());    // class java.util.HashMap$Values
        
        // get(Object key)
        System.out.println(map.get("김상철"));          // 키 기반 value 조회
        System.out.println(map.get(""));                // null return

        System.out.println(map.size());                 // 크기 return
        System.out.println(map.isEmpty());              // false

        // key 기반 순회.
        for (String key : map.keySet()) {
            System.out.println(key);
        }

        // +@ keySet() 과 values() 객체를 이용한 새로운 set, list 선언
        HashSet<String> mapsKey = new HashSet<>(map.keySet());
        ArrayList<Integer> mapsValues = new ArrayList<>(map.values());
        System.out.println(mapsKey);
        System.out.println(mapsValues);


        // 삭제: removeAll로 다른 맵 기반 교집합 삭제 기능은 없음. 직접 범위기반(객체.keySet()활용) key로 지워야함.
        map.remove("김상철");
        System.out.println(map);
        map2.clear();                                   // 모두 삭제
        System.out.println(map2);

    }

}
