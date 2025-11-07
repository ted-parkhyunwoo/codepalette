#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

// 구조체 선언부
typedef struct lottoStruct {                        // lotto 구조체
    unsigned nums[45];                              // 45가지 번호 배열
    unsigned size;                                  // nums의 크기: 45로 초기화됨
    unsigned result[7];                             // 무작위 번호 추출을 담을 배열(bonus번호 첨부)
    unsigned resSize;                               // 무작위 번호배열 result의 크기: 완성시 7로 변경됨
} lotto;


// 함수 선언부: prototype
void init(lotto* l);                                // lottoStruct 구조체 초기화
unsigned getRand(unsigned start, unsigned end);     // 범위 내 무작위 숫자 리턴. start, end가 포함됨
unsigned pop(lotto* l, unsigned idx);               // lottoStruct의 nums[idx] 를 리턴하며, 해당요소를 삭제 후, size를 재조정
void genLotto(lotto* l);                            // lottoStruct의 result를 생성
void printLotto(lotto* l, bool printBonus);         // lottoStruct의 result를 출력
void sortResult(lotto* l);                          // lottoStruct의 result배열중 마지막배열(bonus number)를 제외하고 오름차순 버블정렬
void generate(unsigned gen, bool bonus);            // 모두 자동실행. gen: 생성할 갯수, bonus: 보너스번호 출력여부


// 메인함수
int main() {
    unsigned long stack_noise = (unsigned long)&stack_noise;
    srand(time(NULL) ^ getpid() ^ stack_noise);     // rand() 호출의 시드 설정(유닉스 시간 ^ 프로세스id ^ 스택 정크값)
    generate(1, true);                              // 예: 1개의 번호를 추첨
    generate(5, false);                             // 예: 5개의 조합을 보너스 번호 없이 생성
    return 0;
}


// 함수 구현부
void init(lotto* l) {
    l->size = 45;
    l->resSize = 0;
    for (unsigned i = 0; i < l->size; ++i) 
        l->nums[i] = i + 1;
}

unsigned getRand(unsigned start, unsigned end) {               
    return ((unsigned)rand() % end) + start;
}

unsigned pop(lotto* l, unsigned idx) {
    unsigned res = l->nums[idx];
    for (unsigned i = idx; i < l->size - 1; ++i) 
        l->nums[i] = l->nums[i + 1];
    l->size--;
    return res;
}

void genLotto(lotto* l) {
    while (l->resSize < 7) {
        unsigned r = getRand(0, l->size);
        l->result[l->resSize] = pop(l, r);
        l->resSize++;
    }
}

void printLotto(lotto* l, bool printBonus) {
    for (unsigned i = 0; i < 6; ++i) {
        printf("%d ", l->result[i]);
        if (l->result[i] < 10) printf(" ");     // 한자리 숫자 줄맞춤
    }
    if (printBonus)                             // 보너스숫자 출력 (추천번호 조회할지, 당첨번호 생성할지 등에 쓰임)
        printf(" b: %d\n", l->result[6]);
    else
        printf("\n");
}

void sortResult(lotto* l) {
    for (unsigned i = 0; i < 5; ++i) {
        for (unsigned j = 0; j < 5 - i; ++j) {
            if (l->result[j] > l->result[j + 1]) {
                unsigned tmp = l->result[j];
                l->result[j] = l->result[j + 1];
                l->result[j + 1] = tmp;
            }
        }
    }
}

void generate(unsigned gen, bool bonus) {
    lotto l;
    while (gen > 0) {
        init(&l);
        genLotto(&l);
        sortResult(&l);
        printLotto(&l, bonus);
        gen--;
    }
}
