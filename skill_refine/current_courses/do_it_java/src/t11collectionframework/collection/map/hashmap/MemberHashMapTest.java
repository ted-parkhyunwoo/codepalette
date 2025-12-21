package t11collectionframework.collection.map.hashmap;

import t11collectionframework.collection.Member;

public class MemberHashMapTest {
    public static void main(String[] args) {
        MemberHashMap memberHashMap = new MemberHashMap();
        memberHashMap.addMember(new Member("김상철"));
        memberHashMap.addMember(new Member("우주인"));
        memberHashMap.addMember(new Member("박찬호"));

        memberHashMap.showAllMember();

        memberHashMap.removeMember(1003);       // 실패
        memberHashMap.removeMember(1000);       // 성공

        memberHashMap.showAllMember();
    }

}
