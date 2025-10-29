#include <stdio.h>
// desc: libmylib.so 를 C 에서 사용하려면:

// mylib.h 로 정의 해서 include 해도 됨.
int arraySum(int* arr, size_t size);
void printWelcome(char* name);

// 컴파일: gcc main.c -o main -L. -lmylib
// LD_LIBRARY_PATH=. ./main
//! LD_LIBRARY_PATH 를 쓰기 싫다면 /usr/lib 이나 /usr/local/lib 등에 넣어야함.


// 실험해볼것.
// stdio.h 처럼 전역에서 쓰고싶으면 상단 정의를 h로 분리해 /usr/include 혹은 /usr/local/include 등에 넣고
// so 파일은 마찬가지로 /usr/lib 혹은 /usr/local/lib 등에 넣음. 
// 이때, 소스파일(c) 는 필요없음. 이미 컴파일된 so를 씀. 


int main() {
    
    int arr[] = {1, 2, 3, 4, 5};
    size_t sz = 5;
    printf("%d\n", arraySum(arr, sz));

    printWelcome("Ted");
    
    return 0;
    
}
