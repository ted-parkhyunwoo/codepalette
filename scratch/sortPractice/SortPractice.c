#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// Prototypes:

// helper methods
inline void swap(int* a, int* b);
void printArr(int* arr, unsigned size);

// sort
void bubble(int* arr, unsigned size);
void select(int* arr, unsigned size);
void insert(int* arr, unsigned size);
void shell(int* arr, unsigned size);
void knuth_shell(int* arr, unsigned size);
void merge(int* arr, unsigned size);                                    // 개념만 보고 직접 만든거라 스탠다드 코드와 약간 다름.

void _quick(int* arr, int left, int right);                             // quick core
void quick(int* arr, unsigned size) { _quick(arr, 0, size - 1); }       // 테스트의 양식(매개변수 스타일)에 맞게 사용하기 위한 wrapper함수

void _quickNoReg(int* arr, int left, int right);                        // quick 과 동일한구조. 변수가 일반 변수로 register로 선언되지 않음.
void quickNoReg(int* arr, unsigned size) { _quickNoReg(arr, 0, size - 1); }

void _quickPtr(int* start, int* end);                                   // quickPtr core: 포인터 버전
void quickPtr(int* arr, unsigned size) { _quickPtr(arr, arr + size - 1); }


// for sort time bench marking 
int* getRandArr(long size, int maxInt);
void doTest(void (*func)(int*, unsigned), unsigned loop, int* sampleArr, long size);
void runTests(int init_srand, unsigned loop, void (*funcs[])(int*, unsigned), unsigned funcsSize, long size, int maxInt);


// 메인함수
int main() {

    // 다음 test 배열의 boolean 값에 따라 검사를 진행하고 return 0.
    bool test[] = {
        false, false, true, false     // 기본테스트(출력), 무작위배열테스트(출력), 두 정렬로 정렬검증, 벤치마크테스트
    };

    srand(__builtin_ia32_rdtsc());          // 매 실행마다 다름을 보장하기 위한것이지, 보안적인 랜덤시드는 아님

    // 1. 기본테스트: arr를 정렬하여 출력
    if (test[0]) 
    {
        void (*func)(int*, unsigned) = quick;           // 정렬 선택. 변경가능
        int arr[] = { 2, 3, 7, 1, 9, 6, 0, 5, 4, 8 };   // 정렬 배열. 변경가능

        int arrSz = sizeof(arr) / sizeof(arr[0]);
        func(arr, arrSz);
        printArr(arr, arrSz);
    }


    // 2. 무작위배열 테스트: 무작위 배열을 생성하고 정렬하여 출력
    if (test[1]) 
    {
        void (*func)(int*, unsigned) = quickPtr;        // 정렬 방법. 변경 가능
        int randomLoop = 3;                             // 샘플 갯수. 변경 가능
        int sampleSize = 20;                            // 샘플 길이. 변경 가능
        int max = 100;                                  // 샘플 요소 최대값. 변경 가능

        int* sample = NULL;
        for (int i = 0; i < randomLoop; ++i) {
            sample = getRandArr(sampleSize, max);
            func(sample, sampleSize);
            printArr(sample, sampleSize);
            free(sample);
        }
    }


    // 3. f1정렬, f2정럴 결과가 같음을 검증
    if (test[2]) 
    {
        void (*f1)(int*, unsigned) = quick;             // 첫번째 정렬 방법. 변경 가능
        void (*f2)(int*, unsigned) = quickPtr;          // 두번째 정렬 방법. 변경 가능
        int testLoop = 5;                               // 검증횟수. 변경 가능
        int sz = 100000000;                             // 샘플 길이. 변경 가능
        int max = 10000;                                // 샘플 요소 최대값. 변경 가능

        while(testLoop > 0) {
            int* checkSample = getRandArr(sz, max);
            int* copySample = malloc(sz * sizeof(int));     memcpy(copySample, checkSample, sz * sizeof(int));
            clock_t f1_start = clock();
            f1(checkSample, sz);
            double f1_res = (double)(clock() - f1_start) / CLOCKS_PER_SEC;
            clock_t f2_start = clock();
            f2(copySample, sz);
            double f2_res = (double)(clock() - f2_start) / CLOCKS_PER_SEC;
            for (int i = 0; i < sz; ++i) {
                if (checkSample[i] != copySample[i]) {
                    printf("검증실패: %d != %d\n", checkSample[i], copySample[i]);
                    break;
                }
            }
            printf("검증성공. 정렬소요시간: f1: %f s\t f2: %f s\n", f1_res, f2_res);
            free(checkSample);
            free(copySample);
            testLoop--;
        }
    }


    // 4. 성능 테스트
    if (test[3]) {
        // 기본정렬 테스트
        printf("\nNormal Sort Test:\n");
        void (*funcs[])(int*, unsigned) = { 
            bubble, select, insert, shell, knuth_shell, merge, quick, quickPtr      // 정렬방법. 추가/삭제 가능
        };

        int initSrand = 0;          // rand시드 초기화여부. 수정가능 (0 || 1)
        unsigned loop = 1;          // 평균 구할 루프 횟수. 수정가능
        long size = 100000;         // 랜덤생성할 배열의 크기
        int maxInt = 10000;         // 랜덤 추출 번호범위. 높여도 속도에 별 의미 없음
        runTests(initSrand, loop, funcs, sizeof(funcs) / sizeof(funcs[0]), size, maxInt); 


        // 고성능 테스트 : 천만개 요쇼 배열 검사
        printf("\nHigh Perfomance Sort Test:\n");
        void (*highPerfomFuncs[])(int*, unsigned) = { 
            shell, knuth_shell, merge, quick, quickPtr                              // 정렬방법. 추가/삭제 가능 (bubble, select, insert는 굉장히 느림)
        };

        unsigned highPerfomFuncsSize = sizeof(highPerfomFuncs) / sizeof(highPerfomFuncs[0]);
        runTests(0, 3, highPerfomFuncs, highPerfomFuncsSize, 10000000, maxInt);
    }
    return 0;
}







// 함수 구현부(정의)

void swap(int* a, int* b) { register int tmp = *a;      *a = *b;        *b = tmp; }
void printArr(int* arr, unsigned size) {
    printf("{%d", arr[0]);
    for (unsigned i = 1; i < size; ++i)
        printf(", %d", arr[i]);
    printf("}\n");
}

// 최소값 찾기. 큰 값을 찾아 배열 오른쪽으로 밀어냄 (거품이 교차되듯이)
void bubble(int* arr, unsigned size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}

// 0번 인덱스부터 최소값을 찾고(선택), 있다면 0번과 스왑. 바뀐건 다음 루프에서 처리
void select(int* arr, unsigned size) {
    for (int i = 0; i < size; ++i) {
        int minIdx = i;                 // 인덱스로 저장하며 업데이트 후 , 최소값의 인덱스를 찾아 i와 minIdx를 스왑
        for (int j = i; j < size; ++j) {
            if (arr[minIdx] > arr[j])       minIdx = j;
        }
        if (minIdx != i)        swap(arr + i, arr + minIdx);
    }
}

// i를 기준으로 i의 좌측 배열만 조정하며, 최소값/최대값 등을 저장후 삽입위치 정해질 때 까지 배열을 한칸씩 밀어냄.
void insert(int* arr, unsigned size) {
    for (int i = 1; i < size; ++i) {    // 코드가 배열을 i기준으로 나누어 좌측, 우측배열을 비교하는 방식이므로, 1부터 시작.
        int buffer = arr[i];            // 현재 요소 저장 (index로 사용하지 않는 이유는 j를 다루는 배열에서 이곳의 idx로 밀어낼 수 있음.)
        int j = i;
        // i 기준으로 좌우 배열 슬라이스. 이후 좌측배열의 마지막요소부터 0까지 점검후 밀어내기. 넣을곳이 있다면 삽입하고 루프종료
        for (; j > 0 && arr[j - 1] > buffer; --j)       arr[j] = arr[j - 1];
        if (j != i)         arr[j] = buffer;    // j(삽입할 위치)를 다루는 반복문이 j를 초기값i에서 더 작은 idx값으로 업데이트 했다면, 버퍼에 저장한 값으로 덮어씌움(삽입)
    }
}

// 쉘정렬은 insert의 확장개념. insert에서 int i = 1과 arr[j - 1]에 해당하는 부분이 gap(step)으로 관리되며 크기는 아무렇게나 줄여도 상관없으나, 마지막엔 항상 1을 실행해야 정확도를 보장함.
// gap(step) : size / 2로 갱신할 것을 제안했으나, knuth수열(3^k - 1) / 2 (혹은 3new = 3old + 1) 혹은 치우라 실험검증 수열이 가장 빠르다고 알려짐. size / 2갱신도 충분히 빠름

/* 압도적으로 빠른 이유 분석: 
1. 순수 삽입정렬은 매우 큰 이동이 필요한 경우(오름차순인데 마지막이 1처럼 극단적으로 작은 경우) 아주 잦은 이동이 필요함. 이것의 횟수를 증분활용을 통해 획기적으로 줄임.
2. 삽입정렬은 애초에 어느정도 정렬되어 있어야 빠른데(데이터 이동 최소화), 증분의 단계중 이전 단계가 현재의 단계를 거의 완성시켜놓음.
*/ 
void shell(int* arr, unsigned size) {
    int step = size / 2;
    while (step > 0) { 
        for (int i = step; i < size; ++i) {
            int buffer = arr[i];
            int j = i;
            for (; j >= step && arr[j - step] > buffer; j -= step)      arr[j] = arr[j - step];
            if (j != i) { arr[j] = buffer;}
        }
        step /= 2;
    }
}

// shell 정렬의 단순 비교 정수들 register 적용과 크누스수열 적용(연속된 값들이 서로의 약수가 되지 않도록 설계되어 최적화)
void knuth_shell(int* arr, unsigned size) {
    register int step = 1;      while(step < size / 3) { step = 3 * step + 1; }     // init step.
    register int i;
    register int j;
    register int buffer;

    while (step > 0) { 
        for (i = step; i < size; ++i) {
            buffer = arr[i];
            for (j = i; j >= step && arr[j - step] > buffer; j -= step)         arr[j] = arr[j - step];
            if (j != i) { arr[j] = buffer;}
        }
        step /= 3;                                      // update step
    }    
}

// quick정렬. pivot을 기준으로 큰 값배열과 작은 값배열을 분할하여 재귀실행
void _quick(int* arr, int left, int right) {
    // register선언된 변수들은 그냥 int로 사용시에도 충분히 quick정렬은 빠르지만, 이조차 압도적으로 빨라졌음.
    register int pL = left;                          // 0으로 시작
    register int pR = right;                         // size - 1로 시작
    register int pivot = arr[(pL + pR) / 2];         // 기준값은 센터값
    register int tmp;
    //??? pivot을 중앙값으로 설정하고싶을 때: 좌우 균형을 맞춘 안정성 상승한다지만 속도는 오히려 감소함
    // register int center = (pL + pR) / 2; register int pivot = arr[pL] < arr[pR] ? (arr[center] < arr[pR]? arr[center]: arr[pR]) : (arr[center] < arr[pL] ? arr[center]: arr[pL]);
    while (pL <= pR) {                      // pL, pR 이 교차될 때 까지 탐색
        while(pivot > arr[pL]) pL++;        // pL 은 arr[pL] 값이 pivot보다 크면 멈춤
        while(pivot < arr[pR]) pR--;        // pR 은 arr[pR] 값이 pivot보다 작으면 멈춤
        if (pL <= pR) {                     // 스왑하고 다음탐색. (다만 위 과정에서 pL과 pR이 바꼈으니 조건을 다시 점검)
            tmp = arr[pL];                  //??? 이상하게, swap 함수를 inline처리, tmp를 register로 다뤄도 약간밖에 안빨라짐. 내부구현이 훨씬 빠름
            arr[pL] = arr[pR];
            arr[pR] = tmp;
            pL++;
            pR--;
        }
    } 
    if (left < pR) _quick(arr, left, pR);       // pivot기준 좌측배열 정렬 재귀실행(pR이 pivot쪽으로 왔으므로, right는 pR)
    if (right > pL) _quick(arr, pL, right);     // pviot기준 우측배열 정렬 재귀실행(pL이 pivot쪽으로 왔으므로, left는 pL)
}

void _quickNoReg(int* arr, int left, int right) {
    int pL = left;
    int pR = right;
    int pivot = arr[(pL + pR) / 2];
    int tmp;
    while (pL <= pR) {
        while(pivot > arr[pL]) pL++;
        while(pivot < arr[pR]) pR--;
        if (pL <= pR) {
            tmp = arr[pL];
            arr[pL] = arr[pR];
            arr[pR] = tmp;
            pL++;
            pR--;
        }
    } 
    if (left < pR)  _quickNoReg(arr, left, pR);
    if (right > pL) _quickNoReg(arr, pL, right);
}

void _quickPtr(int* start, int* end) {
    register int* lPtr = start;
    register int* rPtr = end;
    register int pivot = *(start + ((end - start) / 2));
    register int tmp;
    while (lPtr <= rPtr) {
        while (pivot > *lPtr)  lPtr++;
        while (pivot < *rPtr)  rPtr--;
        if (lPtr <= rPtr) {
            tmp = *lPtr;
            *lPtr = *rPtr;
            *rPtr = tmp;
            lPtr++;
            rPtr--;
        }
    }
    if (rPtr > start)   _quickPtr(start, rPtr);
    if (lPtr < end)     _quickPtr(lPtr, end);
}


void merge(int* arr, unsigned size) {
    // 기저조건: 정렬할 것이 없을 때 아무 정렬도 하지 않고 종료
    if (size <= 1) return;
    // 분할
    register unsigned lSize = size / 2;
    register unsigned rSize = size - lSize;
    int* lArr = malloc (lSize * sizeof(int));
    int* rArr = malloc (rSize * sizeof(int));
    memcpy(lArr, arr, lSize * sizeof(int));
    memcpy(rArr, arr + lSize, rSize * sizeof(int));
    // 정복
    merge(lArr, lSize);
    merge(rArr, rSize);
    // 합병
    register unsigned lIdx = 0, rIdx = 0, aIdx =0;
    while (lIdx < lSize && rIdx < rSize && aIdx < size) {
        if (lArr[lIdx] < rArr[rIdx])    arr[aIdx++] = lArr[lIdx++];
        else arr[aIdx++] = rArr[rIdx++];
    }
    // 나머지 발생시 lArr부터 합병
    while (lIdx < lSize) arr[aIdx++] = lArr[lIdx++];
    while (rIdx < rSize) arr[aIdx++] = rArr[rIdx++];
    free(lArr);
    free(rArr);
}


int* getRandArr(long size, int maxInt) {
    int* res = malloc(sizeof(int) * size);      // getRandArr메서드 사용시에는 메모리 해제를 잊지 않도록.
    for (long i = 0; i < size; ++i)             res[i] = rand() % maxInt + 1;
    return res;
}

void doTest(void (*func)(int*, unsigned), unsigned loop, int* sampleArr, long size) {
    int* sample = malloc(sizeof(int) * size);   // 샘플 복사될 메모리 할당
    double spentTimes[loop];                    // 소요시간 기록 배열
    double totalSpent = 0;                      // 최종 누적 시간 기록

    for (int i = 0; i < loop; ++i) {
        memcpy(sample, sampleArr, size * sizeof(int));        // 샘플 초기화
        clock_t start = clock();
        func(sample, size);
        spentTimes[i] = (double)(clock() - start) / CLOCKS_PER_SEC;     // 시간 기록
    }
    // 시간 평균 산출 및 출력
    for (int i = 0; i < loop; ++i)          totalSpent += spentTimes[i];
    printf("average time spent: %.6f s.\n", totalSpent / loop);
    free(sample);
}

void runTests(int init_srand, unsigned loop, void (*funcs[])(int*, unsigned), unsigned funcsSize, long size, int maxInt) {
    int* sampleArr = getRandArr(size, maxInt);                              // 샘플 생성
    if (init_srand)                             srand(time(NULL));          // 랜덤시드주입
    for (unsigned i = 0; i < funcsSize; ++i)    doTest(funcs[i], loop, sampleArr, size);    // 각 테스트 실행
    free(sampleArr);
}