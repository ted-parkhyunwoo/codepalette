#include <iostream>


int main() {

    int score = 10;
    double score_precise = 100.7;

    int* score_ptr = nullptr;
    score_ptr = &score;
    // score_ptr = &score_precise; //컴파일 에러남.
    // 기술적으론 가능하나 C++컴파일러 선에서 커트.
    //! 포인터가 가리키는 타입은 일치해야만 함.



    return 0;
}