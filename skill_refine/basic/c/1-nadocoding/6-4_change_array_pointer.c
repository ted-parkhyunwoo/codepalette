#include <stdio.h>

void changeArray(int * ptr);

int main(void)
{
    // 배열의 값 변경.
    int arr[3] = {10, 20, 30};
    changeArray(arr);


    printf("%d\n", *(arr+1));

    for (int i = 0; i < 3; i++)
    {
        printf("%d 번째 배열값 : %d\n", i, arr[i]);
    }

    //  arr의 크기를 3보다 크게 한다면, array 추가도 가능한 듯 하다.
    // 왜냐하면 나머지는 *(arr+2) 이후로는 다 0으로 채워지기 때문.
    return 0;
}

void changeArray(int * ptr)
{
    ptr[2] = 50;
}
