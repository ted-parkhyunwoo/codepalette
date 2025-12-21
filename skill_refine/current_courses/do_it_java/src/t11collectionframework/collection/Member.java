package t11collectionframework.collection;

// 해당 Member DataClass를 이용해 콜렉션별 추가삭제 기능과 테스트가 작성되었다.

public class Member {
    static int idBuffer = 1000;
    private int memberId;
    private String memberName;

    public Member(String memberName) {
        this.memberName = memberName;
        this.memberId = idBuffer++;
    }

    // memberId를 강제로 추가(set 등 테스트를 위한)
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


    // hashSet 을 올바르게 사용하기 위해 memberId기반 hashCode, equals를 오버라이드
    // memberId 가 같으면 같은 객체로 인식.

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
}
