#ifndef SORT_INSERT_H
#define SORT_INSERT_H

void insert(int* begin, int* end) {
    for (int* p = begin + 1; p < end; ++p) {
        const int bf = *p;
        int* q = p;
        for (; q > begin && *(q - 1) > bf; --q)
            *q = *(q - 1);
        if (q != p)
            *q = bf;
    }
}

#endif