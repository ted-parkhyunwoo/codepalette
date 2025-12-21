package t11collectionframework.collection.hashset;

import t11collectionframework.collection.Member;

public class MemberHashSetTest {
    public static void main(String[] args) {
        MemberHashSet memberHashSet = new MemberHashSet();

        memberHashSet.addMember(new Member(1000, "김상철"));
        memberHashSet.addMember(new Member(1001, "박철호"));
        memberHashSet.addMember(new Member(1002, "안철수"));

        memberHashSet.showAllmember();

        memberHashSet.removeMember(1000);
        memberHashSet.showAllmember();

        // 이미 있는 memberId로 시도: 무시됨(Member에 hashCode,equals를 재정의, hash set사용)
        // hash set은 해시기반, equals를 둘다 평가해서 객체가 같음을 논리비교함.
        memberHashSet.addMember(new Member(1001, "테스트"));
        memberHashSet.showAllmember();


    }
}
