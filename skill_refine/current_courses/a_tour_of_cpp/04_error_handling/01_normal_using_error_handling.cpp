#include <iostream>
#include <stdexcept>

int getPositiveNumber() {
    int num;
    std::cout << "양수를 입력하세요: ";
    std::cin >> num;

    if (num < 0) {
        throw std::invalid_argument("음수는 허용되지 않습니다!"); // 예외 던짐
    }

    // test:
    std::cout << "throw 거치지 않고 통과. 입력된 값: " << num << "\n";
    return num; // 올바른 값 반환
}

int main() {
    int number = 0;

    while (1) {
        try {
            number = getPositiveNumber();   // 함수 호출. 여기서 음수입력시 throw 발생되기 때문에 catch로 넘어감.
            break;                          // 기저조건: 올바른 값이 입력되면 루프 종료
        } catch (const std::invalid_argument& e) {
            std::cout << "예외 발생: " << e.what() << std::endl; // 예외 처리
            std::cout << "다시 입력해주세요." << std::endl;
        }
    }

    std::cout << "입력된 양수: " << number << std::endl;
    return 0;
}