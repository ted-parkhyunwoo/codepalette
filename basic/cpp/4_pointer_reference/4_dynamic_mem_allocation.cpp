//heap 메모리 사용.
// 1. 얼마나 메모리가 필요한 지 미리 알 수 없는 경우
// 1-1.사용자 입력에 따라 크기가 바뀔 경우. 
// 1-2.파일을 선택하여 내용을 읽어오는 경우,
// 2. 큰 데이터를 저장해야 할 때. (stack 으로 커버 안될 때)
// 3. 객체의 생애 주기(언제할당,해제할지)를 직접 제어해야 할 때.

//! 직접 해제 안하면 메모리 누수 발생.


#include <iostream>

int main() {
    int* int_ptr = nullptr; // 동적 메모리에 접근하기 위해 포인터를 사용함.
    int_ptr = new int;  //new 는 C의 malloc.    heap으로 저장.
    //new 하면 메모리주소 반환. 동시에 heap 할당됨.
    //당연하지만 int_ptr의 값 자체는(주소값) stack에 있음.

    *int_ptr = 100;     //int_ptr 메모리 검사하면 메모리 주소가 heap 영역이라 못보던 형태로 되어있음(0x9b1d0)

    delete int_ptr;     //! 반드시 해제 할 것.c 의 free 와 같은 역할.
    int_ptr = nullptr;  // 해주면 좋다. (컴파일러별로 다를 수 있으므로)


    // 동적메모리 할당 - int array사용 예제
    int* arrayPtr = nullptr;
    int size = 0;
    std::cout << "Array size? : ";
    std::cin >> size;
    arrayPtr = new int[size];   

    // Input section
    for (int i = 0; i < size; i++) {
        std::cout << (i+1) << "/" << (size) <<" num : ";
        std::cin >> arrayPtr[i];
    }

    // print section
    std::cout << "result : "; 
    for (int i = 0; i < size; i++) {
        std::cout <<arrayPtr[i] << " ";
    }

    delete[] arrayPtr;     //어레이 동적메모리 해제할 때. delete와 다름 주의.
    arrayPtr = nullptr;

    return 0;
}

