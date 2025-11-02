//! C++ 오류 처리 방법들을 하나의 파일로 정리한 예제
// 방법: 1) 예외 던지기, 2) 오류 코드 반환, 3) 프로그램 종료 방식
// 각 방식에 대한 설명 및 사용 예 포함

#include <iostream>
#include <stdexcept>
#include <cstdlib>  // exit, abort
#include <cassert>  // assert

// ==================== 1. 예외 던지기 ====================
// throw 키워드로 예외 발생
// try-catch 블록으로 예외 처리 가능
// 예외 클래스: std::exception, std::runtime_error, std::out_of_range 등 사용
int getElement(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range!");
    }
    return arr[index];
}

// ==================== 2. 오류 코드 반환 ====================
// 예외 없이 오류 상태를 코드로 반환
// enum 또는 정수형 반환값 사용
enum ErrorCode {
    SUCCESS = 0,
    INDEX_OUT_OF_RANGE = 1
};

int getElementSafe(int arr[], int size, int index, int& outVal) {
    if (index < 0 || index >= size) {
        return INDEX_OUT_OF_RANGE;
    }
    outVal = arr[index];
    return SUCCESS;
}

// ==================== 3. 프로그램 종료 방식 ====================
// 오류 발생 시 강제로 프로그램 종료

void fatalErrorExit() {
    std::cerr << "치명적 오류 발생, 종료함\n";
    std::exit(1);  // 비정상 종료
}

void fatalErrorAbort() {
    std::cerr << "강제 종료(abort) 호출됨\n";
    std::abort();  // 즉시 비정상 종료
}

void willTerminate() {
    throw std::runtime_error("예외 처리하지 않음");  
    // 처리되지 않은 예외는 std::terminate() 호출
}

// ==================== 추가 기능 ====================

// noexcept: 예외를 던지지 않는 함수로 명시
// 예외 발생 시 terminate 호출
void safeFunction() noexcept {
    std::cout << "예외를 던지지 않는 함수\n";
}

// assert(): 런타임 조건 검사, 실패 시 종료
// 디버그 모드에서만 작동 (NDEBUG 매크로로 제어)
void divide(int a, int b) {
    assert(b != 0);  // 조건 실패 시 종료
    std::cout << "결과: " << a / b << std::endl;
}

// static_assert(): 컴파일 타임 조건 검사
static_assert(sizeof(int) == 4, "int는 4바이트여야 함");

// ==================== main 함수 ====================

int main() {
    int arr[] = {10, 20, 30};

    // 예외 던지기 사용 예
    try {
        std::cout << getElement(arr, 3, 5) << std::endl;
    } catch (const std::out_of_range& err) {
        std::cerr << "예외 발생: " << err.what() << std::endl;
    }

    // 오류 코드 반환 예
    int value = 0;
    int result = getElementSafe(arr, 3, 5, value);
    if (result == SUCCESS) {
        std::cout << "값: " << value << std::endl;
    } else {
        std::cerr << "오류: 인덱스 범위 초과\n";
    }

    // 프로그램 종료 예시 (주석처리 상태)
    // fatalErrorExit();
    // fatalErrorAbort();

    // 예외 처리하지 않으면 terminate 발생
    try {
        willTerminate();
    } catch (...) {
        std::cerr << "예외 처리됨 (terminate 방지)\n";
    }

    // noexcept 함수 호출
    safeFunction();

    // assert 테스트
    divide(10, 2);  // b가 0이 되면 assert 실패

    return 0;
}
