#include <vector>
#include <iostream>
#include <list>


//! 함수 템플릿은 멤버함수일 수 는 있으나, virtual 멤버일 수는 없음.(컴파일러가 모든 템플릿의 구체화를 모르므로.)
// v 에다가 s의 모든 요소들을 합하여 리턴하는 함수. : accumulate() 표준의 간소화구현.
template <typename Seq, typename Val>
Val sum(const Seq& s, Val v) {
    for (auto& e : s) {
        v += e;
    }
    return v;
}

// v는 어떠한 컨테이너든지 begin(), end() 를 사용할 수 있도록 구현되어있으면 작동.
// sum의 결과를 출력하는 함수. 보편적인 코드는 아님. 테스트용. 
template <typename Seq>
void test(Seq& v) {
    int res = sum(v, 0);
    std::cout << res << std::endl;
    double res2 = sum(v, 0.0);
    std::cout << res2 << std::endl;
}


int main() {

    std::vector a = {1,2,3,4,5};
    std::list b = {6,5,4,3,2};
    test(a);
    test(b);

    return 0;
}