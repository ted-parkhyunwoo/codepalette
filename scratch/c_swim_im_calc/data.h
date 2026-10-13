#ifndef DATA_H
#define DATA_H

// im 기록을 double 형식으로 저장할 구조체 자료구조. (사실은 배열이 더 훨씬 효과적). 헤더파일에 작성됐으므로 컴파일시 제외해도 됨(main.c 에 #include "data.h" 됐다는 가정하에)

typedef struct imResult{
    double butterfly;
    double back;
    double breast;
    double freestyle;
    double fix;
} imResult;

#endif
