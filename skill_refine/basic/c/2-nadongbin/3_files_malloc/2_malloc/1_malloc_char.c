#include <stdio.h>
#include <stdlib.h>

int main(void) {

    // 메모리 할당
    char *pc;
    pc = malloc(sizeof(char)*100);
    if (pc == NULL) {
        printf("메모리 할당 실패. \n");
        return -1;
    }

    // 입출력 섹션
    int i;
    for (i = 0; i < 26; i++){
        pc[i] = 'a' + i;
        if (i == 25){
            pc[i+1] = '\0';     //사실, if문은 필요 없이 for문 바깥에 써도 i는 for문을 거쳤기때문에 사용 가능.
        }
    }

    printf("%s \n", pc);

    // 메모리 반환
    free(pc);
    return 0;
}