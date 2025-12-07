#include <iostream>

// *을 쓸 땐 정의와 사용할때 두가지가 다름. 

int main() {
    int score = 10;
    int* score_ptr = &score;    //정의할때 쓰는 *는 포인터정의.

    // 사용할 때 쓰는 아스테리스크를 포인터에 쓰면 역참조(dereferencing)
    *score_ptr = 20;    
    
    // 참조자 & (reference) 7번 코드 참고.

    score_ptr = &score; // score의 주소값을 score_ptr의 실제 값에 넣음.
    


    return 0;
}