// 포인터의 상수형. 
// const int* ptr, int* const ptr, const int* const ptr
//! 포인터가 값 또는 주소를 변경하지 못하도록 하는 목적이 있을 때

#include <iostream>

int main() {
    int high_score = 100;
    int low_score = 60;


    // 상수int를 포인팅(변수)한다.      - 포인팅 주소만 변경 가능.  값 변경 금지
    const int* score_ptr = &high_score;
    // *score_ptr = 80;                //!error
    score_ptr = &low_score;         //ok
    //! const int(변수가 상수선언됨을) 를 포인팅. 주소값은 변경 가능하나, 내용은 상수처리됨.

    // 변수int를 포인팅하는 상수포인터다.   - 값만 변경 가능.   주소 변경 금지
    int* const score_ptr2 = &high_score;
    *score_ptr2 = 80;               //OK
    // score_ptr2 = &low_score;        //!Error
    //! 일반 int 변수를 const 포인터로 선언.  주소값이 상수선언. 내용만 변경가능

    // 상수 int를 포인팅하는 상수포인터다.  //! 리턴 고정용.(값, 포인팅 변경불가)
    const int* const score_ptr3 = &high_score;
    // *score_ptr3 = 80;               //!Error
    // score_ptr3 = &low_score;        //!Error    

    return 0;
}