package t11collectionframework.collection.arraylist;

import t11collectionframework.collection.Member;

public class MemberArrayListTest {
    public static void main(String[] args) {
        MemberArrayList memberArrayList = new MemberArrayList();

        memberArrayList.addMember(new Member("이씨"));
        memberArrayList.addMember(new Member("김씨"));
        memberArrayList.addMember(new Member("박씨"));
        memberArrayList.addMember(new Member("홍씨"));

        memberArrayList.showAllMember();        // 멤버 출력

        memberArrayList.removeMember(1004);     // 삭제불가한 멤버 시도
        memberArrayList.removeMember(1000);     // 삭제가능 시도

        memberArrayList.showAllMember();        // 삭제 후 출력
    }
}
