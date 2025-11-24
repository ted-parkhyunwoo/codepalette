#ifndef BUBBLE_H
#define BUBBLE_H

void bubble(int* begin, int* end) {
    if (begin >= end) return;
    for (int* ptr = begin; ptr < end - 1; ++ptr) {
        int swapped = 0;
        for (int* bf = begin; bf < end - 1 - (ptr - begin); ++bf) {
            if (*bf > *(bf + 1)) {
                const int tmp = *bf;
                *bf = *(bf + 1);
                *(bf + 1) = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

#endif