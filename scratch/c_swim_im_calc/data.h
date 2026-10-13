#ifndef DATA_H
#define DATA_H

typedef struct imResult{
    double butterfly;
    double back;
    double breast;
    double freestyle;
    double fix;
} imResult;

// 입력된 매개변수 (argv) 를 기반으로 imResult 구조체로 리턴
imResult argsToImResult(int argc, char* argv[]);
// imResult 구조체의 값을 0으로 초기화, 포인터로 사용하기 때문에 현재로썬 안쓰임.
void clearImResult(imResult* res);

#endif
