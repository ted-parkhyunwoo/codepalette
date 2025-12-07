#include <stdlib.h>
#include <iostream>


//! 이게 무슨 구조로 test()실행시 자동으로 finally 가 호출되는지 이해할 수 없음. : 161p
template <class F>
struct Final_action
{
    explicit Final_action(F f) : act(f) {}
    ~Final_action() {act(); }
    F act;
};

template <class F>
[[nodiscard]] auto finally(F f) {
    return Final_action{f};
}

void test() {
    int* arr = (int*)malloc(sizeof(int) * 5);

    auto act = finally([&]{
        std::cout << "자동실행되는 함수: 범위 끝날 시." << std::endl;
        free(arr);
    });
}


int main() {
    test();
    return 0;
}