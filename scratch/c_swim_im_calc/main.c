#include <stdio.h>
#include "data.h"
#include "core.h"
#include "service.h"

// 사용자 기록 목표의 전역변수. 매개변수로 받기 때문에 필요에따라 사용가능
const double GOAL = 90;

int main(int argc, char* argv[]) {

    if (argc > 1)       wrapper(argc, argv, GOAL);
    else                userInsertMode(GOAL);

    return 0;
}

