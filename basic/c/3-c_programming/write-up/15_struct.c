#include <stdio.h>
#include <stdlib.h>

struct Student1 {
    int kor;
    int mat;
    int eng;
    char* name;
    int age;
} stu;  // 하나의 구조체만 사용할 때 변수명 설정 가능.


// typedef 사용시 자료형처럼 사용 가능.
typedef struct Student2 {
    int kor;
    int mat;
    int eng;
    char* name;
    int age;
} Student;      //반드시 이름이 같을 필요는 없으나, 관례임.

void printStu(Student stu) {
    printf("%s.kor : %d\n", stu.name, stu.kor);
    printf("%s.mat : %d\n", stu.name, stu.mat);
    printf("%s.eng : %d\n", stu.name, stu.eng);
    printf("%s.name : %s\n", stu.name, stu.name);
    printf("%s.age : %d\n", stu.name, stu.age);
    puts("");
}

int main(int argc, char* argv[]) {
    stu.kor = 100;
    stu.mat = 80;
    stu.eng = 70;
    stu.name = "홍길동";
    stu.age = 30;

    printf("stu.kor : %d\n", stu.kor);
    printf("stu.mat : %d\n", stu.mat);
    printf("stu.eng : %d\n", stu.eng);
    printf("stu.name : %s\n", stu.name);
    printf("stu.age : %d\n", stu.age);

    Student s1;
    Student s2;
    s1.kor = 90;
    s1.mat = 80;
    s1.eng = 70;
    s1.name = "최길동";
    s1.age = 40;

    s2.kor = 70;
    s2.mat = 80;
    s2.eng = 90;
    s2.name = "박길동";
    s2.age = 80;

    printStu(s1);
    printStu(s2);
    

    // 구조체 배열
    struct Student2 stu_array[3];
    // Student 타입으로도 사용가능하나, typedef struct 가 아닌경우, struct Student 식으로 사용한다는 예를 보여줌.
    stu_array[0].kor = 10;
    stu_array[1].kor = 20;
    stu_array[2].kor = 30;

    for (int i = 0; i < 3; ++i) {
        printf("kor : %d\n", stu_array[i].kor);
    }

    return 0;
}