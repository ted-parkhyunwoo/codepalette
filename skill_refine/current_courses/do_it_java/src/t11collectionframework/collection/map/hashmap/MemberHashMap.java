package t11collectionframework.collection.map.hashmap;

import java.util.HashMap;
import java.util.Iterator;

import t11collectionframework.collection.Member;

//! 유심히 볼건 put, get, remove, iterator(키기반), containsKey(키 포함여부)

public class MemberHashMap {
    private HashMap<Integer, Member> memberHashMap;

    MemberHashMap() { memberHashMap = new HashMap<>(); }

    public void addMember(Member member) {
        // Integer 는 member의 ID, member는 member 객체 그 자체
        memberHashMap.put(member.getMemberId(), member);
    }

    public boolean removeMember(int memberId) {
        if (memberHashMap.containsKey(memberId)) {
            String name = memberHashMap.get(memberId).getMemberName();
            memberHashMap.remove(memberId);
            System.out.printf("id: %d, name: %s 삭제 성공\n", memberId, name);
            return true;
        }
        System.out.printf("id: %d 삭제 실패\n", memberId);
        return false;
    }


    public void showAllMember() {
        // key 기반으로 Integer 이터레이터 생성
        Iterator<Integer> it = memberHashMap.keySet().iterator();
        while (it.hasNext()) {
            System.out.println(memberHashMap.get(it.next()));
        }

    }


}
