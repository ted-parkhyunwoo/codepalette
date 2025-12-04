#include <thread>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <algorithm>            // 일부환경에서는 다음 두 헤더가 선언되어야함 (std::is_sorted, memcpy)
#include <iostream>


//! 임계값 사용할지 여부. QUICK_MIN_SIZE 혹은 MERGE_MIN_SIZE 값에 따라 샘플배열 크기가 작으면 오리지날 퀵, 병합정렬이 실행되지 아니할 수 있음
int USE_THRESHOLD = 1;
int QUICK_MIN_SIZE = USE_THRESHOLD ? 128 : 0;       // insertion sort로 전환될 배열크기 임계값 상수
int MERGE_MIN_SIZE = USE_THRESHOLD ? 64 : 0;


constexpr int INT_SIZE = sizeof(int);

using sortFunction = void(*)(int*, int*);           // 함수포인터(정렬)을 sortFunction이란 타입으로 사용.


/* DESC:
    data type:  모든 정렬은 정수형 데이터만 사용하며, 모두 오름차순 정렬됨
                배열의 자료형은 정수형 배열을 사용함
    parameter:  정렬함수 파라미터는 모두 정수형 포인터를 사용하며, 정수형 배열 주소포인터로 다루어짐.
    args:       반복자처럼 start는 배열의 시작을, end는 배열의 마지막 요소 '다음'을 가리킴
    return:     정렬함수는 void. 새로운 배열을 리턴하지 않고, 원본배열을 수정함
    sort:       quick, merge는 임계값(배열길이 128 혹은 64 이하) 도달시 insert정렬로 됨. 따라서 정렬신뢰검사에는 샘플크기를 키워야함 
    compile:    -O3 혹은 -Ofast(비권장)로 사용하면, register 키워드 명시 없이도 필요에 따라 최적화됨
                bubble 의 경우, 이상하게 -O3가 적용되지 않은 편이 훨씬 빠름. (100만개 15초->8~9초)
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
        힙정렬 구현
*/


// PROTOTYPES

// Helper
int* getRandomIntArr(const unsigned size, const int max = 10000);    //! DO NOT FORGET FREE MEMORY   random integer array return.
void printIntArr(const int* start, const int* end);             // print array use pointer
inline void swap(int* x, int* y);                               // swap integer data. 인라인 선언

// Test


void findOptimalThreshold(sortFunction sort, int* thresholdVar, int sampleCount);     // thresholdVar는 전역 선언된 임계값을 참조해야함.
void isSortedCorrect(sortFunction sort, const unsigned sampleSize = 13, const bool printArr = false);     // 정렬신뢰검사 
void benchmarkSort  (sortFunction sort, const int* sample = nullptr, const unsigned sampleSize = 1000000);// 정렬시간측정

// Sort
void bubble (int* start, int* end);
void select (int* start, int* end);
void insert (int* start, int* end);
void shell  (int* start, int* end);
void quick  (int* start, int* end);
void merge  (int* start, int* end);
void parallel(int* start, int* end);        // quick 사용중(정의에 sortFunc 로 변경 가능)


// test codes: 




//! ---- MAIN ----
int main() {
    srand(time(NULL));
    printf("%zu\n", sizeof(unsigned));

    // instance sample test: 샘플 자동해제됨.
    //benchmarkSort(quick);

    // find Threshold
    // findOptimalThreshold(parallel, &QUICK_MIN_SIZE, 5);

    
    // 테스트 실행 트리거: 정렬검증, 일반 시간측정, 고성능 시간측정, 쓰레드병렬 측정
    const bool test[] = {
        true, true, true, true
    };
    
    // 정렬검증
    if (test[0]) {
        printf("\n--- Validate the Sort ---\n");
        const unsigned longSampleSize = 100000;
        printf("bubble\t\t");     isSortedCorrect(bubble);
        printf("select\t\t");     isSortedCorrect(select);
        printf("insert\t\t");     isSortedCorrect(insert);
        printf("shell\t\t");      isSortedCorrect(shell, longSampleSize);
        printf("quick\t\t");      isSortedCorrect(quick, longSampleSize);
        printf("merge\t\t");      isSortedCorrect(merge, longSampleSize);
        printf("threads\t\t");    isSortedCorrect(parallel, longSampleSize);
    }

    // 일반 시간측정
    if (test[1]) {
        printf("\n--- Benchmark Sorting ---\n");
        const unsigned sampleSize = 100000;
        const int* sample = getRandomIntArr(sampleSize);
        // printf("bubble\t"); benchmarkSort(bubble, sample, sampleSize);       // 버블은 느려서 주석처리
        printf("select\t"); benchmarkSort(select, sample, sampleSize);
        printf("insert\t"); benchmarkSort(insert, sample, sampleSize);
        printf("shell\t");  benchmarkSort(shell, sample, sampleSize);
        printf("merge\t");  benchmarkSort(merge, sample, sampleSize);
        printf("quick\t");  benchmarkSort(quick, sample, sampleSize);
        printf("stdsort\t");benchmarkSort(std::sort, sample, sampleSize);
        printf("threads\t");benchmarkSort(parallel, sample, sampleSize);
        delete[] sample;
    }

    // 고성능 시간측정
    if (test[2]) {
        printf("\n--- High Perfomance Sort ---\n");
        const unsigned sampleSize = 100000000;
        const int* sample = getRandomIntArr(sampleSize);
        printf("merge\t");  benchmarkSort(merge, sample, sampleSize);
        printf("stdsort\t");benchmarkSort(std::sort, sample, sampleSize);
        printf("quick\t");  benchmarkSort(quick, sample, sampleSize);
        printf("threads\t");benchmarkSort(parallel, sample, sampleSize);
        delete[] sample;
    }

    // 쓰레드 병렬 단독테스트
    if (test[3]) {
        printf("\n--- Parallel Sort ---\n");
        printf("threads\t");        benchmarkSort(parallel, nullptr, 4000000000);
    }

    return 0;
}


// 함수 구현(정의)

//! DO NOT FORGET FREE MEMORY
int* getRandomIntArr(const unsigned size, const int max) {
    // 무작위 정수 배열 리턴. 반드시 사용후 할당해제.
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

void isSortedCorrect(sortFunction sort, const unsigned sampleSize, const bool printArr) {
    // 오름차순인지 검사, 복사생성 후 정렬검증(std::sort 비교)

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
    printf("sort: %s\n", isSorted?"SUCCESS":"[FAIL] \nsort correct :");   
    if ((!isSorted) && printArr)    { printf("\t");   printIntArr(cp, cp + sampleSize); }

    delete[] sample;
    delete[] cp;
}

void benchmarkSort(sortFunction sort, const int* sample, const unsigned sampleSize) {
    // sample을 정렬하는데 걸리는 시간 측정하여 출력. 기본값은 샘플 복사.
    printf("\tbenchmark (sample size %zu) :\t", sampleSize);

    bool isInstanceSample =         false;
    if (sample == nullptr)          isInstanceSample = true;
    int* cp = isInstanceSample?     getRandomIntArr(sampleSize) : new int[sampleSize];
    if (!isInstanceSample)          memcpy(cp, sample, INT_SIZE * sampleSize); 
    
    // 정렬시간 측정
    auto start_time = std::chrono::high_resolution_clock::now();

    sort(cp, cp + sampleSize);  // 정렬

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end_time - start_time;
    
    // 결과 출력과 메모리 해제
    printf("%.8f s.\n", diff.count());
    delete[] cp;
}

void findOptimalThreshold(sortFunction sort, int* thresholdVar, int sampleCount) {
    // 삽입정렬 전환 임계 찾기
    int candidates[] = {4,8,16,32,48,64,96,128,192,256,320,384,512,768,1024,2048,4096};
    int candCount = sizeof(candidates)/sizeof(candidates[0]);
    unsigned sampleSize = 100000000;
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


void bubble(int* start, int* end) {
    // 우측부터 확정정렬. 뽑은요소와 다음요소간 비교연산하며 연속 스왑.
    for (int* p = start; p < end - 1; p++) {
        bool swapped = false;               // 개선 트리거. 한번이라도 swapped 되지 않는 루프가 있다면 실행 종료
        for (int* q = start; q < end - 1 - (p - start); q++)
            if (*q > *(q + 1)) {
                swap(q, q + 1);
                swapped = true;
            }
        if (!swapped) break;
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
    // p 기준 좌측 후 p값 저장. p값을 기준으로 분할된 좌측배열에서만 검사후 적정위치 나올때까지 요소 밀어낸 후 삽입. 어느시점이든 정렬 확정 안됨.
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
    // insert단점으로 특정 요소가 잦은 밀어내기(한칸씩) 발생을 해소하기 위해 gap 만큼 크게 이동하며, gap은 특정 조건에 따라 감소하는게 보통.
    // 단, 마지막에 insert정렬(gap = 1). insert는 정렬이 거의 완성될수록 훨씬 빨라지므로, 지장없음
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
    if (sz <= QUICK_MIN_SIZE)       { insert(start, end);       return; }

    // 분할
    int* lPtr =         start;
    int* rPtr =         end - 1;       //  보정: end는 마지막요소가 아님.마지막 요소 다음을 가리킴.
    const int pivot =   *(start + ((sz) / 2));  // 피봇 선택은 랜덤/정규분포 등을 이용해봤으나, 센터값이 가장 빠르고 균등함.

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


void _merge(int* start, int* end, int* bf) {
    // 싱글버퍼합병: 버퍼공간 할당 1회, 대신 memcpy가 매 루프 실행됨(해결하려면 코드 복잡성 증가). 여러환경 검증결과 cpu 혹은 메모리가 좋지않을수록 속도 등에 이득

    // 기저
    if (start >= end) return;
    const int sz = end - start;
    if (sz <= 1) return;
    if (sz <= MERGE_MIN_SIZE) {
        insert(start, end);
        return;
    }        

    // 분할기준
    const int lSize =  sz / 2;

    // 정복: 재귀호출된 후에는 start가 아래 병합에서 aPtr로 bf를 새로쓰고, memcpy를 통해 start로 덮어씌워지므로, start로 호출하는 것에 의문을 가지거나 걱정하지 않아도 된다.
    _merge(start, start + lSize, bf);
    _merge(start + lSize, start + sz, bf);

    // 병합: 고쳐진 start를 기준으로 bf에 좌우 비교 채워넣기로 다시 작성.
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

    // 갱신: bf를 start로 덮어씌움 (매번 할당하진 않지만 그래도 매 루프 오버헤드 발생 -> 해결하려면 코드 복잡성 급증)
    memcpy(start, bf, INT_SIZE * sz);
}

void merge(int* start, int* end) {
    // 래퍼함수: 하나의 코드로 bf를 매번 할당하면 오버헤드 증가하므로, 래퍼에서 한번만 할당. 정말 낙서장처럼 쓰는 메모리공간.
    const int sz = end - start;
    int* bf = new int[sz];
    _merge(start, end, bf);
    delete[] bf;
}



/*
    shell정렬 버전으로 사용했을 때:
        1억개: 1.1초, 10억개: 17초, 25억개: 54초, 50억개(현재 벤치마크 자료구조에선 사용불가): 117초
    quick전환 후:
        1억개: 0.53초, 10억개: 5.07초, 25억개: 12.35초, 50억개(현재 벤치마크 자료구조에선 사용불가): 25.00초
*/

// 쓰레드를 나누어 sortFunc로 병렬처리
void parallel(int* start, int* end) {
    sortFunction sort = quick;     // 정렬방법. 변경가능
    size_t size = end - start;

    unsigned num_threads = std::thread::hardware_concurrency();

    if (size <= 1 || num_threads == 1) {    // 싱글로 진행할 예외처리
        sort(start, end);
        return;
    }

    std::vector<std::thread> threads;
    size_t chunk = (size + num_threads - 1) / num_threads;     // 전체사이즈에서 쓰레드 나눈만큼 작업분배
    auto worker = [sort](int* start, int* end) { sort(start, end); };

    for (unsigned t = 0; t < num_threads; ++t) {
        int* th_start = start + t * chunk;
        int* th_end = (t == num_threads - 1) ? end : th_start + chunk;
        threads.emplace_back(worker, th_start, th_end);
    }
    for (auto& th : threads) th.join();

    // 병합과정. inplace_merge를 싱글버퍼(merge에서 사용한 방법)로 개선하면 더 빨라지지만 메모리 오버헤드 증가. 
    size_t offset = chunk;
    while (offset < size) {
        size_t left = 0;
        while (left + offset < size) {
            size_t mid = left + offset;
            size_t right = std::min(left + 2 * offset, size);
            std::inplace_merge(start + left, start + mid, start + right);
            left += 2 * offset;
        }
        offset *= 2;
    }
}


