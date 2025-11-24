#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

// prototypes

// 삭제 검토중
// void print(const int* arr, const int size);             // 디버그 배열 출력용.
// int popNum(int* arr, int* size, const int num);         // 현재 사용 안되는듯. 점검.

// 저수준 코드: 일부 함수 동적할당. 고수준 래퍼 메서드에서 할당/해제 제어됨. 따라서 직접사용시 주의. 필요시 프로토타입에서 주석해제
/*
int* initNums();                                        // 동적할당 주의!!  1~45 까지의 번호를 임의 생성.
int popIdx(int* arr, int* size, const int idx);         // index 기반 요소삭제 and 삭제된 요소 리턴(파이썬, js 형식으로 구현해봄)
int getRandInt(const int start, const int last);        // start - last 까지의 번호 무작위 리턴
void sort(int* arr, const long size);                   // 배열 정렬용(당첨번호 및 사용자 자동게임 정렬용)
int* getNums();                                         // 동적할당 주의!! 6 ~ 7(bonus) 개의 무작위 게임 번호 배열 생성
void printGame(const int* arr, const int bonus);        // getNums()로 생성한 배열을 출력. bonus는 보너스번호 출력여부(당첨번호용)
int getRank(const int* res, const int* game);           // res(당첨번호), game(사용자번호) 로 등수 계산 TODO: 이진탐색 리펙토링 고려
*/

// 고수준 인터페이스 메서드
static void printFiveGames();           // 5게임 자동 출력 (자동 번호를 받아 실제 마킹하여 사용할 때 유용)
static void printWinner();              // 임의 추첨번호 출력 (당첨번호 임의 생성)
static void printFiveGamesSimulator(int games);         // 1회 시뮬레이터 출력 (5게임 자동)
static void doLottoSimulate(const long weeks, const unsigned games);   // weeks수 만큼 추첨, 매주 games게임 총 당첨횟수 출력


//! MAIN: 사용예제
int main() {
    srand(time(NULL) ^ getpid());
    
    printFiveGames();               // 5게임 임의 생성
    printWinner();                  // 당첨번호 임의 생성

    printFiveGamesSimulator(5);     // 5게임 임의 생성, 당첨번호 임의 생성 후 추첨내역 출력

    doLottoSimulate(520000, 5);     // 52만 주(week) 추첨, 매주 구매 5게임 시 총 당첨횟수 출력 (약 1만년)

    return 0;
}


// 함수 정의

int* initNums() {
    int* res =                   (int*)malloc(sizeof(int) * 45);
    if (res == NULL) {
        perror("메모리 할당 실패");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 45; ++i)    res[i] = i + 1;
    return res;
}

void print(const int* arr, const int size) {
    printf("{ ");
    if (size)                           printf("%d", arr[0]);
    for (int i = 1; i < size; ++i)      printf(", %d", arr[i]);
    printf(" } : %d\n", size);
}

int popIdx(int* arr, int* size, const int idx) {
    const int res = arr[idx];
    for (int i = idx; i < *size - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    *size -= 1;
    return res;
}

int popNum(int* arr, int* size, const int num) {
    int idx = -1;
    for (int i = 0; i < *size; ++i) {
        if (arr[i] == num) idx = i;
    }
    if (idx == -1) { printf("없음\n"); return -1; }
    else return popIdx(arr, size, idx);
}

int getRandInt(const int start, const int last) {
    const int size = last - start + 1;
    return (rand() % size) + start;
}

void sort(int* arr, const long size) {
    for (long i = 1; i < size; ++i) {
        const int buffer =        arr[i];
        long j = i;
        for (; j > 0 && arr[j - 1] > buffer; --j)
            arr[j] = arr[j - 1];
        if (j != i)         arr[j] = buffer;
    }
}

int* getNums() {
    int* res = (int*)malloc(sizeof(int) * 7);
    if (res == NULL) {
        perror("메모리 할당 실패");
        exit(EXIT_FAILURE);
    }
    int* bf = initNums();
    int size = 45;

    for (int i = 0; i < 7; ++i) {
        res[i] = popIdx(bf, &size, getRandInt(0, size - 1));
    }

    sort(res, 6);
    free(bf);
    return res;
}

void printGame(const int* arr, const int bonus) {
    for (int i = 0; i < 6; ++i)
        printf(" %2d ", arr[i]);

    if (bonus)  printf("\tb: %d", arr[6]);
    // printf("\n");
}

int getRank(const int* res, const int* game) {
    int count = 0;
    for (int i = 0; i < 6; ++i) {
        int r = res[i];
        for (int j = 0; j < 6; ++j) {
            if (r == game[j]) {
                count++;
                break;
            }
        }
    }

    if (count == 6) return 1;
    else if (count == 5) {
        const int b = res[6];
        for (int i = 0; i < 6; ++i) {
            if (b == game[i])  return 2;
        }
        return 3;
    }

    else if (count == 4) return 4;
    else if (count == 3) return 5;
    return 0;       //꽝
}


static void printFiveGames() {
    printf("5 games: \n");
    for (int i = 0; i < 5; ++i) {
        int* tmp =      getNums();
        printGame(tmp, 0);
        printf("\n");
        free(tmp);
    }
}

static void printWinner() {
    printf("Winner: \n");
    int* tmp = getNums();
    printGame(tmp, 1);
    printf("\n");
    free(tmp);
}

static void printFiveGamesSimulator(int games) {
    printf("5 games and winner: \n");
    int* winner = getNums();
    int win = 0;
    for (int i = 0; i < games; ++i) {
        int* game = getNums();
        const int rank = getRank(winner, game);
        printGame(game, 0);
        if (rank != 0)  {
            printf(": [%d등 당첨]", rank);
            win++;
        }
        printf("\n");
        free(game);
    }

    if (!win) printf("[%d게임 모두 낙첨]\n", games);
    printf("추첨번호: "); printGame(winner, 1); printf("\n");
    free(winner);
}

// 매개변수: weeks(총 추첨), games(매주 구매할 게임)
void doLottoSimulate(const long weeks, const unsigned games) {
    printf("\n계산중...\n");
    const int printing = weeks <= 5? 1 : 0;     // 게임 횟수가 과하게 많으면(5회초과) 추첨번호는 출력하지 않음
    long result[] = {0, 0, 0, 0, 0};            // 전체 당첨 결과를 담는 배열

    for (long i = 0; i < weeks; ++i) {
        // res = 당첨번호 tmp = 무작위 사용자 번호 rank =  res기준 tmp의 등수
        if (printing)       printf("\n");
        int* res =          getNums();
        if (printing) {
            printGame(res, 1);
            printf("\n");
        }

        for (unsigned j = 0; j < games; ++j) {
            int* tmp =      getNums();
            if (printing)   printGame(tmp, 0);
            int rank =      getRank(res, tmp);
            if (printing)   printf("\t등수: %d\n", rank);

            if (rank != 0)  result[rank - 1]++;
            free(tmp);
        }
        free(res);
    }

    printf("총 결산:\n\t");
    for (int i = 0; i < 5; ++i)
        printf("%d등: %ld회   ", i + 1, result[i]);
    printf("\n");
}