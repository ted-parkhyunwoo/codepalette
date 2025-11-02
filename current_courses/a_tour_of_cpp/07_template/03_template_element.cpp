#include <iostream>
//! c++20 에서 작동하며, Element를 쓰기 위해선 콘셉트에 관한 초기 세팅이 필요함.
#include <concepts>
#include <thread>

template <typename T>
concept Element = std::copyable<T>;     // 복사 가능한 원소들만.
// 특정 타입만 넣을수도 있음.
// concept Element = std::integral<T> || std::floating_point<T>;


template <Element T>
class Vector{
    private:
        T* elem;
        int sz;
    public:
        explicit Vector(int sz): sz{sz} {}
};

int main() {
    Vector<int> a(3);
    // Vector<std::thread> b;            // 복사불가능하므로 사용불가!

    return 0;
}


// C++17에서는 아래와 같은 방법으로 작성됨
#include <iostream>
#include <type_traits>
#include <thread>

// C++17에서는 콘셉트 대신 SFINAE와 type traits 사용: 구현이 조금 복잡해보인다.
// template <typename T>
// struct is_element : std::is_copy_constructible<T> {};  // 복사 가능 여부 검사

// template <typename T, typename = std::enable_if_t<is_element<T>::value>>
// class Vector {
//     private:
//         T* elem;
//         int sz;
//     public:
//         explicit Vector(int sz) : sz{sz} {
//             elem = new T[sz];
//         }

//         ~Vector() {
//             delete[] elem;
//         }
// };

// // 특정 타입만 허용하는 방법 (C++17에서)
// // template <typename T, typename = std::enable_if_t<std::is_integral<T>::value || std::is_floating_point<T>::value>>
// // class Vector {
// //     private:
// //         T* elem;
// //         int sz;
// //     public:
// //         explicit Vector(int sz) : sz{sz} {
// //             elem = new T[sz];
// //         }

// //         ~Vector() {
// //             delete[] elem;
// //         }
// //     };
// // }

// int main() {
//     Vector<int> a(3);
//     // Vector<std::thread> b(2); // std::thread는 복사 불가능하므로 사용 불가!
//     // Vector<std::string> c(4); // std::string은 허용되지 않음 (정수 또는 부동소수점만 가능)

//     return 0;
// }