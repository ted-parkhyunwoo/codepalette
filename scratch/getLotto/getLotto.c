#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct lottoStruct{
    int nums[45];
    int size;
    int result[7];
    int resSize;
} lotto;

lotto* init() {
    lotto* res = malloc(sizeof(lotto));
    res->size = 45;
    for (int i = 0; i < res->size; ++i) {
        res->nums[i] = i + 1;
        if (i <= 7)
            res->result[i] = 0;
    }
    res->resSize = 0;
    return res;
}

void printLotto(lotto* l, int printBonus) {
    for (int i = 0; i < 6; ++i) {
        printf("%d ", l->result[i]);
        if (l->result[i] < 10) printf(" ");     // 한자리 숫자 줄맞춤
    }
    if (printBonus)                             // 보너스숫자 출력 (추천번호 조회할지, 당첨번호 생성할지 등에 쓰임)
        printf(" b: %d\n", l->result[6]);
    else
        printf("\n");
}

int getRand(int start, int end) {               // start, end가 포함됨.
    return (rand() % end) + start;
}

int pop(lotto* l, int idx) {
    if (idx + 1 > l->size) return -1;
    int res = l->nums[idx];
    for (int i = idx; i < l->size - 1; ++i) 
        l->nums[i] = l->nums[i + 1];
    l->size--;
    return res;
}

void genLotto(lotto* l) {
    while (l->resSize < 7) {
        int r = getRand(0, l->size);
        l->result[l->resSize] = pop(l, r);
        l->resSize++;
    }
}

void sortResult(lotto* l) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5 - i; ++j) {
            if (l->result[j] > l->result[j + 1]) {
                int tmp = l->result[j];
                l->result[j] = l->result[j + 1];
                l->result[j + 1] = tmp;
            }
        }
    }
}

void wrapper(unsigned gen, int bonus) {            // 출력용 생성기 래퍼함수. gen은 갯수를 나타냄. bonus는 보너스번호 출력여부
    srand(time(NULL) * getpid());
    while (gen > 0) {
        lotto* test = init();
        genLotto(test);
        sortResult(test);
        printLotto(test, bonus);
        free(test);
        gen--;
    }
}

int main() {
    wrapper(5, 0);
    return 0;
}