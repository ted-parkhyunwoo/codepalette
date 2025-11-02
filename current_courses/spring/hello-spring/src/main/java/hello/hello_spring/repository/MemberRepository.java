package hello.hello_spring.repository;

import hello.hello_spring.domain.Member;
import java.util.List;
import java.util.Optional;

// DB가 선정되기 전이라 MemberRepository는 인터페이스로 선정. 구현체(메모리멤버리포지토리)로 임시사용
public interface MemberRepository {
    Member save(Member member);
    Optional<Member> findById(Long id);
    Optional<Member> findByName(String name);
    List<Member> findAll();
}
