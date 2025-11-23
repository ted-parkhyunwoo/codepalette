#include <iostream>
#include <time.h>
#include <vector>

void makeRandArr(int* res, int size, int max = 100000) {
    for (int i = 0; i < size; ++i) 
        res[i] = rand() % max + 1;
}

void makeRandVec(std::vector<int>& v, int max = 100000) {
    for (int& e : v) {
        e = rand() % max + 1;
    }
}

void swap(int* x, int* y) {
    const int tmp = *x;
    *x = *y;
    *y = tmp;
}

void insert(int* start, int* end) {
    for (int* p = start + 1; p < end; p++) {
        const int bf = *p;
        int* q = p;
        for (; q > start && bf < *(q - 1); --q)
            *q = *(q - 1);
        if (q != p)
            *q = bf;
    }
}

void insert(std::vector<int>::iterator start, std::vector<int>::iterator end) {
    for (auto p = start + 1; p < end; p++) {
        const int bf = *p;
        auto q = p;
        for (; q > start && bf < *(q - 1); --q)
            *q = *(q - 1);
        if (q != p)
            *q = bf;
    }
}

void quick(int* start, int* end) {
    const int sz =      end - start;
    if (sz <= 1)        return;
    if (sz <= 384)       { insert(start, end);       return; }

    int* lPtr =         start;
    int* rPtr =         end - 1;
    const int pivot =   *(start + ((sz) / 2));

    while (lPtr <= rPtr) {
        while (pivot > *lPtr)       ++lPtr;
        while (pivot < *rPtr)       --rPtr;
        if (lPtr <= rPtr) {
            swap(lPtr, rPtr);
            ++lPtr;
            --rPtr;
        }
    }

    if (rPtr > start)       quick(start, rPtr + 1);
    if (lPtr < end - 1)     quick(lPtr, end);
}

void quick(std::vector<int>::iterator start, std::vector<int>::iterator end) {
    const int sz =      end - start;
    if (sz <= 1)        return;
    if (sz <= 384)       { insert(start, end);       return; }

    auto lPtr =         start;
    auto rPtr =         end - 1;
    const int pivot =   *(start + ((sz) / 2));

    while (lPtr <= rPtr) {
        while (pivot > *lPtr)       ++lPtr;
        while (pivot < *rPtr)       --rPtr;
        if (lPtr <= rPtr) {
            std::swap(*lPtr, *rPtr);
            ++lPtr;
            --rPtr;
        }
    }

    if (rPtr > start)       quick(start, rPtr + 1);
    if (lPtr < end - 1)     quick(lPtr, end);
}


int main() {

    int sz = 100000000;
    int* test2 = new int[sz];
    makeRandArr(test2, sz, 100000);
    clock_t sTime = clock();
    quick(test2, test2 + sz);
    printf("%.8f s\n", (double)(clock() - sTime) / CLOCKS_PER_SEC);
    delete[] test2;


    std::vector<int> vec(sz);
    makeRandVec(vec, 10000);
    sTime = clock();
    quick(vec.begin(), vec.end());
    printf("%.8f s\n", (double)(clock() - sTime) / CLOCKS_PER_SEC);

    return 0;
}

