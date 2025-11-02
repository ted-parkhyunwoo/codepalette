//! RAII기법은 다음 PersonInfo 클래스 예제와 같이 간단한 것에선 코드가 더 복잡해 보일 수 있으나, 네트워크, 파일등 복잡한 자원을 관리할때 효과적임.

#include <iostream>
#include <stdexcept> // 예외 처리를 위한 헤더

// PersonInfo 클래스: RAII 기법을 활용한 자원 관리
class PersonInfo {
private:
    int* age; // 동적 메모리로 관리할 자원

public:
    // 생성자: 초기화와 자원 할당
    explicit PersonInfo(int initialAge) {   //! explicit 키워드 사용: 단일 인자 생성자에 대해 암시적 변환 방지
        if (initialAge < 0) {
            throw std::invalid_argument("나이는 음수가 될 수 없습니다!"); // 예외 던짐
        }
        age = new int(initialAge); // 동적 메모리 할당
        std::cout << "자원 할당 완료\n";
    }

    // 소멸자: 자원 해제
    ~PersonInfo() {
        delete age; // 동적 메모리 해제
        std::cout << "자원 해제 완료\n";
    }

    // 나이 반환 메서드
    int getAge() const {
        return *age;
    }

    // 나이 설정 메서드
    void setAge(int newAge) {
        if (newAge < 0) {
            throw std::invalid_argument("나이는 음수가 될 수 없습니다!"); // 예외 던짐 (RAII 기법이기 때문에 throw를 사용하지 않아도 작동하며 자원 회수 됨)
        }
        *age = newAge;
    }
};

int main() {
    try {
        // 사용자 입력으로 초기 나이 설정 (초기 음수 입력시 강제종료.)
        int initialAge;
        std::cout << "초기 나이를 입력하세요: ";
        std::cin >> initialAge;

        PersonInfo person(initialAge); // PersonInfo 객체 생성
        std::cout << "현재 나이: " << person.getAge() << std::endl;

        // 반복적으로 나이 변경: 루프 테스트 이며, 양수와 0을 제외한 음수 입력시 예외발생.
        while (1) {
            try {
                int newAge;
                std::cout << "변경할 나이를 입력하세요 (음수를 입력하면 예외 발생): ";
                std::cin >> newAge;

                // 종료 기저조건 0 입력 시 종료
                if (newAge == 0) {
                    std::cout << "변경 루프 종료\n";
                    break;
                }

                person.setAge(newAge);
                std::cout << "변경된 나이: " << person.getAge() << std::endl;

            } catch (const std::invalid_argument& e) {
                std::cerr << "예외 발생: " << e.what() << std::endl;
                std::cout << "다시 시도하세요.\n";
            }
        }

    } catch (const std::exception& e) {     // 초기 나이 입력시 음수설정시 강제종료.
        std::cerr << "프로그램 초기화 중 예외 발생: " << e.what() << std::endl;
    }

    std::cout << "프로그램 종료\n";
    return 0;
}