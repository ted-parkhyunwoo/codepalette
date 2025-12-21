package t11collectionframework.collection.treeset;

import java.util.Iterator;
import java.util.TreeSet;

import t11collectionframework.collection.Member;

//! String같은 기본 구현된 참조자료형들엔 문제 없지만 Member 같은 커스텀 타입의 경우, Comparable 구현 후 compareTo 오버라이딩 해야함

public class MemberTreeSet {
    private TreeSet<Member> treeSet;
    public MemberTreeSet() { this.treeSet = new TreeSet<>(); }

    public void addMember(Member member) {
        treeSet.add(member);
    }

    public boolean removeMember(int memberId) {
        Iterator<Member> it = treeSet.iterator();

        while (it.hasNext()) {
            Member bf = it.next();
            int bfId = bf.getMemberId();
            if (bfId == memberId) {
                it.remove();
                System.out.printf("%d 삭제 성공\n", memberId);
                return true;
            }
        }

        System.out.printf("%d 삭제 실패\n", memberId);
        return  false;
    }

    public void showAllmember() {
        for (Member e : treeSet) {
            System.out.println(e);
        }
    }



}
