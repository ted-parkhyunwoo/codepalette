#include <iostream>
#include <time.h>
#include <algorithm>            // 일부환경에서는 다음 두 헤더가 선언되어야함 (std::is_sorted, memcpy)
#include <string.h>

int QUICK_MIN_SIZE = 384;       // insertion sort로 전환될 배열크기 임계값 상수
int MERGE_MIN_SIZE = 64;

constexpr int INT_SIZE = sizeof(int);
/* DESC:
    data type:  모든 정렬은 정수형 데이터만 사용하며, 모두 오름차순 정렬됨
                배열의 자료형은 정수형 배열을 사용함
    parameter:  정렬함수 파라미터는 모두 정수형 포인터를 사용하며, 정수형 배열 주소포인터로 다루어짐.
    args:       반복자처럼 start는 배열의 시작을, end는 배열의 마지막 요소 '다음'을 가리킴
    return:     정렬함수는 void. 새로운 배열을 리턴하지 않고, 원본배열을 수정함
    sort:       quick, merge는 임계값(배열길이 128 혹은 64 이하) 도달시 insert정렬로 됨. 따라서 정렬신뢰검사에는 샘플크기를 키워야함
    compile:    -O3 혹은 -Ofast(비권장)로 사용하면, register 키워드 명시 없이도 필요에 따라 최적화됨
    기타서술:
                정렬 신뢰검사(올바르게 정렬되는지), 정렬소요시간측정 등이 구현됨.
                범용성 고려. 일부 cpp 구현을 컨버팅을 하면 거의 모든 기능을 c에서도 그대로 쓸 수 있음

    code structure:
        HEADER                      헤더선언
        descripion comment          코드설명
        definition(PROTOTYPES)      함수선언
        testcodes                   구조화 되기 전 테스트 코드
        MAIN                        메인함수
        declaration                 함수정의(구현)
    
    functions:
        Helper: 무작위샘플배열생성, swap, 출력, 배열복사기능
        Test: 출력테스트, 시간측정테스트
        Sort: 버블, 선택, 삽입, 쉘, 퀵, 합병정렬

    TODOLIST:
        부분정렬(quick) 구현
        힙정렬 구현
*/


// PROTOTYPES

// Helper
int* getRandomIntArr(const int size, const int max = 10000);    //! DO NOT FORGET FREE MEMORY   random integer array return.
void printIntArr(const int* start, const int* end);             // print array use pointer
inline void swap(int* x, int* y);                               // swap integer data. 인라인 선언

// Test
void isSortedCorrect(void (*sort)(int*, int*), const int sampleSize = 13, const bool printArr = false);     // 정렬신뢰검사 
void benchmarkSort  (void (*sort)(int*, int*), const int* sample = nullptr, const int sampleSize = 1000000);// 정렬시간측정

// Sort
void bubble (int* start, int* end);
void select (int* start, int* end);
void insert (int* start, int* end);
void shell  (int* start, int* end);
void quick  (int* start, int* end);
void merge  (int* start, int* end);
void _singleBfMerge(int* start, int* end, int* bf);
void singleBfMerge(int* start, int* end);

// test codes: 
// thresholdVar는 임계값 변수.
// 각 임계값을 n번 측정해 평균 시간을 계산한 후 가장 빠른 임계값을 찾는다.
void findOptimalThreshold(void (*sort)(int*,int*), int* thresholdVar, int sampleCount) {
    int candidates[] = {4,8,16,32,48,64,96,128,192,256,320,384,512,768,1024,2048,4096};
    int candCount = sizeof(candidates)/sizeof(candidates[0]);
    int sampleSize = 100000000;
    int initial = *thresholdVar;
    int* record = (int*)malloc(sizeof(int)*sampleCount);

    for (int s = 0; s < sampleCount; ++s) {
        printf("sample %d\n", s+1);
        int* original = getRandomIntArr(sampleSize);
        double bestTime = 1e9; int bestT = -1;

        for (int i = 0; i < candCount; ++i) {
            *thresholdVar = candidates[i];
            int* buf = (int*)malloc(sizeof(int)*sampleSize);
            memcpy(buf, original, sizeof(int)*sampleSize);

            clock_t st = clock();
            sort(buf, buf + sampleSize);
            double t = (double)(clock() - st) / CLOCKS_PER_SEC;

            if (t < bestTime) { bestTime = t; bestT = candidates[i]; }
            free(buf);
        }
        free(original);
        record[s] = bestT;
    }

    *thresholdVar = initial;

    double avg = 0; for (int i=0;i<sampleCount;i++) avg += record[i];
    avg /= sampleCount;

    int mode = -1, maxCnt = -1;
    for (int i=0;i<candCount;i++) {
        int cnt = 0;
        for (int s=0;s<sampleCount;s++) if (record[s] == candidates[i]) cnt++;
        if (cnt > maxCnt) { maxCnt = cnt; mode = candidates[i]; }
    }

    free(record);

    printf("avg=%d\n", (int)avg);
    printf("mode=%d\n", mode);
}


// MAIN 
int main() {
    srand(time(NULL));

    // instance sample test: 샘플 자동해제됨.
    benchmarkSort(quick);

    // find Threshold
    findOptimalThreshold(quick, &QUICK_MIN_SIZE, 5);

    // 테스트 실행 트리거: 정렬검증, 일반 시간측정, 고성능 시간측정
    const bool test[] = {
        false, false, false
    };
    
    // 정렬검증
    if (test[0]) {
        const int longSampleSize = 10000;
        isSortedCorrect(bubble);
        isSortedCorrect(select);
        isSortedCorrect(insert);
        isSortedCorrect(shell, longSampleSize);
        isSortedCorrect(quick, longSampleSize);
        isSortedCorrect(merge, longSampleSize);
        isSortedCorrect(singleBfMerge, 10, true);
        isSortedCorrect(singleBfMerge, longSampleSize);
    }

    // 일반 시간측정
    if (test[1]) {
        const int sampleSize = 10000;
        const int* sample = getRandomIntArr(sampleSize);
        benchmarkSort(shell, sample, sampleSize);
        benchmarkSort(quick, sample, sampleSize);
        benchmarkSort(merge, sample, sampleSize);
        benchmarkSort(singleBfMerge, sample, sampleSize);
        delete[] sample;
    }

    // 고성능 시간측정
    if (test[2]) {
        const int sampleSize = 100000000;
        const int* sample = getRandomIntArr(sampleSize);
        benchmarkSort(merge, sample, sampleSize);
        benchmarkSort(singleBfMerge, sample, sampleSize);
        benchmarkSort(std::sort, sample, sampleSize);
        benchmarkSort(quick, sample, sampleSize);
        delete[] sample;
    }

    return 0;
}


// 함수 구현(정의)

//! DO NOT FORGET FREE MEMORY
int* getRandomIntArr(const int size, const int max) {
    int* res =                              new int[size];
    for (int i = 0; i < size; ++i)          *(res + i) = rand() % max + 1;
    return res;
}

void printIntArr(const int* start, const int* end) {
    printf("[");
    if (start < end)                        printf("%d", *start);
    else                                    { printf("]\n");    return; }
    for (int i = 1; i < end - start; ++i)   printf(", %d", *(start + i));
    printf("]\n");
}

void swap(int* x, int* y) {
    const int tmp = *x;
    *x = *y;
    *y = tmp;
}

void isSortedCorrect(void (*sort)(int*, int*), const int sampleSize, const bool printArr) {
    // 오름차순인지 검사, 복사생성 후 정렬검증(std::sort 비교)
    printf("\nsort test(sample:%d) :\n", sampleSize);                   // 함수 진입 출력

    int* sample =                   getRandomIntArr(sampleSize, 50);    // 샘플 생성
    int* cp =                       new int[sampleSize];                // 샘플 복사할당
    memcpy(cp, sample, sampleSize * INT_SIZE);

    if (printArr)                   { printf("\t");    printIntArr(sample, sample + sampleSize); }
    
    sort(sample, sample + sampleSize);                                  // 정렬
    std::sort(cp, cp + sampleSize);                                     // 복사샘플 정렬(비교용)

    bool isSorted =                   true;                             // 정렬검증 성공여부
    for (int i = 0; i < sampleSize; ++i)
        if (sample[i] != cp[i])     { isSorted = false; break; }

    // 결과 출력과 메모리 해제
    if (printArr)                   { printf("\t");   printIntArr(sample, sample + sampleSize); }
    printf("\tsort: %s\n", isSorted?"OK":"[WARING] Fail. \nsort correct :");   
    if ((!isSorted) && printArr)    { printf("\t");   printIntArr(cp, cp + sampleSize); }

    delete[] sample;
    delete[] cp;
}

void benchmarkSort(void (*sort)(int*, int*), const int* sample, const int sampleSize) {
    // sample을 정렬하는데 걸리는 시간 측정하여 출력함. sample 입력시 복사생성(원본샘플손상금지), nullptr시 새로할당
    printf("\nbenchmark (sample size %d) :\n", sampleSize);

    // 사용자정의샘플, 임시샘플인지에 따라 cp를 복사하거나 새로 할당
    bool isInstanceSample =         false;
    if (sample == nullptr)          isInstanceSample = true;
    int* cp = isInstanceSample?     getRandomIntArr(sampleSize) : new int[sampleSize];
    if (!isInstanceSample)          memcpy(cp, sample, INT_SIZE * sampleSize); 
    
    // 정렬시간 측정
    const clock_t timeStart =       clock();
    sort(cp, cp + sampleSize);
    const double timeResult =       (double)(clock() - timeStart) / CLOCKS_PER_SEC;
    
    // 결과 출력과 메모리 해제
    printf("\ttime: %.6fs.\n", timeResult);
    delete[] cp;
}


void bubble(int* start, int* end) {
    // 우측부터 확정정렬. 뽑은요소와 다음요소간 비교연산하며 연속 스왑.
    for (int* p = start; p < end - 1; p++) {
        for (int* q = start; q < end - 1 - (p - start); q++)
            if (*q > *(q + 1))
                swap(q, q + 1);
    }
}

void select(int* start, int* end) {
    // 좌측부터 확정정렬. 최소값을 찾아 배열 좌측부터 확정 정렬
    for (int* p = start; p < end; p++) {
        int* bf = p;

        for (int* q = p; q < end; q++) 
            if (*bf > *q) bf = q;

        if (bf != p)
            swap(bf, p);
    }
}

void insert(int* start, int* end) {
    // p 기준 좌우 분할후 p를 저장하여 , 좌측에서만 p 비교 조건만족시까지 밀어내기 후 p삽입. 반복문 종료까지 정렬 확정되지 않음.
    for (int* p = start + 1; p < end; p++) {
        const int bf = *p;
        int* q = p;

        for (; q > start && bf < *(q - 1); --q)
            *q = *(q - 1);

        if (q != p)
            *q = bf;
    }
}

void shell(int* start, int* end) {
    // insert와 같으나, 특정 요소가 많은 swap이 일어날정도로 거리가 멀 경우를 대비하여 gap 만큼 크게 이동후 마지막에 insert정렬(gap = 1)
    int gap = 1;
    while (gap < (end - start) / 3)  gap = gap * 3 + 1;     // update gap using knuth gap

    for (;gap > 0; gap /= 3) {
        for (int* p = start + gap; p < end; p++) {
            int bf = *p;
            int* q = p;

            for (; q - start >= gap && bf < *(q - gap); q -= gap)
                *q = *(q - gap);

            if (q != p)
                *q = bf;
        }
    }
}

void quick(int* start, int* end) {          // end 혹은 right, 재귀호출과 조건검사에 -1 등의 보정이 들어감.
    // pivot기준 좌측과 우측을 분할하여 좌측은 작은쪽, 우측은 큰쪽으로 스왑하고 좌 우측 따로 재귀실행 (더이상 분할할 수 없을 때 까지)

    const int sz =      end - start;
    if (sz <= 1)        return;
    // 분할기저조건: 분할중 배열 길이 임계값 도달시 삽입정렬로 전환
    if (sz <= QUICK_MIN_SIZE)   { insert(start, end); return; }    

    // 분할
    int* lPtr =         start;
    int* rPtr =         end - 1;       //  보정: end는 마지막요소가 아님.마지막 요소 다음을 가리킴.
    const int pivot =   *(start + ((sz) / 2));

    // 분할정렬: pivot 기준으로 작은쪽은 left로, 큰쪽은 right로 스왑. 조건: 교차직후 종료
    while (lPtr <= rPtr) {
        while (pivot > *lPtr)       ++lPtr;
        while (pivot < *rPtr)       --rPtr;
        if (lPtr <= rPtr) {
            swap(lPtr, rPtr);
            ++lPtr;
            --rPtr;
        }
    }

    // 정복 조건: 재귀호출될 right와 left 가 원본 배열의 범위를 벗어나지 않고, 최소 1개라도 요소를 갖고있음.
    if (rPtr > start)       quick(start, rPtr + 1);     // 보정: sz산출 정상화 및 재귀호출시 분할에서 rPtr이 end - 1로 초기화되므로.
    if (lPtr < end - 1)     quick(lPtr, end);           // 보정: 조건식 end는 -1 하지 않아도 작동은 정상.
}

void merge(int* start, int* end) {
    // memcpy가 재귀적으로 실행되는 상태라 메모리할당이 클 수 있음.(속도는 빠름)
    // 센터기준 좌우로 나눴다가 다시 합치되, 합칠 땐 좌우 비교후 작은것 부터 채워넣음.

    // 기저
    if (start >= end) return;           // 정상 사용시 도달할 리 없음.
    const int sz = end - start;
    if (sz <= 1) return;                // 재귀호출이 아닌 초기 호출될 경우에 도달될 가능성 있음.
    if (sz <= MERGE_MIN_SIZE) {         // 배열 길이 임계값 도달시 삽입정렬전환
        insert(start, end);
        return;
    }        

    // 분할
    const int lSize =  sz / 2;

    int* bf = new int[sz];              // 개선: left, right를 따로 할당하지 않고 복사 할당하여 left, right 별 포지션을 포인터로 다룸.
    memcpy(bf, start, INT_SIZE * sz);

    // 정복
    merge(bf, bf + lSize);
    merge(bf + lSize, bf + sz);

    // 병합(좌우측 하나씩 비교후 최소부터 원본에 채워넣는 정렬하면서)
    int* lPtr = bf;
    int* rPtr = bf + lSize;
    const int* lEnd = bf + lSize;
    const int* rEnd = bf + sz;
    int* resPtr = start;
    
    while (lPtr < lEnd && rPtr < rEnd) {
        if(*lPtr < *rPtr)       *(resPtr++) = *(lPtr++);
        else                    *(resPtr++) = *(rPtr++);
    }

    while (lPtr < lEnd)         *(resPtr++) = *(lPtr++);
    while (rPtr < rEnd)         *(resPtr++) = *(rPtr++);

    // 해제
    delete[] bf;
}


void _singleBfMerge(int* start, int* end, int* bf) {
    // 싱글버퍼합병: 버퍼공간 할당 1회, 대신 memcpy가 매 루프 실행됨(해결하려면 코드 복잡성 증가). 여러환경 검증결과 cpu 혹은 메모리가 좋지않을수록 속도 등에 이득

    // 기저
    if (start >= end) return;
    const int sz = end - start;
    if (sz <= 1) return;
    if (sz <= MERGE_MIN_SIZE) {
        insert(start, end);
        return;
    }        

    // 분할
    const int lSize =  sz / 2;

    // 정복: 재귀호출된 후에는 start가 아래 병합에서 aPtr로 bf를 새로쓰고, memcpy를 통해 start로 덮어씌워지므로, start로 호출하는 것에 의문을 가지거나 걱정하지 않아도 된다.
    _singleBfMerge(start, start + lSize, bf);
    _singleBfMerge(start + lSize, start + sz, bf);

    // 병합: 고쳐진 start를 기준으로 bf를 다시씀
    int* lPtr = start;
    int* rPtr = start + lSize;
    const int* lEnd = start + lSize;
    const int* rEnd = start + sz;
    int* resPtr = bf;
    
    while (lPtr < lEnd && rPtr < rEnd) {
        if(*lPtr < *rPtr)       *(resPtr++) = *(lPtr++);      // 정렬조건(오름/내림차순)
        else                    *(resPtr++) = *(rPtr++);
    }

    while (lPtr < lEnd)         *(resPtr++) = *(lPtr++);
    while (rPtr < rEnd)         *(resPtr++) = *(rPtr++);

    // 갱신: 새로 쓴 bf를 start로 덮어씌움 (매번 할당하진 않지만 그래도 매 루프 오버헤드 발생 -> 해결하려면 코드 복잡성 급증)
    memcpy(start, bf, INT_SIZE * sz);
}

void singleBfMerge(int* start, int* end) {
    // 래퍼함수: 하나의 코드로 bf를 매번 할당하면 오버헤드 증가하므로, 래퍼로 한번만 할당. 정말 버퍼처럼 쓰는 메모리공간. 초기화 필요하지 않음.
    const int sz = end - start;
    int* bf = new int[sz];
    _singleBfMerge(start, end, bf);
    delete[] bf;
}
