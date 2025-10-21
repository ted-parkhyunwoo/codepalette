#include <stdio.h>
#define SIZE 5

struct student {
    int number;
    char name[20];
    double grade;
};

int main(void) {

    struct student list[SIZE];
    int i;

    // 입력파트
    for (i = 0; i < SIZE; i++){
        printf("학번 입력 : ");
        scanf("%d", &list[i].number);
        printf("이름 입력 : ");
        //* 강사는 & 붙이라 하는데, 
        //!사실 포인터 문자열은 안붙이는게 맞음.
        scanf("%s", list[i].name);
        printf("학점 입력 : ");
        scanf("%lf", &list[i].grade);
    }

    // 출력파트
    for (i = 0; i < SIZE; i++) {
        printf("Student Num : %d\n", list[i].number);
        printf("Name : %s\n", list[i].name);
        printf("GPA : %lf\n", list[i].grade);
    }

    return 0;
}