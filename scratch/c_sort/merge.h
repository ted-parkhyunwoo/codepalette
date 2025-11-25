#ifndef C_SORT_MERGE_H
#define C_SORT_MERGE_H
#include <stdlib.h>
// #include <string.h>     // memcpy에 필요할 수 있음
#include "insert.h"

void _merge(int* begin, int* end, int* bf) {
    if (begin >= end)       return;
    const unsigned size =   end - begin;
    if (size <= 1)          return;
    if (size <= 64)         { insert(begin, end); return; }

    int* lBegin =       begin;
    int* rBegin =       lBegin + (size / 2);
    const int* lEnd =   rBegin;
    const int* rEnd =   end;

    _merge(lBegin, lEnd, bf);
    _merge(rBegin, rEnd, bf);

    int* bfBegin = bf;
    while (lBegin < lEnd && rBegin < rEnd) {
        if (*lBegin <= *rBegin)     *(bfBegin++) = *(lBegin++);
        else                *(bfBegin++) = *(rBegin++);
    }

    while (lBegin < lEnd)   *(bfBegin++) = *(lBegin++);
    while (rBegin < rEnd)   *(bfBegin++) = *(rBegin++);

    memcpy(begin, bf, sizeof(int) * (bfBegin - bf));
}

void merge(int* begin, int* end) {
    if (begin >= end) return;
    int* bf = (int*)malloc(sizeof(int) * (unsigned)(end - begin));
    _merge(begin, end, bf);
    free(bf);
}

#endif