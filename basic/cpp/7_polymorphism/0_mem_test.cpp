#include <iostream>

// 가상함수를 메모리 찍다보니, 코드영역이 보이던 찰나 호기심이 생겨서 
// (gdb) disassemble makeDouble(int) 로 데이터영역에서 번역된 코드를 볼 수 있음을 테스트 함.

// 이로써 C언어는 C-> 어셈블리 -> 기계어로 된 실행파일 로 번역되는 과정이란걸 알 수 있음 

int makeDouble(int x) {
    int result = x * x;
    return result;
}

int main() {

    int a = makeDouble(3);
    std::cout << a << std::endl;

    return 0;
}
