#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//객체지향 클래스의 근본이 구조체.
//서로 다른 자료형을 묶어서 처리하는 개념.

struct student {
    int number;
    char name[10];
    double grade;
};


int main(void) {
    struct student s;
    s.number = 20240104;
    strcpy(s.name, "kimsangchul");
    s.grade = 4.3;
    printf("stu_num : %d\nname : %s\ngrade : %lf\n", s.number, s.name, s.grade );

    

    return 0;
}