#include <stdio.h>
#include <stdlib.h>

// 매개변수로서의 배열 사용
void printArr(int arr[], int sz, int init) {
    for (int i = 0; i < sz; ++i) {
        if (init) arr[i] = i + 1;
        printf("arr[%d]: %d\n", i, arr[i]);
    }
    printf("end.\n");
}

// 반환 타입이 배열인경우
int* getArr() {
    //! 지역변수이므로 int배열은 소멸됨. 따라서 static 선언
    //다만 연속 사용시 스택메모리를 계속 차지함.
    static int arr[] = {1,2,3};
    return arr;
}

int main(int argc, char* argv[]) {

    int max = 3;
    int array[max];

    printArr(array, max, 1);

    // 경우에 따라서 범위를 넘어서도 정상작동 되는 것 처럼 보이는 경우도 있음. 일부환경은 오류표기됨.
    printf("%d\n", array[max]);

    int array2[] = {1,2,3,4,5};     // 선언과 동시에초기화시.
    printArr(array2, 5, 0);

    // 포인터로 접근시
    for (int i = 0; i < 5; ++i) 
        printf("*(array2 + %d) : %d\n", i, *(array2 + i));

    puts("end.");


    // 사이즈 추론불가로 다음과같이는 사용불가능해보임.
    // int array3[] = getArr();
    int* array3 = getArr();
    printArr(array3, 3, 0);
    
    return 0;
}