package t11collectionframework.collection;

// 해당 Member DataClass를 이용해 콜렉션별 추가삭제 기능과 테스트가 작성되었다.

public class Member implements Comparable<Member> {
    //! TreeSet을 위해 implements Comparable<Member> 추가(compareTo도 구현해야함)
    static int idBuffer = 1000;
    private int memberId;
    private String memberName;

    public Member(String memberName) {
        this.memberName = memberName;
        this.memberId = idBuffer++;
    }

    //! memberId를 강제로 추가(set 등 테스트를 위한)
    public Member(int memberId, String memberName) {
        this.memberId = memberId;
        this.memberName = memberName;
    }

    public int getMemberId() {
        return memberId;
    }

    public String getMemberName() {
        return memberName;
    }

    @Override
    public String toString() {
        return memberName + "님의 ID: " + memberId;
    }


    //! hashSet을 사용하기 위해 memberId기반 hashCode, equals를 오버라이드 (memberId와 hashCode 가 같으면 같은객체라 판단하도록 유도)
    // hashCode가 같은지 먼저 살피고 최종 기준은 equals를 검사하는 구조라 함
    @Override
    public int hashCode() {
        return memberId;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj instanceof Member bf) {
            return bf.getMemberId() == this.getMemberId();
        }
        return false;
    }

    //! TreeSet은 이진탐색 트리기반 정렬을 하여 요소중복여부 판단, 요소의 위치를 정렬할 기준의 함수를 만들어줘야함.
    @Override
    public int compareTo(Member member) {
        // 오름차순으로 정렬. * -1 하면 내림차순
        return (this.memberId - member.memberId);
    }
}
