package hello.hello_spring.repository;

import hello.hello_spring.domain.Member;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
// import org.assertj.core.api.Assertions;
import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;

// testcase의 클래스는 Test를 써주는것이 관례.
class MemoryMemberRepositoryTest {
    MemoryMemberRepository repository = new MemoryMemberRepository();

    // 중요: Test를 클래스 단위로 실행할 때 각 테스트는 순서보장이 안됨. 따라서, MemoryMemberRepository에 clear할 수 있는 멤버를 만들고 다음과 같이 작성하면 매 테스트마다 실행됨.
    @AfterEach
    public void afterEach() {
        repository.clearStore();
    }

    @Test
    public void save() {
        Member member = new Member();
        member.setName("spring");

        repository.save(member);
        Member result = repository.findById(member.getId()).get();      //get 으로 Optional을 꺼낼 수 있으나, 원래는 이러면 안됨(이유설명X). 테스트니까.
//        System.out.println("result = " + (result == member));       // 글자로 출력하는 방법도 있으나...

        //  (기대값, 실제결과)
        Assertions.assertEquals(member, result);                      // 테스트 결과에 초록불이 들어옴. 잘못되면 노란불.

        // JUnit 4에선 가능했으나, JUnit5에선 삭제되어 import static org.assertj.core.api.Assertions.assertThat;하고  assertThat으로 씀.
        //Assertions.assertThat(result).isEqualTo(member);
        // assertThat(result).isEqualTo(member);

        // 혹은 Assertions를 import org.assertj.core.api.Assertions;
        assertThat(result).isEqualTo(member);
    }

    @Test
    public void findByName() {
        Member member1 = new Member();
        member1.setName("spring1");
        repository.save(member1);

        Member member2 = new Member();
        member2.setName("spring2");
        repository.save(member2);

        Member result = repository.findByName("spring1").get();     // "spring2" 로 하면 에러.
        assertThat(member1.getName()).isEqualTo(result.getName());

    }

    @Test
    public void findAll() {
        Member member1 = new Member();
        member1.setName("spring1");
        repository.save(member1);

        Member member2 = new Member();
        member2.setName("spring2");
        repository.save(member2);

        Member Member3 = new Member();
        Member3.setName("spring3");
        repository.save(Member3);

        List<Member> result = repository.findAll();
        assertThat(result.size()).isEqualTo(3);         // 3명이 아닌 다른것으로 하면 에러.

    }

}
