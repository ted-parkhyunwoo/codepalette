#include <iostream>


int* dont_do_this()
{
    // int num = 10;
    int* num_ptr = new int;
    *num_ptr = 10;
    return num_ptr;
    //지역변수로 설정된 포인터는 리턴이 안됨. 따라서 동적메모리 포인터로 리턴.
}

int main() {

    int* ptr = nullptr;
    ptr = dont_do_this();
    std::cout << *ptr << std::endl;

    delete ptr;
    ptr = nullptr;

    return 0;
}


//! 추가첨언. 함수로 리턴받는 포인터 사용 시 동적할당을 이용하여야 하며, 안그러면 값 보장을 받지 못함(사용은 됨). 해제시에는 위와같이 delete ptr; 로 처리한다. (선언은 int* ptr = dont_do_this;)