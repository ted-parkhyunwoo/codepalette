#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


int* initNums() {
    int* result =                   (int*)malloc(sizeof(int) * 45);
    for (int i = 0; i < 45; ++i)    result[i] = i + 1;
    return result;
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

int getRand(const int start, const int last) {
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
    int* bf = initNums();
    int size = 45;
    
    for (int i = 0; i < 7; ++i) {
        int e = popIdx(bf, &size, getRand(0, size - 1));
        res[i] = e;
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


void printFiveGames() {
    for (int i = 0; i < 5; ++i) {
        int* tmp =      getNums();    
        printGame(tmp, 0);
        printf("\n");
        free(tmp);
    }    
}

void printWinner() {
    int* tmp = getNums();
    printGame(tmp, 1);
    printf("\n");
    free(tmp);
}

int main() { 
    srand(time(NULL) ^ getpid());
    
    printFiveGames();       // 5게임 자동 출력
    printWinner();          // 추첨번호 출력


    // 1회당 1번의당첨번호, 5개의 자동게임을 대조하여 시뮬레이트. (1회당 1주라 생각하면 현실이랑 가장 가까움)
    int runSimulate = 1;        // 실행 트리거 (0 || 1)
    if (runSimulate) {
        const long allGame = 10000;               // 총 추첨
        const int yourGame = 5;                 // 한번에 구매할 게임 수


        int printing = allGame <= 5? 1 : 0;
        long result[] = {0, 0, 0, 0, 0};
    
        for (long i = 0; i < allGame; ++i) {
            if (printing)       printf("\n");
            int* res =          getNums();
            if (printing)       printGame(res, 1);
            if (printing)       printf("\n");
            
            for (int i = 0; i < yourGame; ++i) {
                int* tmp =      getNums();    
                if (printing)   printGame(tmp, 0);
                int rank =      getRank(res, tmp);
                if (printing)   printf("\t등수: %d\n", rank);

                if (rank != 6)  result[rank - 1]++;
                free(tmp);
            }
            
            free(res);
        }

        printf("총 결산:\n\t");
        for (int i = 0; i < 5; ++i) 
            printf("%d등: %ld회   ", i + 1, result[i]);
        printf("\n");
    }

    return 0;
}