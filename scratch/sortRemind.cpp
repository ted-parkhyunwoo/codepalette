#include <iostream>
#include <unistd.h>
#include <ctime>
#include <cstdlib>

static int initSeed = 0;

void initRandomSeed() {
    if (!initSeed) {
        srand(time(NULL) ^ getpid());
        initSeed = 1;
    } 
}

int getRandInt(int max) {
    return rand() % max + 1;
}

int* getRandIntegerArray(int size, int maxInt) {
    int* res = new int[size];
    for (int i = 0; i < size; ++i)
        *(res + i) = getRandInt(maxInt);
    return res;
}

void freeArray(int* arr) {
    delete[] arr;
}

void printArr(int* begin, int* end) {
    int size = end - begin;
    if (size < 1) std::cout << "[";
    else if (size >= 1)  std::cout << "[" << *begin;
    
    for (int* p = begin + 1; p < end; ++p) 
        std::cout << ", " << *p;

    std::cout << "]\n";
}

void swapPtr(int* p, int* q) {
    int bf = *p;
    *p = *q;
    *q = bf;
}

void bubble(int* begin, int* end) {
    if (end - begin <= 1) return;
    for (int* p = begin; p < end - 1; ++p) {
        bool swapped = false;
        // p 반복문에 큰 의미는 없음. q반복문이 핵심이며, 현재와 다음의 값 비교후 스왑
        for (int* q = begin; q < end - 1 - (p - begin); ++q) 
            if (*q > *(q + 1)) {
                swapPtr(q, q + 1);
                swapped = true;
            }
        if (!swapped) break;
    }
}

void select(int* begin, int* end) {

}

void sortArr(int* begin, int* end) {

}



int main() {
    initRandomSeed();
    int sz = 10, max = 100;

    int* arr = getRandIntegerArray(sz, max);

    int* begin = arr;
    int* end = begin + sz;

    printArr(begin, end);
    bubble(begin, end);
    printArr(begin, end);


    freeArray(arr);

    return 0;
}