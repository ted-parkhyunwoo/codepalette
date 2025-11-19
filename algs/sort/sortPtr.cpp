#include <iostream>
#include <time.h>

// TODO: 보기 쉽게 함수 선언 구현 따로배치
// TODO: 테스트케이스를 다른 파일과 똑같도록 기본값 정렬
// TODO: 함수 내 줄바꿈 재정렬

void initRandomSeed() { srand(time(NULL)); }


// 동적배열 선언되므로, 사용시 반드시 메모리 해제
int* getRandomIntArr(int size, int max = 10000) {
    int* res = new int[size];
    for (int i = 0; i < size; ++i)
        res[i] = rand() % max + 1;
    return res;
}

void printIntArr(int* start, int* end) {
    std::cout << '[';
    if (start < end) std::cout << *start;
    else { 
        std::cout << ']' << std::endl;
        return;
    }
    for (int* p = start + 1; p < end; ++p) {
        std::cout << ", " << *p;
    }
    std::cout << "]\n";
}

// DO NOT FORGET FREE MEMORY cause leak.
int* cpArr(int* start, int* end) {
    int sz = end - start;
    int* res = new int[sz];
    memcpy(res, start, sz * sizeof(int));   
    return res;
}

inline void swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void bubble(int* start, int* end) {
    for (int* p = start; p < end - 1; p++) {
        for (int* q = start; q < end - 1 - (p - start); q++) {
            if (*q > *(q + 1))  swap(q, q + 1);
        } 
    }
}

void select(int* start, int* end) {
    for (int* p = start; p < end; p++) {
        int* bf = p;
        for (int* q = p; q < end; q++)     if (*bf > *q) bf = q;
        if (bf != p)    swap(bf, p);
    }
}

void insert(int* start, int* end) {
    for (int* p = start + 1; p < end; p++) {
        int bf = *p;
        int* q = p;
        for (; q > start && bf < *(q - 1); q--)     *q = *(q - 1);
        if (q != p) *q = bf;
    }
}

void shell(int* start, int* end) {
    int gap = 1;
    while (gap < (end - start) / 3)  gap = gap * 3 + 1;

    while (gap > 0) {
        for (int* p = start + gap; p < end; p++) {
            int bf = *p;
            int* q = p;
            for (; q - start >= gap && bf < *(q - gap); q -= gap)   *q = *(q - gap);
            if (q != p) *q = bf;
        }
        gap /= 3;
    }
}

// end 혹은 right, 재귀호출과 조건검사에 -1 등의 보정이 들어감
void quick(int* start, int* end) {
    int* left = start;
    int* right = end - 1;       //  보정: end는 마지막요소가 아님.마지막 요소 다음을 가리킴.
    int pivot = *(start + ((end - start) / 2));
    
    while (left <= right) {
        while (pivot > *left)  left++;
        while (pivot < *right) right--;
        if (left <= right) {
            int tmp = *left;        // 내장 스왑이 압도적으로 빠름
            *left = *right;
            *right = tmp;
            left++;
            right--;
        }
    }
    if (right > start)  quick(start, right + 1);        // 보정: 재귀호출시 처음에 right는 -1로 초기화됨
    if (left < end - 1)     quick(left, end);           // 보정: 조건식 end는 -1 하지 않아도 작동은 정상.
}


void merge(int* start, int* end) {
    if (start >= end) return;
    int sz = end - start;
    if (sz <= 1) return;
    int leftSize = sz / 2;
    int rightSize = sz - leftSize;

    int* leftArr = cpArr(start, start + leftSize);
    int* rightArr = cpArr(start + leftSize, end);

    merge(leftArr, leftArr + leftSize);
    merge(rightArr, rightArr + rightSize);

    int* lPtr = leftArr;
    int* rPtr = rightArr;
    int* aPtr = start;
    
    while (lPtr < leftArr + leftSize && rPtr < rightArr + rightSize) {
        if(*lPtr < *rPtr)       *(aPtr++) = *(lPtr++);
        else                    *(aPtr++) = *(rPtr++);
    }

    while (lPtr < leftArr + leftSize)       *(aPtr++) = *(lPtr++);
    while (rPtr < rightArr + rightSize)     *(aPtr++) = *(rPtr++);
    delete leftArr;
    delete rightArr;
    
}


void benchmarkSort(void (*sort)(int*, int*), int sampleSize = 1000000) {
    printf("\nbenchmark (sample size %d) :\n", sampleSize);
    int* sample = getRandomIntArr(sampleSize);
    clock_t timeCheck = clock();
    sort(sample, sample + sampleSize);
    double timeResult = (double)(clock() - timeCheck) / CLOCKS_PER_SEC;
    bool isSorted = std::is_sorted(sample, sample + sampleSize);
    printf("\tsort: %s\n\ttime: %.6fs.\n", isSorted?"OK":"Fail", timeResult);   
    delete sample;
}

void simpleTestSort(void (*sort)(int*, int*), int sampleSize = 5) {
    printf("\nsimple test(sample:%d) :\n", sampleSize);
    int* sample =  getRandomIntArr(sampleSize, 50);
    printf("\t");   printIntArr(sample, sample + sampleSize);
    sort(sample, sample + sampleSize);
    printf("\t");   printIntArr(sample, sample + sampleSize);
    bool isSorted = std::is_sorted(sample, sample + sampleSize);
    printf("\tsort: %s\n", isSorted?"OK":"Fail");   
    delete sample;
}

int main() {
    initRandomSeed();
    
    simpleTestSort(merge);
    simpleTestSort(quick);
    benchmarkSort(merge);
    benchmarkSort(quick);

    return 0;
}
