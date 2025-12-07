#include <iostream>
#include <string>
#include <cassert>

using namespace std;

//! 스트롭스트룹의 스키마. (except 함수)
enum class Error_action { ignore, throwing, terminating, logging };
constexpr Error_action default_Error_action = Error_action::throwing;
enum class Error_code { range_error, length_error };

string error_code_name[] {"range error", "length error"};

template<Error_action action = default_Error_action, class C>
constexpr void expect(C cond, Error_code x) {
    if constexpr (action == Error_action::logging)
        if (!cond()) std::cerr << "expect() failur: " << int(x) << ' ' << error_code_name[int(x)] << '\n';
    if constexpr (action == Error_action::throwing)
        if (!cond()) throw x;
    if constexpr (action == Error_action::terminating)
        if (!cond()) terminate();
}


// 기본적인 double 배열을 기반한 Vector 클래스
class Vector{
public:
    Vector(int s) : elem{new double[s]}, sz{s} {}       // 생성자
    int size() { return sz; }                           // sz 접근
    double& operator[](int i) {                 // except 함수로 예외처리를 추가한 [] 접근 오버로딩
        expect([i, this] { return 0 <= i && i < size(); }, Error_code::range_error);
        return elem[i];
    }
    
private:
    double* elem;
    int sz;
};


int main() {

    // Vector 클래스 사용예시. 현재 필요없는 예시 이므로 주석처리.
    // Vector a(3);
    // for (int i = 0; i < a.size(); i++) {
    //     a[i] = i+1;
    // }

    // for (int i = 0; i < a.size(); i++) {
    //     cout << a[i] << endl;
    // }



    // 에러처리 예시( assert() 스타일의 except()  함수 사용)
    // Vector b(-2);

    //! assert() 예시: !!!디버그모드!!!에서만 정상작동함.    (include <cassert>)
    // assert(b.size() == 0); // b.size()가 0이 아닐 경우 프로그램 종료

    //! static_assert() 예시: !!!컴파일 타임!!!에 확인하는 assert (C++11부터 지원)
    constexpr int b = 11;
    // static_assert(b < 10, "ERROR!!!");      // 편집할 때 밑줄 생김. 컴파일 에러 발생

    return 0;
}