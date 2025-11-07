package hello.hello_spring.service;

import hello.hello_spring.domain.Member;
import hello.hello_spring.repository.MemoryMemberRepository;
import org.junit.jupiter.api.*;

import static org.assertj.core.api.AssertionsForClassTypes.assertThat;
// import static org.assertj.core.api.Fail.fail;


class MemberServiceTest {

    // MemberService memberService = new MemberService();
    // MemoryMemberRepository memberRepository = new MemoryMemberRepository(); // 위와 다른 객체지만 static store라 작동은 하는상태

    // 따라서 MemberService의 멤버변수 memberRepository를 직접 생성하는 것이 아니라, 생성자 오버로딩 후 beforeEach
    MemberService memberService;
    MemoryMemberRepository memberRepository;

    // 이 과정을 의존성주입 (DI : dependency injection) 이라 함: 가짜저장소(목:mock 또는 stub) 테스트 케이스 주입을 위해.
    @BeforeEach
    public void beforeEach() {
        memberRepository = new MemoryMemberRepository();
        memberService = new MemberService(memberRepository);
    }


    @AfterEach
    public void afterEach() {
        memberRepository.clearStore();
    }


    // 테스트클래스 메서드 이름은 회원가입() 등 직관적으로 한글로 많이 작성하기도 함.
    @Test
    void join() {
        // given - when - then 문법을 보통 따름. 이와같은 주석패턴을 권장.

        //given
        Member member = new Member();
        member.setName("hello");

        //when
        Long saveId = memberService.join(member);

        //then
        // 내 생각엔 별로 좋지 않은 방식임. 비교식 자체가 둘다 서비스클래스에 있는 메서드들이라서.
        Member findMember = memberService.findOne(saveId).get();
        assertThat(member.getName()).isEqualTo(findMember.getName());
    }

    @Test
    public void duplicateMember() {
        //given
        Member member1 = new Member();
        member1.setName("spring");
        Member member2 = new Member();
        member2.setName("spring");

        //when
        memberService.join(member1);
/*
        try {
            memberService.join(member2);
            fail("예외가 발생해야 함.");
        } catch (IllegalStateException e) {
            assertThat(e.getClass()).isEqualTo(Exception.class); // Exception.class 대신 IllegalStateException.class 를 넣으면 통과되나, 실패해야 하는 메서드 이므로 일부러 다른것을 넣음.
        }
*/

        // try- catch문보다 더 권장되는 방식
        Assertions.assertThrows(IllegalStateException.class, () -> memberService.join(member2));
        //then

    }


    @Test
    void findMember() {
    }

    @Test
    void findOne() {
    }
}