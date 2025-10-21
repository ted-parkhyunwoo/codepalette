#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int number;
    char title[100];
};

void showBook (struct Book *ps, int indexNum){
    int i;
    for (i = 0; i < indexNum; i++) {
        printf("Num %d : %s\n", (ps+i)->number, (ps+i)->title);
    }
}

int main(void) {

    // 메모리 할당. 구조체 사용시.
    struct Book *ps = malloc(sizeof(struct Book) * 2);
    if (ps == NULL) {
        printf("메모리할당 실패");
        return -1;
    }

    // 입력 섹션
    //! ps[0].number = 1; 등과 같음. (배열로 구조체 접근사용)
    //! ->는 포인터를 쓸때만 사용가능. (포인터로 구조체 접근시)
    ps->number = 1;
    strcpy(ps->title, "C Programming");
    (ps + 1)->number = 2;
    strcpy((ps + 1)->title, "Data Structure");

    // 출력 섹션
    // printf("%d %s\n", ps->number, ps->title);
    // printf("%d %s\n", (ps+1)->number, (ps+1)->title);
    // 출력 함수로 대체하여 구현
    showBook(ps, 2);

    //메모리 반환
    free(ps);

    return 0;
}