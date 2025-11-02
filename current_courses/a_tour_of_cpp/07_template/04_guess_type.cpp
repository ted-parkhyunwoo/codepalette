#include <vector>
#include <iostream>
#include <type_traits>
#include <string>


template <typename T>
class Vector{
    private:
        T* elem;
        int sz;
    public:
        Vector(int sz) : sz{sz} {}
        Vector(std::initializer_list<T> list): sz(list.size()) {}        // 선언: 초기화 할때 요소의 타입을 추론.
        //! std::initializer_list<int> 는 size()와 begin(), end() 등이 구현되어있음

};

int main (){
    // Vector Class를 사용하는 함수. (cpp20 주의.)
    Vector f = {1,2,3};
    auto g = new Vector{1.2, 3.4};
    Vector h{1,3,4};
    Vector<int> i(3);       // ()는 초기자리스트를 사용하지 않음. 초기자 리스트가 없으니 타입추론도 불가능해서 직접 <int> 넣어야함.
    delete g;


    //! c++17 에서도 인수추론은 됨. 방식이 20과 약간 다른부분이 있는듯 함.
    std::vector a = {1,2,3};
    // std::vector b = {1,1.2,3};       // 이런방식은 둘다 지원안되는듯.
    std::vector c = {1.0, 1.2, 3.0};    // 가능!
    std::vector d {"hello"};            // const char* 
    using namespace std::string_literals;       // "문자열"s로 std::string임을 명시하려면 작성해야됨.
    std::vector e {"hello"s};           // std::string
    // std::cout << typeid(d[0]).name();        // 타입 점검용 코드.


    return 0;
}