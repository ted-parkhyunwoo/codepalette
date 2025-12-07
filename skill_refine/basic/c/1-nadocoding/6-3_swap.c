#include <stdio.h>

void Swap(int first, int second);
void Swapaddr(int *first, int *second);

int main(void)

{
    // 함수로 swap 할때, 포인터를 쓰고 안쓰고의 차이.
    int a = 10;
    int b = 20;
    printf("본래값 a= %d, b: %d\n", a, b);
    Swap(a, b);     //값만 복사한다는 의미  (call by value)
    printf("swap 이후 = a: %d, b: %d\n", a, b);   //a, b 원상복구됨.
                                            //
    Swapaddr(&a, &b);
    printf("swapaddr 이후 = a: %d, b: %d\n", a, b);   //포인터를 이용하면 a, b스왑됨.
                                
    // 따라서, Swap 은 값만 복사, Swapaddr는 위치를 찍어 변경.

    return 0;
}


void Swap(int first, int second)
{
    int temp = first;
    first = second;
    second = temp;
    printf("Swap 함수 내 = a: %d, b: %d\n", first, second);
}

void Swapaddr(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
    printf("Swapaddr 함수 내 = a: %d, b: %d\n", *first, *second);
}

