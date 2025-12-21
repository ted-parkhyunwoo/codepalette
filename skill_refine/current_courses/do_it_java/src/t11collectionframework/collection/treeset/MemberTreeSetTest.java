package t11collectionframework.collection.treeset;

import t11collectionframework.collection.Member;

public class MemberTreeSetTest {
    public static void main(String[] args) {
        MemberTreeSet memberHashSet = new MemberTreeSet();

        memberHashSet.addMember(new Member(1000, "김상철"));
        memberHashSet.addMember(new Member(1001, "박철호"));
        memberHashSet.addMember(new Member(1002, "안철수"));

        memberHashSet.showAllmember();


        memberHashSet.addMember(new Member(1001, "테스트"));
        memberHashSet.showAllmember();


    }
}
