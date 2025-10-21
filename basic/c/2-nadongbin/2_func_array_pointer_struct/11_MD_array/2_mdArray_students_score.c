#include <stdio.h>

int main(void){

    int score[5][2];    //학생수, 수학/영어
    int total[2] = {0, };   
    //! 선언과 동시에 모두 0으로 초기화
    // 다만, int total[2] = {0}; 도 같은의미.
    // int total[2] = {}; 문법엔 어긋나지만 이런방식도 많이 씀.
    // 추가로 int total[2] = {5, }; 이러면 total[0]만 5,나머진 0


    int i;

    //입력 루프
    for (i = 0; i < 5; i++){
        printf("%d번 학생의 수학, 영어점수 : ", i + 1);
        scanf("%d %d", &score[i][0], &score[i][1]);
        //! scanf에 %c 로 입력 받을 경우는 getchar();를 넣을것

    }

    // total 넣기 루프
    for (i = 0; i < 5; i++){
        total[0] += score[i][0];
        total[1] += score[i][1];
    }

    printf("수학점수 합 : %d \n" , total[0]);
    printf("영어점수 합 : %d \n" , total[1]);


    return 0;
}