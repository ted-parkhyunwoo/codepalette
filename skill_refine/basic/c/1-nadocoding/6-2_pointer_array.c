#include <stdio.h>

int main(void)

{
    // array와 pointer는 좀 비슷한 기능을 가짐.

    int arr[3] = {5, 10, 15};
    int *ptr = arr;

    for (int i = 0; i < 3; i++)
    {
        printf("배열 arr[%d]의 값 : %d\n", i, arr[i]);
        printf("배열 arr[%d]의 값(포인터) : %d\n", i, *(arr + i));
        printf("배열 ptr[%d]의 값 : %d\n", i, ptr[i]);
        printf("배열 ptr[%d]의 값(포인터) : %d\n", i, *(ptr + i));
    }
    

    // arr[i] == *(arr + i) 와 같은 표현. 
    // arr의 주소를 찍어보자.
    printf("arr 자체의 값 : %d\n", arr);
    printf("arr[0] 의 주소 : %d\n", &arr[0]);

    // 실제 값을 찍어보자. 
    printf("arr 자체 값이 가지는 실제 값  : %d\n", *arr); // *(arr +0)
    printf("arr[0] 의 주소값이 가지는 실제값 : %d\n", *&arr[0]); // arr[0]

    // *&는 없는것과 같음.
    // &는 주소, *은 값이므로 상쇄됨. 
    return 0;
}
