#include <stdio.h>

int main(void)

{
    //배열 (array)
    int subway_1 = 30; //지하철 1호차 30명이 타고있다
    int subway_2 = 40;
    int subway_3 = 50;

    printf("지하철 1호차에 %d명 탑승\n", subway_1);
    printf("지하철 2호차에 %d명 탑승\n", subway_2); 
    printf("지하철 3호차에 %d명 탑승\n", subway_3);

    // 여러 개의 변수를 함께 동시에 생성
    // array로 재구현
    int subway_array[3];
    subway_array[0] = 30;
    subway_array[1] = 40;
    subway_array[2] = 50;

    for (int i= 0; i < 3; i++)
    {
        printf("지하철 %d호차에 %d명 탑승.\n", i+1, subway_array[i]); 
    }


    // 값 설정 
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  //초기화.
    // int arr[10]; 만 하고 출력하면 더미데이터만 출력 됨.
    // int arr[10] = {1, 2}; // 이런식으로 선언하면 나머지 인덱스들은 0으로 출력됨.
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", arr[i]);
    }

    // 배열 크기는 항상 상수로 선언
    /* 
    int size = 10;
    int arr[size];
    처럼 사용 불가! */
    
    // int arr[] = {1, 2}; //[]를 비워두면 arr[2] 와 동일하게 작동한다 함.
    
    float arr_f[5] = {1.0f, 2.0f, 3.0f};
    // 마찬가지로, for문 출력시 1.0 2.0 3.0 0.0 0.0 0.0 출력됨 
    for (int i = 0; i < 5; i++)
    {
        printf("%.2f\n", arr_f[i]);
    }


    return 0;
}
