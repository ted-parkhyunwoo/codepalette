#include <iostream>


void print_array(int number[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << number[i] << std::endl;
    }
}

int main() {

    int my_array[] = {0, 1, 2, 3, 4, 5};
    
    int* ptr = my_array;

    print_array(my_array, 5);

    //메모리 검사 해보면 ptr 포인터처럼 print_array은 메모리를 push하지 않고 주소 값을 저장하여 사용함.

    return 0;
}

//! 함수 call stack에는 my_array의 주소만 저장되기 때문에 포인터처럼 scope에 영향 받지 않고 값을 변경할 수 있음.


//! 따라서 함수가 어레이의 값을 변경하길 원치 않으면 const로 선언 할 것.-실수로 라도 협업시 중요사항. my_array의 데이터 보존 보장.
// void print_array(const int number[], int size)