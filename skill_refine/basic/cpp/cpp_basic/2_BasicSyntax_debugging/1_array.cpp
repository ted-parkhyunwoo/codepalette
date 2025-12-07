#include <iostream>

int main() {

    // C++엔 class 를 많이 써서 사용은 잘 안함. -그래도 알아야되는 기초.
    // 동일한 타입만 가능.  //길이 변경 불가. 연속된 메모리 저장.
    int array[6] = {100, 85, 21, 56, 70, 95 };

    // 배열의 크기를 상수로 넣고, 0~9까지 초기화(이니셜라이징) 하는 예제.
    // array의 크기는 상수로 선언되어야 하나, 내 환경에선 아래처럼 안해도 작동됨.
    const int test = 10;    //! 그래도 항상 상수 선언 할 것.(표준문법)
    int testarray[test] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << testarray[9];

    // 자동 사이즈 넣기 . 5짜리로 자동으로 넣어짐.
    int my_array[] = {1, 2, 3, 4, 5};
    
    //배열의 사용법. - index 기반.
    std::cout << "first num : " << array[0] << std::endl;   //출력예
    std::cin >> array[0];     //입력 예.
    array[0] = 40;            //변수처럼 선언 예.

    return 0;
}