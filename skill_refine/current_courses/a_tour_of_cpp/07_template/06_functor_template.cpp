#include <iostream>
#include <vector>

// 함수객체 : functor의 템플릿 사용.
template <typename T>
class LessThan {
private: 
    const T val;
public:
    LessThan(const T& val) : val{val} {}
    bool operator() (const T& x) { return x < val; }
};

// C = 컨테이너, P = 검사용 프레디킷:펑터   : count_if의 간소화버전
//! P에 펑터. 즉, 따지고 보면 클래스를 넘길수 있다는 것이 재밌는점. (게다가 펑터는 객체를 초기화 할 필요가 없다.)
// 설명: pred를 true 통과 하는 c라는 컨테이너의 요소 갯수
template <typename C, typename P>
int count(const C& c, P pred) {
    int cnt = 0;
    for (const auto& e : c) {
        if (pred(e)) ++cnt;
    }
    return cnt;
}

// 프레디킷으로 쓸 검사 예제: 컨테이너에서 특정 값보다 작은 요소의 개수를 출력
template <typename C, typename T>
void f(const C& c, T val) {
    using std::cout;
    cout << "number of values less than " << val << ": " << count(c, LessThan{val}) << '\n';
}

int main() {

    //! "abc" 등은 const char* 로 해석되므로 잘못된 코드.
    std::cout << ("abc" < "ab") << std::endl;
    //! std::string의 비교연산은 사전순 오름차순에서 앞으로 올수록 작은 값, 뒤로 갈 수록 큰 값임.
    std::cout << (std::string("abc") < std::string("ab")) << std::endl;
    

    // 펑터(만!) 사용 예제
    LessThan lti {3};
    bool resA = lti(5);                         // false: 3 < 5
    std::cout << resA << std::endl;         

    LessThan lts {std::string("string")};
    bool resLts = lts(std::string("str"));      // true: "str" < "string"
    std::cout << resLts << std::endl;


    //! 프레디킷 검사 사용예제
    std::vector p1 = {5,4,3,2,1};
    f(p1, 3);       // 3보다 작은것은 2개다.
    f(p1, 6);       // 모두 6보다 작다

    return 0;
}