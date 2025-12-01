#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// Prototypes:

// helper methods
inline void swap(int* a, int* b);
void printArr   (const int* arr, const long size);

// for sort time bench marking
int* getRandArr (const long size, const int maxInt);
void doTest     (void (*func)(int*, long), int loop, int* sampleArr, long sampleSize);
bool isSameArr  (const int* first, const int* last, const long sz);
void runTests   (int init_srand, int testLoop, void (*funcs[])(int*, long), int funcsSize, int* sample, long sampleSize);

// sort
void bubble     (int* arr, long size);
void selection  (int* arr, long size);
void insertion  (int* arr, long size);
void shell      (int* arr, long size);
void merge      (int* arr, long size);              
void quick      (int* arr, long size);

// 개선된 정렬
void knShell    (int* arr, long size);
void quickPtr   (int* arr, long size);      // quickPtr core: 포인터 버전 (7% 정도개선)
void sbMerge    (int* arr, long size);      // merge 개선: 1회만 버퍼할당.(25% 정도개선, 메모리복사 오버헤드)


// qsort(stdlib.h) 전용 비교함수
int compare_int (const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return (x > y) - (x < y); // 양수, 음수, 0 반환
}



//! MAIN
int main() {
    srand(time(NULL));
    
    // 다음 test 배열의 boolean 값에 따라 검사를 진행
    bool test[5] = {

        // 1.정렬 출력,  2.랜덤샘플 정렬출력,  3.정렬검증,  4.속도측정(기본),  5.속도측정(고성능)
        false, false, false, true, true

    };

    

    // 1. 정렬 출력:    직접 입력한 arr를 정렬하여 출력
    if (test[0])
    {
        void (*func)(int*, long) = 
        
            // 정렬방법
            sbMerge;             

        int arr[] = { 2, 3, 7, 1, 9, 6, 0, 5, 4, 8 };   // 정렬배열
        int arrSz = sizeof(arr) / sizeof(arr[0]);
        func(arr, arrSz);
        printf("result: ");
        printArr(arr, arrSz);
    }


    // 2. 샘플 정렬 출력:   func로 할당된 정렬방밥으로 무작위배열 생성후 정렬하여 출력(정렬 전/후 출력)
    if (test[1])
    {
        void (*func)(int*, long) = 

            // 정렬방법
            quick;

        int randomLoop = 3;                             // 샘플갯수
        int sampleSize = 20;                            // 샘플길이
        int max = 100;                                  // 샘플요소 최대값

        int* sample = NULL;
        for (int i = 0; i < randomLoop; ++i) {
            sample = getRandArr(sampleSize, max);
            printf("before:\t");
            printArr(sample, sampleSize);
            func(sample, sampleSize);
            printf("after:\t");
            printArr(sample, sampleSize);
            free(sample);
        }
    }


    // 3. 정렬 신뢰검사:    func로 할당된 정렬방법으로 qsort와 비교하여 검사. 'testLoop'회 만큼 'sz'크기의 무작위배열 검사
    if (test[2])
    {
        void (*func)(int*, long) = {
            
            // 정렬방법
            quickPtr
        };

        int testLoop = 1000;                        // 검증횟수
        int sz = 10000;                             // 샘플길이
        int max = 10000;                            // 샘플요소 최대값
        int failCount = 0;

        // 반복
        for (int l = testLoop; l > 0; --l) {
            // 샘플생성
            int* checkSample =  getRandArr(sz, max);
            int* copySample =   malloc(sz * sizeof(int));
            memcpy(copySample, checkSample, sz * sizeof(int));
            if (!isSameArr(checkSample, copySample, sz))    { printf("[ERR]샘플할당 동일검증실패!\n"); failCount++; break; }

            // 정렬
            (*func)(checkSample, sz);
            qsort(copySample, sz, sizeof(int), compare_int);
            
            // 정렬검증과 결과출력 준비
            bool isSame =   isSameArr(checkSample, copySample, sz);
            if (!isSame)    failCount++;

            // 샘플 메모리 해제
            free(checkSample);
            free(copySample);
        }

        // 결과 출력
        if (failCount)  printf("\n[실패]실패횟수: %d\n", failCount);
        else            printf("\n[성공]샘플길이: %d \t정렬횟수: %d회 \t정렬검증 성공\n", sz, testLoop);
    }


    // 4. 기본 성능측정:    funcs배열에 할당된 함수들을 모두 성능측정
    if (test[3]) {
        printf("\nBenchmark Sorting...\n");
        void (*funcs[])(int*, long) = {

            // 정렬방법
            bubble, selection, insertion, shell, knShell, quick, quickPtr, merge, sbMerge

        };

        int initSrand = 0;          // 시드초기화 실행여부(0 | 1)
        int loop = 1;               // 검사횟수: 평균값 산출됨
        long size = 100000;         // 샘플크기

        int* sample = getRandArr(size, 10000);
        runTests(initSrand, loop, funcs, sizeof(funcs) / sizeof(funcs[0]), sample, size);
        free(sample);
    }

    // 5. 고성능 성능측정
    if (test[4]) {
        printf("\nBenchmark Sorting...\n");
        void (*highPerfomFuncs[])(int*, long) = {

            // 정렬방법. 추가/삭제 가능
            merge, sbMerge, quick, quickPtr

        };

        int initSrand = 0;          // 시드초기화 실행여부(0 | 1)
        int loop = 1;               // 검사횟수: 평균값 산출됨
        long size = 100000000;      // 샘플크기

        int* sample = getRandArr(size, 10000);
        runTests(initSrand, loop, highPerfomFuncs, sizeof(highPerfomFuncs) / sizeof(highPerfomFuncs[0]), sample, size);

        // qsort(stdlib.h내장) 은 단한번만 실행. 외부구현하지 않음.
        clock_t start = clock();
        qsort(sample, size, sizeof(int), compare_int);
        double res = (double)(clock() - start) / CLOCKS_PER_SEC;
        printf("qsort 기본정렬시간: %.6f s.\n", res);

        free(sample);
    }

    return 0;
}




// 함수 구현부(정의)

void swap(int* a, int* b) { int tmp = *a; *a = *b; *b = tmp; }
void printArr(const int* arr, const long size) {
    // 배열출력
    printf("{ %d", arr[0]);
    for (long i = 1; i < size; ++i)     printf(", %d", arr[i]);
    printf(" }\n");
}

int* getRandArr(const long size, const int maxInt) {
    // 메모리 해제 주의. 동적할당된 랜덤 정수배열 리턴
    int* res = malloc(sizeof(int) * size);      
    for (long i = 0; i < size; ++i)             res[i] = rand() % maxInt + 1;
    return res;
}

void doTest(void (*func)(int*, long), int loop, int* sampleArr, long sampleSize) {
    // 벤치마크 코어함수. func정렬을 loop만큼 sampleArr를 복사하여 실행.
    int* copySample = malloc(sizeof(int) * sampleSize);   // 샘플 복사될 메모리 할당
    double spentTimes[loop];                    // 소요시간 기록 배열
    double totalSpent = 0;                      // 최종 누적 시간 기록

    for (int i = 0; i < loop; ++i) {
        memcpy(copySample, sampleArr, sampleSize * sizeof(int));        // 샘플 초기화
        clock_t start = clock();
        func(copySample, sampleSize);
        spentTimes[i] = (double)(clock() - start) / CLOCKS_PER_SEC;     // 시간 기록
    }
    // 시간 평균 산출 및 출력
    for (int i = 0; i < loop; ++i)          totalSpent += spentTimes[i];
    printf("average time spent: %.6f s.\n", totalSpent / loop);
    free(copySample);
}

void runTests(int init_srand, int testLoop, void (*funcs[])(int*, long), int funcsSize, int* sample, long sampleSize) {
    // doTest 의 래퍼함수.
    if (init_srand)
    srand(time(NULL));                  
    for (int i = 0; i < funcsSize; ++i)    
        doTest(funcs[i], testLoop, sample, sampleSize);    // 각 테스트 실행
}

bool isSameArr(const int* first, const int* last, const long sz) {
    // first 배열과 last 배열이 같음을 검증
    for (long i = 0; i < sz; ++i)
        if (*(first + i) != *(last + i)) {
            printf("%ld: %d != %d\n", i, *(first + i), *(last + i));
            return false;
        }
    return true;
}




void bubble(int* arr, long size) {
    // j와 j + 1의 교환. 최소값 찾기지만 최대값 교차하며 밀어내기. i의 기저조건 size - 1, j의 기저조건 size - 1 - i 에 주의
    for (long i = 0; i < size - 1; ++i) {
        bool swapped = false;
        for (long j = 0; j < size - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr + j, arr + j + 1);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selection(int* arr, long size) {
    // i부터(1씩증가) 마지막까지의 배열들중 최소값의 인덱스를 찾아 i로 꽂아넣음.
    for (long i = 0; i < size; ++i) {
        long minIdx = i;
        for (long j = i; j < size; ++j) {
            if (arr[minIdx] > arr[j])       minIdx = j;
        }
        if (minIdx != i)        swap(arr + i, arr + minIdx);
    }
}

void insertion(int* arr, long size) {
    // i를 기준으로 좌측배열만 조정(이로인해 1로 초기화). 따라서 j는 i로 초기화 되며 1씩감소. i요소를 bf로 저장해 삽입위치 j가 정해질 때까지 직전요소를 현재위치로 밀어낸 후 bf를 j로 삽입.
    for (long i = 1; i < size; ++i) {
        int buffer =        arr[i];
        long j = i;
        for (; j > 0 && arr[j - 1] > buffer; --j)
            arr[j] = arr[j - 1];
        if (j != i)         arr[j] = buffer;
    }
}

void shell(int* arr, long size) {
    // insert의 확장개념. gap(step) 만큼 크게 이동시켜 잦은이동을 미연에 방지. 마지막엔 step1(기존 삽입정렬)을 무조건 실행
    int step = size / 2;
    while (step > 0) { 
        for (long i = step; i < size; ++i) {
            int buffer = arr[i];
            long j = i;
            for (; j >= step && arr[j - step] > buffer; j -= step)      arr[j] = arr[j - step];
            if (j != i) { arr[j] = buffer;}
        }
        step /= 2;
    }
}

void knShell(int* arr, long size) {
    // shell 정렬의 단순 비교 정수들 register 적용과 크누스수열 적용(연속된 값들이 서로의 약수가 되지 않도록 설계되어 최적화)
    int step = 1;
    while(step < size / 3) { step = 3 * step + 1; }     // init step.
    long i;
    long j;
    int buffer;

    while (step > 0) { 
        for (i = step; i < size; ++i) {
            buffer = arr[i];
            for (j = i; j >= step && arr[j - step] > buffer; j -= step)         arr[j] = arr[j - step];
            if (j != i) { arr[j] = buffer;}
        }
        step /= 3;                                      // update step
    }    
}

void _quick(int* arr, int left, int right) {
    // pivot을 기준으로 큰 값배열과 작은 값배열을 분할하여 재귀실행
    // 인덱스 기반의 정렬 스타일
    if (right - left <= 256)    { insertion(arr, right-left);  return; }
    long pL = left, pR = right;
    int pivot = arr[(pL + pR) / 2], tmp;

    while (pL <= pR) {
        while(pivot > arr[pL])  pL++;
        while(pivot < arr[pR])  pR--;
        if (pL <= pR)           swap(arr + (pL++), arr + (pR--));
    } 
    if (left < pR)              _quick(arr, left, pR);
    if (right > pL)             _quick(arr, pL, right);
}

void quick(int* arr, long size) {
    // _quick의 래퍼(사용자 인터페이스)함수
    _quick(arr, 0, size - 1); 
}

void _quickPtr(int* start, int* end) {
    // quick를 포인터 스타일로 개선
    const long sz =     end - start;
    if (sz <= 1)        return;
    if (sz <= 256)      { insertion(start, sz); return; }
    int* lPtr =         start;
    int* rPtr =         end - 1;
    const int pivot =   *(start + (sz / 2));

    while (lPtr <= rPtr) {
        while (pivot > *lPtr)   ++lPtr;
        while (pivot < *rPtr)   --rPtr;
        if (lPtr <= rPtr)       swap(lPtr++, rPtr--);
    }

    if (rPtr > start)           _quickPtr(start, rPtr + 1);
    if (lPtr < end -1)          _quickPtr(lPtr, end);
}

void quickPtr(int* arr, long size) {
    // _quickPtr 포인터 스타일의 퀵정렬 래퍼(사용자 인터페이스) 함수
    _quickPtr(arr, arr + size);
}

void merge(int* arr, long size) {
    // 병합정렬. lArr, rArr 할당과 복사 오버헤드 있음.

    // 기저조건: 정렬할 것이 없을 때 아무 정렬도 하지 않고 종료
    if (size <= 1)      return;
    if (size <= 64)     { insertion(arr, size);    return; }

    // 분할
    long lSize =        size / 2;
    long rSize =        size - lSize;
    int* lArr =         malloc (lSize * sizeof(int));
    int* rArr =         malloc (rSize * sizeof(int));
    memcpy(lArr, arr, lSize * sizeof(int));
    memcpy(rArr, arr + lSize, rSize * sizeof(int));

    // 정복
    merge(lArr, lSize);
    merge(rArr, rSize);

    // 합병
    long lIdx = 0, rIdx = 0, aIdx =0;
    while (lIdx < lSize && rIdx < rSize && aIdx < size) {
        if (lArr[lIdx] < rArr[rIdx])    arr[aIdx++] = lArr[lIdx++];
        else arr[aIdx++] =              rArr[rIdx++];
    }
    // 나머지 발생시 lArr부터 합병
    while (lIdx < lSize)                arr[aIdx++] = lArr[lIdx++];
    while (rIdx < rSize)                arr[aIdx++] = rArr[rIdx++];
    free(lArr);
    free(rArr);
}

void _singleBufferMerge(int* start, int* end, int* bf) {
    // 포인터방식으로 개선, bf를 할당받아 재활용
    const int size =    end - start;
    if (size <= 1)      return;
    if (size <= 64)     { insertion(start, size);    return; }
    const int lSize =   size / 2;

    _singleBufferMerge(start, start + lSize, bf);
    _singleBufferMerge(start + lSize, start + size, bf);

    int* lPtr =         start;
    int* rPtr =         start + lSize;
    const int* lEnd =   start + lSize;
    const int* rEnd =   start + size;
    int* resPtr =       bf;

    while (lPtr < lEnd && rPtr < rEnd) {
        if (*lPtr < *rPtr)  *(resPtr++) = *(lPtr++);
        else                *(resPtr++) = *(rPtr++);
    }

    while (lPtr < lEnd)     *(resPtr++) = *(lPtr++);
    while (rPtr < rEnd)     *(resPtr++) = *(rPtr++);

    memcpy(start, bf, size * sizeof(int));
}

void sbMerge(int* arr, long size) {
    // _singleBufferMerge 의 래퍼(사용자 인터페이스) 함수
    int* end = arr + size;
    int* bf = malloc(size * sizeof(int));
    _singleBufferMerge(arr, end, bf);
    free(bf);
}
