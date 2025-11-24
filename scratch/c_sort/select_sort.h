#ifndef SELECT_SORT_H
#define SELECT_SORT_H

void select_sort(int* begin, int* end) {
    if (begin >= end) return;
    for (int* p = begin; p < end; ++p) {
        int* bf = p;
        for (int* q = p; q < end; ++q) {
            if (*q < *bf)
                bf = q;
        }
        if (bf != p) {
            int tmp = *p;
            *p = *bf;
            *bf = tmp;
        }
    }
}

#endif