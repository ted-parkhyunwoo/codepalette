#include <iostream>
#include <string>

// 다중 매개변수 탬플릿.
template <typename T1, typename T2>
void func(T1 a, T2 b) {
    std::cout << a << " " << b << std::endl;
}

// 다 타입 탬플릿 기본 뼈대.
template<typename T>
T my_max(T a, T b) {
    return (a > b) ? a:b;
}


// 템플릿 특수화. (위 함수로 실행되게 하지 않도록 template<> 로 사용. 타입 명시가 되지 않기 때문에 비워둔다 함- 명시적 사용 위해. std::string 만 쓰기 위해 오버로딩 하는 느낌)
template<>
std::string my_max(std::string a, std::string b) {
    return (a.length() > b.length()) ? a : b;
}

int main() {

    func<char, int>('C', 3);

    // max 사용.
    std::cout << my_max<int>(3, 5) << std::endl;


    // 특수화 사용. (길이가 더 긴 스트링을 출력)
    std::string a = "abc";
    std::string b = "abcd";
    std::cout << my_max<std::string>(a, b) << std::endl;



    return 0;
}

