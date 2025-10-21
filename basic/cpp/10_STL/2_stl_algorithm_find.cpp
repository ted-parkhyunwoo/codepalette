#include <iostream>
#include <algorithm>
#include <vector>

// 다양한 알고리즘.
// https://en.cppreference.com/w/cpp/algorithm

// find (찾기), max (최대값), for_each, accummulate

// 함수를 인자(매개변수) 로 제공해야 하는 경우가 존재. - for_each를 참고.
// functor, function pointer, lambda expression(C++11) 등의 방법이 있음.


// 반복자를 인자로 필요로 함.
// 컨테이너 별 적용할 수 있는 알고리즘이 다름.


int main() {
    std::vector<std::string> myVec{"Hello", " ", "World"};

    // find(vec.begin(), vec.end(), 찾을 대상)
    // find 는 찾은게 있으면 그것의 iterator 가 반환되고, 없으면 end()를 가리킴
    auto it = find(myVec.begin(), myVec.end(), "Hello");
    std::string result = (it != myVec.end()) ? "found": "cannot found";
    std::cout << result;
    // 응용
    auto it2 = find(myVec.begin(), myVec.begin()+1, "Hello"); //1번 인덱스부터 Hello 문자열을 찾음.

    // find 알고리즘은 요소 비교 가능해야 하므로, 사용자정의 타입에선 operator== 을 오버로딩해야함.
    return 0;
}