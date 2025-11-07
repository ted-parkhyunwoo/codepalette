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
    srand(time(NULL) * getpid());
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

void printLotto(lotto* l) {
    for (int i = 0; i < 6; ++i) {
        printf("%d ", l->result[i]);
    }
    printf(" b: %d\n", l->result[6]);
}

int getRand(int start, int end) {
    
    int res = (rand() % end) + start;
    return res;
}

int pop(lotto* l, int idx) {
    if (idx + 1 > l->size) return -1;
    int res = l->nums[idx];

    for (int i = idx; i < l->size - 1; ++i) {
        l->nums[i] = l->nums[i + 1];
    }
    l->size --;

    return res;
}

void genLotto(lotto* l) {
    while (l->resSize < 7) {
        int r = getRand(0, l->size);
        l->result[l->resSize] = pop(l, r);
        l->resSize++;
    }
}


// 같은번호 나오면 다시뽑는상태. pop방식 고려
void oldGenLotto(lotto* l) {
    while (l->resSize < 7) {
        int r = getRand(0, 45);
        while(l->nums[r] == 0) {
            r = getRand(0, 45);
        }
        l->nums[r] = 0;
        l->result[l->resSize] = r + 1;
        l->resSize += 1;
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


void debugPrint(lotto* l) {
    printf("size: %d\narray: ", l->size);
    for (int i = 0; i < l->size; ++i) {
        printf("%d ", l->nums[i]);
    }
    printf("\n");
}

void wrapper() {
    lotto* test = init();
    genLotto(test);
    sortResult(test);
    printLotto(test);
    free(test);
}

void poptest() {
    lotto* test = init();
    debugPrint(test);
    pop(test, 1);
    debugPrint(test);
    free(test);
}


int main() {
    wrapper();
    return 0;
}