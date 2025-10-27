#include <stdio.h>
#include <stdlib.h>

// prototype 선언
void swap(int* a, int* b);          // &a 와 &b의 값을 서로 교체
void print(int* arr, int sz);       // arr[sz]의 배열을 [ 1, 2, 3 ] 과 같이 print
void bubble(int* arr, int sz);      // bubble로 오름차순 정렬

int main() {
    // swap test
    printf("Test: swap(&a, &b);\n");
    int a = 3;
    int b = 5;
    printf("a: %d, b: %d\n", a, b);
    swap(&a, &b);
    printf("a: %d, b: %d\n", a, b);

    // print test
    printf("\nTest: print(printTest, 3);\n");
    int printTest[] = {1, 2, 3};
    int* printTest2 = malloc(3 * sizeof(int)); printTest2[0] = 1; printTest2[1] = 2; printTest2[2] = 3;
    print(printTest, 3);
    print(printTest2, 3);
    free(printTest2);

    // bubble sort.
    printf("\nBubble Sorting: \n");
    // 정적배열의 정렬.
    int userArrSz = 6;
    int userArr[] = {1, 4, 3, 6, 9, 2};
    bubble(userArr, userArrSz);
    print(userArr, userArrSz);

    int testArr[] = {261378, 1823, 3892, 2384, 12, 4895, 9, 8923843, 8928, 989, 9, 201, 3, 0, 238, 329};
    // 표준적인 size 추정: 컴파일 타임에 정해지는 정적 배열은 다음과 같이 정의 할 수 있다.
    int testArrSz = sizeof(testArr) / sizeof(int);
    bubble(testArr, testArrSz);
    print(testArr, testArrSz);


    // 동적할당 배열의 정렬
    int heapArrSz = 5;
    int* heapArr = (int*)calloc(heapArrSz, sizeof(int));
    heapArr[0] = 432; heapArr[1] = 28913; heapArr[2] = 48932; heapArr[3] = 289; heapArr[4] = 47938;
    bubble(heapArr, heapArrSz);
    print(heapArr, heapArrSz);
    free(heapArr);

    return 0;
}



// 함수구현
void swap(int* a, int* b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

void print(int* arr, int sz) {
    if (sz <= 0) return;
    printf("[ %d", arr[0]);
    for (size_t i = 1; i < sz; ++i) 
        printf(", %d", arr[i]);
    printf(" ]\n");
}

void bubble(int* arr, int sz) {
    // 조기리턴 트리거. 초기 탐색에 정렬이 일어나지 않는다면 바로 break.
    int changed = 0;
    for (size_t i = 0; i < sz - 1; ++i) {
        for (size_t j = 0; j < sz - 1 - i; ++j) {
            size_t l = j;
            size_t r = j + 1;
            if (arr[l] > arr[r]) {
                // 포인터 산술로 전달하거나, 직접 요소의 주소를 참조 하거나. 예제일 뿐 일관되게 작성할 것.
                swap(arr + l, &arr[r]);
                changed = 1;
            }
        }

        if (!changed)   break; 
    }
}