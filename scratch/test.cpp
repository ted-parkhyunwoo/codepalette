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

void sortArr(int* begin, int* end) {

}



int main() {
    initRandomSeed();
    int sz = 10, max = 100;

    int* arr = getRandIntegerArray(sz, max);
    printArr(arr, arr + sz);
    freeArray(arr);

    return 0;
}