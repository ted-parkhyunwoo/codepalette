package t11collectionframework.collection.arraylist;

import java.util.ArrayList;
import java.util.Iterator;

import t11collectionframework.collection.Member;

public class MemberArrayList {
    private ArrayList<Member> arrayList;
    public MemberArrayList() { this.arrayList = new ArrayList<>(); }


    public void addMember(Member member) {
        this.arrayList.add(member);
    }

    public boolean removeMember(int memberId) {

        // for문 사용을 통한 memberId 삭제
        /*
        for (int i = 0; i < this.arrayList.size(); ++i) {
            Member bf = this.arrayList.get(i);
            int bfId = bf.getMemberId();
            if (bfId == memberId) {
                arrayList.remove(i);
                return true;
            }
        }
        return false;
        */


        // iterator 를 사용한 memberId 삭제
        Iterator<Member> it = arrayList.iterator();
        while(it.hasNext()) {
            Member bf = it.next();
            int bfId = bf.getMemberId();
            if (bfId == memberId) {
                // 강의처럼 다음과 같이 사용하면 오버헤드 증가(굳이 다시 찾음)
                //// this.arrayList.remove(bf);
                // +@ 이터레이터로 삭제 가능
                it.remove();
                System.out.printf("%d 삭제 성공\n", memberId);

                return true;
            }
        }

        System.out.printf("%d 를 찾지 못했습니다\n", memberId);
        return false;
    }

    public void showAllMember() {
        Iterator<Member> it = this.arrayList.iterator();
        while (it.hasNext()) {
            System.out.println(it.next());
        }
    }



}
