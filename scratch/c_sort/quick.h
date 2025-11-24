#ifndef SORT_QUICK_H
#define SORT_QUICK_H
#include "insert.h"

void quick(int* begin, int* end) {
    const int size = end - begin;
    if (size <= 0) return;
    if (size < 384) {
        insert(begin, end);
        return;
    }

    int* lp = begin;
    int* rp = end - 1;
    const int pivot = *(begin + (size / 2));

    while (lp <= rp) {
        while (*lp < pivot) ++lp;
        while (*rp > pivot) --rp;
        if (lp <= rp) {
            int tmp = *lp;
            *lp = *rp;
            *rp = tmp;
            ++lp;
            --rp;
        }
    }

    if (rp > begin)     quick(begin, rp + 1);
    if (lp < end - 1)       quick(lp, end);

}

#endif