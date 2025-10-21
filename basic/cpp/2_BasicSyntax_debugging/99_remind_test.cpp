#include <iostream>

//! 배열과 조건문, 반복문 기초 + 디버깅(gdb 등을 다시 공부해 볼 것. vscode 에선 gdb를 안쓰려면 .vscode를 참조하도록 cpp 디렉토리를 통째로 다시 열 것)
//! vscode 에서 gdb를 안쓰기 힘듬. -exec print &a 혹은 -exec x /64xb &a 등으로 gdb처럼 출력해야 할 일이 많으므로 gdb에 대한 학습이 필요한 부분(다음강의 포함)
// 굳이 gdb를 안쓴다면 MemoryView 확장을 활용.


int main() {

    // array 와 for반복문, if조건문 복합 로직 시험
    int myArraySize = 5;
    int myArray[myArraySize] = {};
    for (int i = 0; i < 5; i++) {
        // i 가 짝수면 그대로 넣고, 홀수면 음수로 바꿔서 넣어보기.
        if (i % 2 == 0) myArray[i] = i;
        else myArray[i] = i * -1;

        // 단순출력
        std::cout << myArray[i] << std::endl;
    }

    puts("");


    // while 반복문
    int a = 0;
    while (a != myArraySize) {
        std::cout << ++a << std::endl;
    }

    puts("");

    // do while문, switch문 복합 로직 시험.
    //! 참고로 switch 문은 int, char 등 만 사용 가능한 것으로 알고 있음. (enum 에 대해서도 설명되나, 이것이 어떤 자료형인지는 아직 잘 모름.)
    do {
        a--;
        switch(a) {
            case 0: {
                std::cout << "a is 0. quit." << std::endl;
                break;
            } 
            default: {
                std::cout << "a : " << a << std::endl;
                break;
                }
        }


    } while (a != 0);

    puts("");

    // 삼항연산 기초.
    a++;

    bool isRight = a != 0 ? true : false;
    std::cout << isRight << std::endl;
    
    a--;
    isRight = a != 0 ? true : false;
    std::cout << isRight << std::endl;

    return 0;
}