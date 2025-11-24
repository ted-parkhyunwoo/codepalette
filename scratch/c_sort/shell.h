#ifndef SORT_SHELL_H
#define SORT_SHELL_H

void shell(int* begin, int* end) {
    unsigned gap = 1;
    while (gap < (end - begin) / 3) gap = gap * 3 + 1;

    for (; gap > 0; gap /= 3) {
        for (int* p = begin + gap; p < end; ++p) {
            const int bf = *p;
            int* q = p;
            for (; q - begin >= gap && bf < *(q - gap); q -= gap)
                *q = *(q - gap);
            if (q != p)
                *q = bf;
        }
    }
}

#endif