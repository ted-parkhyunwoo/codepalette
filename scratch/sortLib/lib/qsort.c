// qsort.c


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
