package hello.hello_spring.service;

import hello.hello_spring.domain.Member;
import hello.hello_spring.repository.MemberRepository;
import hello.hello_spring.repository.MemoryMemberRepository;

import java.util.List;
import java.util.Optional;


// 서비스의 메서드명은 비지니스에 의존적인 설계를 함. (모델 요구에 맞춘 추상화. 기계적인 설계는 MemberRepository.)
public class MemberService {
    private final MemberRepository memberRepository;


    // 테스트케이스에 사용할 경우 회원 리포지토리(메모리 리포지토리) 통일을 위해 오버로딩.
    // 만약 멤버리포지토리 인터페이스의 구현이 정해지고 완료되면 수정해야함(어차피 시나리오)
    public MemberService() {
        memberRepository = new MemoryMemberRepository();
    }
    public MemberService(MemberRepository memberRepository) {
        this.memberRepository = memberRepository;
    }

    /**
     * 회원 가입
     */
    public Long oldJoin(Member member) {
        // 비지니스 로직에 만약 같은이름 회원 허용 안된다 하면. (result 는 일단 저장전에 검색하고 존재하면 throw)
        Optional<Member> result = memberRepository.findByName(member.getName());
        // 옵셔널에선 직접 꺼내려면(권장X)
        // Member test = result.get(); 혹은 "orElseGet()" 많이씀: 값이 있으면 꺼내고 없으면 디폴트로 실행할 것을 지정할 수 있다함.
        //하지만 아래와 같이 쓰는것을 권장. (ifPresent는 값이 있는지)
        result.ifPresent(m -> {
            throw new IllegalStateException("이미 존재하는 회원입니다.");
        });

        memberRepository.save(member);
        return member.getId();
    }

    // 위처럼 Optional 선언이 보기 싫을 때 아래처럼 코드를 짤 수 있음.
    public Long join(Member member) {
        // 아래 블록을 선택하여 우클릭- 리펙토링-메서드 추출 (단축키 ctrl alt m)로 메서드 분리 가능. (아래는 분리됨)
        validateDuplicateMember(member);

        memberRepository.save(member);
        return member.getId();
    }

    private void validateDuplicateMember(Member member) {
        memberRepository.findByName(member.getName())
                .ifPresent(m -> {
                    throw new IllegalStateException("이미 존재하는 회원입니다");
                });
    }

    /**
     * 전체 회원 조회
     */
    public List<Member> findMember() {
        return memberRepository.findAll();
    }

    /**
     * 특정회원 ID로 조회
     */
    public Optional<Member> findOne(Long memberId) {
        return memberRepository.findById(memberId);
    }


}
