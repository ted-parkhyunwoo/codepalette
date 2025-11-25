#ifndef C_SORT_MERGE_H
#define C_SORT_MERGE_H
#define MERGE_INSERT_CONVERT_THRESHOLD 64

#include <stdlib.h>
#include <string.h>     // memcpy 때문에 필요함. helper.h에서 선언되어 있음
#include "insert.h"

void _merge(int* begin, int* end, int* bf) {
    if (begin >= end)       return;
    const unsigned size =   end - begin;
    if (size <= 1)          return;
    if (size <= MERGE_INSERT_CONVERT_THRESHOLD)   { insert(begin, end); return; }

    int* lBegin =   begin;
    int* rBegin =   lBegin + (size / 2);
    int* lEnd =     rBegin;
    int* rEnd =     end;

    _merge(lBegin, lEnd, bf);
    _merge(rBegin, rEnd, bf);

    int* bfBegin = bf;
    do {
        if (*lBegin <= *rBegin)     *(bfBegin++) = *(lBegin++);
        else                        *(bfBegin++) = *(rBegin++);
    } while(lBegin < lEnd && rBegin < rEnd);

    while (lBegin < lEnd)           *(bfBegin++) = *(lBegin++);
    while (rBegin < rEnd)           *(bfBegin++) = *(rBegin++);

    memcpy(begin, bf, sizeof(int) * (bfBegin - bf));
}

void merge(int* begin, int* end) {
    if (begin >= end) return;
    int* bf = (int*)malloc(sizeof(int) * (unsigned)(end - begin));
    _merge(begin, end, bf);
    free(bf);
}

#endif