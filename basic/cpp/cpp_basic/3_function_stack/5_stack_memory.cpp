//! Stack memory
// 함수에 따른 콜스택 push, 함수가 사용종료되면 pop. 
#include <iostream>

// calc 함수에 진입하면 메모리는 calc호출 스택(callstack)에 push됨. (쉽게말해 복사같은 개념.)
// 먼저 호출되는 순으로 위에 쌓임 (주소값은 a,b,c의 주소값보다 낮은 숫자라는 뜻.)
// return과 동시에 calc호출 스택 부분은 덮어쓰기 가능상태로 바꿈(정확하게는 pop)  
//! 추가 첨언: 덮어쓰기 가능상태는 삭제로 오해할 수 있으나, 삭제로 봐도 무리 없음. 다만 메모리가 보장되지 않는 상태라 할 수 있음 -> 삭제로 간주.
int calc(int a, int b) {

    return a + b;
}

int main() {

    int a, b, c;    //처음엔'CC' 라는 더미로 채워진다는데,visual studio한정.
                    // 내환경에선 00으로 채움.--디버그환경에 따라 다를 수 있다는것.
    a = 10;
    b = 20;
    c = 30; //여기까지 메인함수 stack memory에 push됨. (쉽게말해 저장이나 복사됨)
    c = calc(a, b);

    return 0;       //마찬가지로 메인함수에 return을 만나면 모든 stack memory가 pop됨(쉽게 말해 지워짐.)
}

//! 함수간 데이터가 격리된다는 결론도 낼 수 있음. 따라서 함수별로 scope가 적용되니, 지역변수는 해당 함수의 스택메모리 안에서만 꺼내 쓸 수 있다는 뜻.