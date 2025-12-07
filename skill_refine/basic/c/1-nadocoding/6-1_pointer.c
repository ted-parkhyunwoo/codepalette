#include <stdio.h>

int main(void)
{
    int ted = 1;
    int hyeree = 2;
    printf("ted = %d, hyeree = %d\n", ted, hyeree); // ted와 hyeree의 값을 정상적으로 출력.

    int *pointer = &ted;
    printf("pointer = %d\n", pointer);      // 잘못된 사용 예: 포인터의 주소를 %d로 출력하려 함.
    printf("pointer = %d\n", *pointer);     // 올바른 사용 예: 포인터를 통해 ted의 값을 출력.

    // int *second_pointer = &pointer;       // 잘못된 선언: 포인터의 주소를 int* 변수에 저장하려 함.
    // printf("second_pointer = %d\n", *second_pointer); // 잘못된 접근.

    int **third_pointer = &pointer;        // 올바른 이중 포인터 선언.
    printf("third_pointer = %d\n", **third_pointer); // 올바른 사용 예: 이중 포인터를 통해 ted의 값을 출력.

    int *forth_pointer = pointer;          // 포인터 복사.
    printf("forth_pointer = %d\n", *forth_pointer); // 올바른 사용 예: 포인터를 통해 ted의 값을 출력.

    // 포인터로 ted 수정.
    *forth_pointer += 1; // ted의 값을 1 증가시킴.
    printf("edit forth_pointer = %d\n", *forth_pointer); // 수정된 ted의 값 출력.



    return 0;
}
