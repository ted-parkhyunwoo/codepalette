#include <vector>
#include <iostream>
#include <sstream>

template <typename C, typename P>
int count(const C& c, P pred) {
    int cnt = 0;
    for (const auto& e : c) {
        if (pred(e)) ++cnt;
    }
    return cnt;
}

// 06_functor_template.cpp 의 코드 
//! pred에 램다 연결: lambda 식 함수객체 생성.
template <typename C, typename T>
void f(const C& c, T val) {
    using std::cout;
    cout << "number of values less than " << val << ": " << count(c, [&](int n){ return val > n; }) << '\n';
}

//! []는 캡쳐리스트. 비워둘 수 있음: 아무것도 캡쳐하지 않음.
// [&] 현재 스코프 내 모든 지역명(변수명)을 참조접근
// [=] &와 동일하나, 모든 참조가 const처럼 다루어져서 값 수정할 수 없음.
// [&x] x라는 변수만 참조접근
// [x] x라는 변수 복사캡쳐.
// [this] 클래스 내 멤버로 참조.
// [*this] 클래스 내 멤버를 복사캡쳐
// [i, this] 처럼 캡쳐할 객체들 열거하여 넣을 수 있음


// for-each의 간소화 구현.
template <typename C, typename Oper>
void for_each(C& c, Oper op) {
    for (auto& e : c) {
        op(e);
    }
}

// for-each 테스트용 컨테이너 출력함수
template <typename C>
void printV(const C& c) {
    std::ostringstream oss;
    oss << "{ " << c[0];
    for (int i = 1; i < c.size(); i++) {
        oss << ", " << c[i];
    }
    oss << " }\n";
    std::cout << oss.str();
}

int main() {
    std::vector a = {1,2,3,4,5};
    f(a, 3); // 3보다 작은건 2개다. 


    // for_each함수의 램다 참조전달. (책의 내용과는 다른 간소화된 예제임.)
    printV(a);
    int mul = 3;
    for_each(a, [&mul](int& n) { n *= mul;} );
    printV(a);
    int sum = 1;
    for_each(a, [&sum](auto& n) { n += sum;} ); // n 타입을 제네릭으로 사용 가능: 제네릭 람다.
    printV(a);

    // 교재에 처음보는 while 문법이 있어서 테스트 (책의 내용과 조금 다름. ) ctrl+c 등으로 종료
    std::vector<int> test;
    int num;
    while (std::cin >> num) {
        test.push_back(num);
    }

    printV(test);

    return 0;
}