#include <stdio.h>
#include <stdlib.h>

typedef struct Struct1{
    int val1;
    int val2;
} Struct1;

void nextLine() {
    printf("\n");
}

int main(int argc, char* argv[]) {
    
    /*
    calloc: 크기만큼 생성, 0으로 초기화
    malloc: 크기만큼 공간할당, 초기화x
    realloc: 크기 재설정
    free: 해제

    원하는 크기만큼 할당 가능.
    포인트 변수(*)로만 접근 가능.
    반드시 해제해야함
    */

    // 일부 C에선 (int*) 생략 가능.
    int* a = (int*)calloc(1, sizeof(int));
    int* b = (int*)malloc(sizeof(int));
    printf("a 초기화전: %d\n", *a);
    printf("b 초기화전: %d\n", *b);
    *a = 3;
    *b = 3;
    printf("a: %d\n", *a);
    printf("b: %d\n", *b);

    nextLine();
    
    // 크기 재할당(a를 배열로 변환)
    a = realloc(a, 5);      //windows gcc에선 현재 0으로 초기화됨
    for (int i = 0; i < 5; ++i)
        printf("%d ", *(a + i));
    nextLine();

    for (int i = 0; i < 5; i++) {
        *(a + i) = i;
        printf("%d ", *(a + i));
    }
    nextLine();

    // 구조체배열할당
    Struct1* c = (Struct1*)malloc(sizeof(Struct1) * 2);
    // +@. 여러 변수 접근 방법.
    (*c).val1 = 3;
    c[0].val2 = 5;
    (c + 1)->val1 = 4;
    (c + 1)->val2 = 6;
    printf("c[0].val1: %d, %d\n", c[0].val1, (*c).val2);
    printf("c[0].val2: %d, %d\n", (*c).val1, (*c).val2);
    printf("c[1].val1: %d, %d\n", (c + 1)->val1, (c + 1)->val2);
    printf("c[1].val1: %d, %d\n", (c + 1)->val1, (c + 1)->val2);


    // +@. 2차원배열을 사용한 할당과 해제
    int sz = 6;
    int** arrarr = (int**)malloc(sizeof(int*) * sz);

    for (int i = 0; i < sz; ++i) {
        arrarr[i] = (int*)malloc(sizeof(int) * sz);
        for(int j = 0; j < sz; j++) {
            (*(arrarr + i))[j] = (i * sz) + j;
            printf("%d ", arrarr[i][j]);
        }
        printf("\n");        
    }

    for (int i = 0; i < sz; ++i) {
        free(*(arrarr + i));
    }

    free(arrarr);


    free(a);
    free(b);
    free(c);
    return 0;
}