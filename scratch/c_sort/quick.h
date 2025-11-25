#ifndef SORT_QUICK_H
#define SORT_QUICK_H
#define QUICK_INSERT_CONVERT_THRESHOLD 384

#include "insert.h"

void quick(int* begin, int* end) {
    const int size =    end - begin;
    if (size <= 0)      return;
    if (size < QUICK_INSERT_CONVERT_THRESHOLD) { insert(begin, end); return; }

    int* lp =           begin;
    int* rp =           end - 1;
    const int pivot =   *(begin + (size / 2));

    do {
        while (*lp < pivot)     ++lp;
        while (*rp > pivot)     --rp;
        if (lp <= rp) {
            int tmp = *lp;
            *lp = *rp;
            *rp = tmp;
            ++lp;
            --rp;
        }
    } while(lp <= rp);

    if (rp > begin)     quick(begin, rp + 1);
    if (lp < end - 1)   quick(lp, end);

}

#endif