#include <iostream>
#include <map>

template <typename Value>
using charMap = std::map<char, Value>;
charMap<int> a;         // std::map<char, int> 타입임.

using customMap = std::map<int, std::string>;       // 고정으로 사용하고 싶을 때가 있다면 이렇게.

int main() {

    a['C'] = 3;
    std::cout << a['C'] << std::endl;

    customMap b;
    b[3] = "test";
    std::cout << b[3] << '\n';
    return 0;
}