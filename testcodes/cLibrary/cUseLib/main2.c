#include <mylib.h>


// libmylib.so 를 /usr/local/lib에 넣고
// mylib.h 를 /usr/include 에 넣은 이후에 행동을 서술.

// sudo ldconfig 실행해야함.
// 컴파일도 명시해줘야함. gcc main2.c -o main2 -lmylib
// lmylib 은 libmylib.so를 찾음
int main() {
    
    printWelcome("Ted");

    return 0;
}
