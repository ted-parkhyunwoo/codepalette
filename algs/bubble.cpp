#include <iostream>
#include <vector>
#include <stack>
#include <concepts>

// 확인: 전통적인 C스타일 배열(int, char), vector<int>
template <typename T>
void bsort(T& t) requires (std::same_as<T, std::vector<int>>) {
    size_t sz = t.size();
    for (size_t i = 0; i < sz - 1; ++i) 
        for (size_t j = 0; j < sz - 1 - i; ++j) 
            if (t[j] > t[j + 1])    std::swap(t[j], t[j + 1]);  // 오름차순
}

template <typename T, size_t size>
void bsort(T (&t)[size]) {
    for (size_t i = 0; i < size - 1; ++i)
        for (size_t j = 0; j < size - 1 - i; ++j)
            if (t[j] > t[j + 1])    std::swap(t[j], t[j + 1]);  //오름차순
}

template <typename T>
void print(T t) {
    int sz = t.size();
    for (int i = 0; i < sz; ++i)    std::cout << t[i] << ' ';
    std::cout << '\n';
}

template <typename T, size_t size>
void print(T (&t)[size]) {
    for (int i = 0; i < size; ++i)  std::cout << t[i] << ' ';
    std::cout << '\n';
}

int main() {

    int arr[] = {5, 3, 2, 1, 4};    // 자동 크기 추론
    print(arr);

    std::vector vec = {5,2,3,1,4};  // 자동 타입추론
    print(vec);

    bsort(vec);
    print(vec);

    bsort(arr);
    print(arr);

    return 0;
}