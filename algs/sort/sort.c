#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// Prototypes:

// helper methods
inline void swap(int* a, int* b);
void printArr(const int* arr, const long size);

// for sort time bench marking
int* getRandArr(const long size, const int maxInt);
void doTest(void (*func)(int*, long), int loop, int* sampleArr, long sampleSize);
bool isSameArr(const int* first, const int* last, const long sz);
void runTests(int init_srand, int testLoop, void (*funcs[])(int*, long), int funcsSize, int* sample, long sampleSize);

// sort
void bubble(int* arr, long size);
void selection(int* arr, long size);
void insertion(int* arr, long size);
void shell(int* arr, long size);
void knuth_shell(int* arr, long size);
void merge(int* arr, long size);              
void _quick(int* arr, int left, int right);
void quick(int* arr, long size)     { _quick(arr, 0, size - 1); }

// 개선된 정렬
void _quickPtr(int* start, int* end);                                   // quickPtr core: 포인터 버전 (7% 정도개선)
void quickPtr(int* arr, long size)  { _quickPtr(arr, arr + size); }
void _singleBfMerge(int* start, int* end, int* bf);                     // merge 개선: 1회만 버퍼할당.(25% 정도개선, 메모리복사 오버헤드)
void singleBfMerge(int* arr, long size);


// TEST
int compare_int(const void* a, const void* b) {
    // qsort 전용 조건 비교식 함수
    int x = *(int*)a;
    int y = *(int*)b;
    return (x > y) - (x < y); // 양수, 음수, 0 반환
}



// 메인함수
int main() {

    // 다음 test 배열의 boolean 값에 따라 검사를 진행
    bool test[5] = {
        // 간단한 정렬 출력, 무작위 샘플 정렬 출력, 두 정렬로 정렬검증, 벤치마크테스트(기본), 고성능벤치마크
        false, false, false, false, true
    };

    srand(time(NULL));         // 매 실행마다 다름을 보장하기 위한것이지, 보안적인 랜덤시드는 아님

    // 1. 간단한 정렬 출력
    if (test[0])
    {
        void (*func)(int*, long) = singleBfMerge;       // 정렬선택
        int arr[] = { 2, 3, 7, 1, 9, 6, 0, 5, 4, 8 };   // 정렬배열
        int arrSz = sizeof(arr) / sizeof(arr[0]);
        func(arr, arrSz);
        printArr(arr, arrSz);
    }


    // 2. 무작위 샘플 정렬 출력
    if (test[1])
    {
        void (*func)(int*, long) = quick;               // 정렬방법
        int randomLoop = 3;                             // 샘플갯수
        int sampleSize = 20;                            // 샘플길이
        int max = 100;                                  // 샘플요소 최대값

        int* sample = NULL;
        for (int i = 0; i < randomLoop; ++i) {
            sample = getRandArr(sampleSize, max);
            printf("before: ");
            printArr(sample, sampleSize);
            func(sample, sampleSize);
            printf("after: ");
            printArr(sample, sampleSize);
            free(sample);
        }
    }


    // 3. 두가지 정렬의 결과가 같음을 검사
    if (test[2])
    {
        const void (*func[2])(int*, long) = {
            // 정렬 방법
            singleBfMerge, quickPtr
        };


        int testLoop = 1000;                        // 검증횟수
        int sz = 10000;                             // 샘플길이
        int max = 10000;                            // 샘플요소 최대값
        int failCount = 0;

        for (int l = testLoop; l > 0; --l) {
            // 과정1: 샘플생성
            int* checkSample =  getRandArr(sz, max);
            int* copySample =   malloc(sz * sizeof(int));
            memcpy(copySample, checkSample, sz * sizeof(int));
            if (!isSameArr(checkSample, copySample, sz))    { printf("[ERR]샘플할당 동일검증실패!\n"); failCount++; break; }

            // 과정2: 정렬
            (*func)         (checkSample, sz);
            (*(func + 1))   (copySample, sz);
            
            // 과정3: 검증과 결과출력
            bool isSame =   isSameArr(checkSample, copySample, sz);
            if (!isSame)    failCount++;

            // 과정4: 샘플 배열 메모리 해제
            free(checkSample);
            free(copySample);
        }

        if (failCount)  printf("[실패]실패횟수: %d\n", failCount);
        else            printf("[성공]샘플길이: %d 정렬횟수: %d회 정렬검증 성공\n", sz, testLoop);
    }


    // 4. 기본 벤치마크
    if (test[3]) {
        printf("\nBenchmark Sorting...\n");
        void (*funcs[])(int*, long) = {

            // 정렬방법. 추가/삭제 가능
            selection, insertion, shell, knuth_shell, quick, quickPtr, merge, singleBfMerge

        };

        int initSrand = 0;          // 시드초기화 실행여부(0 | 1)
        int loop = 1;               // 검사횟수: 평균값 산출됨
        long size = 100000;          // 샘플크기

        int* sample = getRandArr(size, 10000);
        runTests(initSrand, loop, funcs, sizeof(funcs) / sizeof(funcs[0]), sample, size);
        free(sample);
    }

    // 5. 고성능 벤치마크
    if (test[4]) {
        printf("\nBenchmark Sorting...\n");
        void (*highPerfomFuncs[])(int*, long) = {

            // 정렬방법. 추가/삭제 가능
            merge, singleBfMerge, quick, quickPtr

        };

        int initSrand = 0;          // 시드초기화 실행여부(0 | 1)
        int loop = 1;               // 검사횟수: 평균값 산출됨
        long size = 100000000;      // 샘플크기

        int* sample = getRandArr(size, 10000);
        runTests(initSrand, loop, highPerfomFuncs, sizeof(highPerfomFuncs) / sizeof(highPerfomFuncs[0]), sample, size);

        // qsort(stdlib.h내장) 은 구현 복잡도로 인해 단한번만 실행.
        clock_t start = clock();
        qsort(sample, size, sizeof(int), compare_int);
        double res = (double)(clock() - start) / CLOCKS_PER_SEC;
        printf("qsort 기본정렬시간: %.6f\n", res);

        free(sample);
    }

    return 0;
}



// 함수 구현부(정의)

void swap(int* a, int* b) { int tmp = *a; *a = *b; *b = tmp; }
void printArr(const int* arr, const long size) { printf("{%d", arr[0]); for (long i = 1; i < size; ++i) printf(", %d", arr[i]); printf("}\n"); }



// 최소값 찾기. 큰 값을 찾아 배열 오른쪽으로 밀어냄 (거품이 교차되듯이)
void bubble(int* arr, long size) {
    for (long i = 0; i < size - 1; ++i) {
        for (long j = 0; j < size - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}

// 0번 인덱스부터 최소값을 찾고(선택), 있다면 0번과 스왑. 바뀐건 다음 루프에서 처리
void selection(int* arr, long size) {
    for (long i = 0; i < size; ++i) {
        long minIdx = i;
        for (long j = i; j < size; ++j) {
            if (arr[minIdx] > arr[j])       minIdx = j;
        }
        if (minIdx != i)        swap(arr + i, arr + minIdx);
    }
}

// i를 기준으로 i의 좌측 배열만 조정하며, 최소값/최대값 등을 저장후 삽입위치 정해질 때 까지 배열을 한칸씩 밀어냄.
void insertion(int* arr, long size) {
    for (long i = 1; i < size; ++i) {
        int buffer =        arr[i];
        long j = i;
        for (; j > 0 && arr[j - 1] > buffer; --j)
            arr[j] = arr[j - 1];
        if (j != i)         arr[j] = buffer;
    }
}

// 쉘정렬은 insert의 확장개념. gap(step) 만큼 크게 이동시켜 잦은이동을 미연에 방지. 마지막엔 step1(기존 삽입정렬)을 무조건 실행
void shell(int* arr, long size) {
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

// shell 정렬의 단순 비교 정수들 register 적용과 크누스수열 적용(연속된 값들이 서로의 약수가 되지 않도록 설계되어 최적화)
void knuth_shell(int* arr, long size) {
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

// 메모리 해제 주의. 동적할당된 랜덤 정수배열 리턴
int* getRandArr(const long size, const int maxInt) {
    int* res = malloc(sizeof(int) * size);      
    for (long i = 0; i < size; ++i)             res[i] = rand() % maxInt + 1;
    return res;
}


// 벤치마크 코어함수. func정렬을 loop만큼 sampleArr를 복사하여 실행.
void doTest(void (*func)(int*, long), int loop, int* sampleArr, long sampleSize) {
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
    if (init_srand)
    srand(time(NULL));                  
    for (int i = 0; i < funcsSize; ++i)    
        doTest(funcs[i], testLoop, sample, sampleSize);    // 각 테스트 실행
}


bool isSameArr(const int* first, const int* last, const long sz) {
    for (long i = 0; i < sz; ++i)
        if (*(first + i) != *(last + i)) {
            printf("%d: %d != %d\n", i, *(first + i), *(last + i));
            return false;
        }
    return true;
}



// quick정렬. pivot을 기준으로 큰 값배열과 작은 값배열을 분할하여 재귀실행
void _quick(int* arr, int left, int right) {
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

void _quickPtr(int* start, int* end) {
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

void merge(int* arr, long size) {
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

// 래퍼함수에서 bf를 할당받아 재활용. 포인터방식으로 개선
void _singleBfMerge(int* start, int* end, int* bf) {
    const int size =    end - start;
    if (size <= 1)      return;
    if (size <= 64)     { insertion(start, size);    return; }
    const int lSize =   size / 2;

    _singleBfMerge(start, start + lSize, bf);
    _singleBfMerge(start + lSize, start + size, bf);

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

void singleBfMerge(int* arr, long size) {
    int* end = arr + size;
    int* bf = malloc(size * sizeof(int));
    _singleBfMerge(arr, end, bf);
    free(bf);
}
