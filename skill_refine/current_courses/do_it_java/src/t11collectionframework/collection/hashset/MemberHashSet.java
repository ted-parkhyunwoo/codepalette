package t11collectionframework.collection.hashset;

import java.util.HashSet;
import java.util.Iterator;

import t11collectionframework.collection.Member;


public class MemberHashSet {
    private HashSet<Member> hashSet;
    public MemberHashSet() { this.hashSet = new HashSet<>(); }

    public void addMember(Member member) {
        hashSet.add(member);
    }

    public boolean removeMember(int memberId) {
        Iterator<Member> it = hashSet.iterator();

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
        for (Member e : hashSet) {
            System.out.println(e);
        }
    }



}
