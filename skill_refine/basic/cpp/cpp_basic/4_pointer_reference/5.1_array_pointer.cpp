#include <iostream>

int main() {
    int scores[] = {100, 95, 90};
    int* scores_ptr = scores;


    // 주소값 표현임.
    std::cout << scores_ptr << std::endl;
    std::cout << (scores_ptr+1) << std::endl;
    std::cout << (scores_ptr+2) << std::endl;    
    // + 1은 두번째주소값 (int의 바이트크기를 한칸 더함.)
    //! 이것이 포인터변수를 선언할 때 자료형을 입력하는 이유. (int* 등.)
    // 쉽게말해 얼만큼을(int:8bytes) 건너뛴게 다음 주소값인지(+1) 알기 위해.


    // 값표현 두가지.(어레이,포인터 둘다 같음.)
    std::cout << *scores_ptr << std::endl;
    std::cout << *(scores_ptr+1) << std::endl;
    std::cout << *(scores_ptr+2) << std::endl;   
    std::cout << scores_ptr[0] << std::endl;
    std::cout << scores_ptr[1] << std::endl;
    std::cout << scores_ptr[2] << std::endl;   

    return 0;
}