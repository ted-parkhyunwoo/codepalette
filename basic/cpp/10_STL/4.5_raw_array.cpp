#include <iostream>


// 전통적인 raw array

int main() {

    // 정적할당(stack, 컴파일시 크기 결정 필수)
    int s_size = 5;
    int myStackArray[s_size] = {0}; // init all 0

    for (int i = 0; i < s_size; i++) {
        myStackArray[i] = i + 1;
    }

    for (int i = 0; i < s_size; i++) {
        std::cout << myStackArray[i] << " ";
    }
    puts("");

    // 동적할당(heap, 런타임시 크기 결정 가능.)
    int a_size;
    std::cout << "size: ";
    std::cin >> a_size;

    int* myArray = new int[a_size]{0};  // init all 0

    for (int i = 0; i < a_size; i++) {
        myArray[i] = i+1;
    }

    for (int i = 0; i < a_size; i++) {
        std::cout << myArray[i] << " ";
    }
    puts("");


    delete[] myArray;

    return 0;
}