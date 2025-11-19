#include <iostream>
#include <time.h>
#include <algorithm>            // 일부환경에서는 다음 두 헤더가 선언되어야함 (std::is_sorted, memcpy)
#include <string.h>
#define QUICK_MIN_SIZE 256      // insertion sort로 전환될 배열크기 임계값 상수
#define MERGE_MIN_SIZE 64


/* DESC:
    compile:    -O3 혹은 -Ofast(비권장)로 사용하면, register 키워드 명시 없이도 필요에 따라 최적화됨
    data type:  모든 정렬은 정수형 데이터만 사용하며, 오름차순 정렬됨
                배열의 자료형은 정수형 배열을 사용함
    return:     정렬함수는 새로운 배열을 리턴하지 않고, 원본배열을 수정함
    parameter:  정렬 파라미터는 두가지 모두 포인터를 사용하며, 반복자처럼 start는 배열의 시작을, end는 배열의 마지막 요소 다음을 가리킴
    sort:       quick, merge는 임계값(배열길이 256 혹은 64 이하) 도달시 insert정렬로 전환된다. 따라서 정렬신뢰검사에는 샘플크기를 키워야함
    추가서술:   c와의 범용성 확대를 위해 일부 cpp 구현을 컨버팅을 하면 거의 모든 기능을 c에서도 그대로 쓸 수 있음
        
    code structure:
        HEADER
        descripion comment
        definition(PROTOTYPES)
        MAIN
        declaration
    
    functions:
        Helper: 무작위샘플배열생성, swap, 출력, 배열복사기능
        Test: 출력테스트, 시간측정테스트
        Sort: 버블, 선택, 삽입, 쉘, 퀵, 합병정렬

    TODOLIST: 
        힙정렬 구현
*/


// PROTOTYPES

// Helper
int* getRandomIntArr(int size, int max = 10000);        //! DO NOT FORGET FREE MEMORY   random integer array return.
void printIntArr(int* start, int* end);                 // print array use pointer
inline void swap(int* x, int* y);                       // swap integer data. 인라인 선언

// Test
void isSortedCorrect(void (*sort)(int*, int*), int sampleSize = 13);        // 정렬신뢰성 검사. 샘플 크기 "30" 이하 시 정렬 전, 후 출력. 정렬실패시 정확한 배열출력도 이 기준을 따름.
void benchmarkSort  (void (*sort)(int*, int*), int sampleSize = 1000000);   // 정렬시간측정

// Sort
void bubble (int* start, int* end);
void select (int* start, int* end);
void insert (int* start, int* end);
void shell  (int* start, int* end);
void quick  (int* start, int* end);
void merge  (int* start, int* end);

// test codes




// MAIN 
int main() {
    srand(time(NULL));

    // 테스트 실행 트리거: 정렬검증, 일반 시간측정, 고성능 시간측정
    bool test[] = {
        true, false, true
    };
    
    // 정렬검증
    if (test[0]) {
        isSortedCorrect(bubble);
        isSortedCorrect(select);
        isSortedCorrect(insert);
        isSortedCorrect(shell, 100000);
        isSortedCorrect(quick, 100000);
        isSortedCorrect(merge, 100000);
    }

    // 일반 시간측정
    if (test[1]) {
        benchmarkSort(shell);
        benchmarkSort(quick);
        benchmarkSort(merge);
    }

    // 고성능 시간측정
    if (test[2]) {
        benchmarkSort(merge, 100000000);
        benchmarkSort(quick, 100000000);
    }

    return 0;
}


// 함수 구현(정의)

//! DO NOT FORGET FREE MEMORY
int* getRandomIntArr(int size, int max) {
    int* res =                              new int[size];
    for (int i = 0; i < size; ++i)          res[i] = rand() % max + 1;
    return res;
}

void printIntArr(int* start, int* end) {
    printf("[");
    if (start < end)                        printf("%d", *start);
    else                                    { printf("]\n");    return; }
    for (int* p = start + 1; p < end; ++p)  printf(", %d", *p);
    printf("]\n");
}

void swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void isSortedCorrect(void (*sort)(int*, int*), int sampleSize) {
    // 오름차순인지 검사, 복사생성 후 정렬검증(std::sort 비교)
    const bool printArr =                 sampleSize <= 30;             // 배열출력 조건선언(30이하 길이만 출력)
    printf("\nsort test(sample:%d) :\n", sampleSize);                   // 함수 진입 출력

    int* sample =                   getRandomIntArr(sampleSize, 50);    // 샘플 생성
    int* cp =                       new int[sampleSize];                // 샘플 복사할당
    memcpy(cp, sample, sampleSize * sizeof(int));

    if (printArr)                   {printf("\t");    printIntArr(sample, sample + sampleSize);}
    
    sort(sample, sample + sampleSize);                                  // 정렬
    std::sort(cp, cp + sampleSize);                                     // 복사샘플 정렬(비교용)

    bool isSorted =                   true;                             // 정렬검증 성공여부
    for (int i = 0; i < sampleSize; ++i) {
        if (sample[i] != cp[i]) {
            isSorted = false;
            break;
        }
    }

    // 결과 출력과 메모리 해제
    if (printArr)                   { printf("\t");   printIntArr(sample, sample + sampleSize); }
    printf("\tsort: %s\n", isSorted?"OK":"[WARING] Fail. \nsort correct :");   
    if ((!isSorted) && printArr)    { printf("\t");   printIntArr(cp, cp + sampleSize); }

    delete[] sample;
    delete[] cp;
}

void benchmarkSort(void (*sort)(int*, int*), int sampleSize) {
    printf("\nbenchmark (sample size %d) :\n", sampleSize);             // 함수 진입 출력
    
    int*    sample =                getRandomIntArr(sampleSize);        // 샘플생성
    clock_t timeStart =             clock();                            // 시간측정

    sort(sample, sample + sampleSize);                                  // 정렬

    double  timeResult =            (double)(clock() - timeStart) / CLOCKS_PER_SEC; // 시간결과 생성
    
    // 결과 출력과 메모리 해제
    printf("\ttime: %.6fs.\n", timeResult);
    delete[] sample;
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
        int bf = *p;
        int* q = p;

        for (; q > start && bf < *(q - 1); q--)
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
    
    // 분할기저조건: 분할중 배열 길이 임계값 도달시 삽입정렬로 전환
    if (end - start <= QUICK_MIN_SIZE) {
        insert(start, end);
        return;
    }    

    // 분할
    int* left =     start;
    int* right =    end - 1;       //  보정: end는 마지막요소가 아님.마지막 요소 다음을 가리킴.
    int pivot =     *(start + ((end - start) / 2));
    int tmp;

    // 분할정렬: pivot 기준으로 작은쪽은 left로, 큰쪽은 right로 스왑. 조건: 교차직후 종료
    while (left <= right) {
        while (pivot > *left)       left++;
        while (pivot < *right)      right--;
        if (left <= right) {
            swap(left, right);
            left++;
            right--;
        }
    }

    // 정복 조건: 재귀호출될 right와 left 가 원본 배열의 범위를 벗어나지 않고, 최소 1개라도 요소를 갖고있음.
    if (right > start)      quick(start, right + 1);    // 보정: 재귀호출시 처음에 right는 -1로 초기화됨
    if (left < end - 1)     quick(left, end);           // 보정: 조건식 end는 -1 하지 않아도 작동은 정상.
}

void merge(int* start, int* end) {
    // memcpy가 재귀적으로 실행되는 상태라 메모리할당이 클 수 있음.(속도는 빠름)
    // 센터기준 좌우로 나눴다가 다시 합치되, 합칠 땐 좌우 비교후 작은것 부터 채워넣음.

    // 기저
    if (start >= end) return;
    int sz = end - start;
    if (sz <= 1) return;

    // 배열 길이 임계값 도달시 삽입정렬전환
    if (sz <= MERGE_MIN_SIZE) {
        insert(start, end);
        return;
    }        

    // 분할
    int leftSize =  sz / 2;
    int rightSize = sz - leftSize;
    int* leftArr = new int[leftSize];
    int* rightArr = new int[rightSize];
    memcpy(leftArr, start, sizeof(int) * leftSize);
    memcpy(rightArr, start + leftSize, sizeof(int) * rightSize);

    // 정복
    merge(leftArr, leftArr + leftSize);
    merge(rightArr, rightArr + rightSize);

    // 병합(좌우측 하나씩 비교후 최소부터 원본에 채워넣는 정렬하면서)
    int* lPtr = leftArr;
    int* rPtr = rightArr;
    int* aPtr = start;
    
    while (lPtr < leftArr + leftSize && rPtr < rightArr + rightSize) {
        if(*lPtr < *rPtr)       *(aPtr++) = *(lPtr++);
        else                    *(aPtr++) = *(rPtr++);
    }

    while (lPtr < leftArr + leftSize)       *(aPtr++) = *(lPtr++);
    while (rPtr < rightArr + rightSize)     *(aPtr++) = *(rPtr++);

    // 해제
    delete[] leftArr;
    delete[] rightArr;
}

