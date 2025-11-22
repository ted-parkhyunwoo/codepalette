// qsort.c

int QUICK_MIN_SIZE = 384;                   // insertion sort로 전환될 배열크기 임계값 상수

inline void swap(int* x, int* y) {
    const int tmp = *x;
    *x = *y;
    *y = tmp;
}

void insert(int* start, int* end) {
    // p 기준 좌측 후 p값 저장. p값을 기준으로 분할된 좌측배열에서만 검사후 적정위치 나올때까지 요소 밀어낸 후 삽입. 어느시점이든 정렬 확정 안됨.
    for (int* p = start + 1; p < end; p++) {
        const int bf = *p;
        int* q = p;

        for (; q > start && bf < *(q - 1); --q)
            *q = *(q - 1);

        if (q != p)
            *q = bf;
    }
}


void quick(int* start, int* end) {          // end 혹은 right, 재귀호출과 조건검사에 -1 등의 보정이 들어감.
    // pivot기준 좌측과 우측을 분할하여 좌측은 작은쪽, 우측은 큰쪽으로 스왑하고 좌 우측 따로 재귀실행 (더이상 분할할 수 없을 때 까지)

    const int sz =      end - start;
    if (sz <= 1)        return;
    if (sz <= QUICK_MIN_SIZE)       { insert(start, end);       return; }

    // 분할
    int* lPtr =         start;
    int* rPtr =         end - 1;       //  보정: end는 마지막요소가 아님.마지막 요소 다음을 가리킴.
    const int pivot =   *(start + ((sz) / 2));

    // 분할정렬: pivot 기준으로 작은쪽은 left로, 큰쪽은 right로 스왑. 조건: 교차직후 종료
    while (lPtr <= rPtr) {
        while (pivot > *lPtr)       ++lPtr;
        while (pivot < *rPtr)       --rPtr;
        if (lPtr <= rPtr) {
            swap(lPtr, rPtr);
            ++lPtr;
            --rPtr;
        }
    }

    // 정복 조건: 재귀호출될 right와 left 가 원본 배열의 범위를 벗어나지 않고, 최소 1개라도 요소를 갖고있음.
    if (rPtr > start)       quick(start, rPtr + 1);     // 보정: sz산출 정상화 및 재귀호출시 분할에서 rPtr이 end - 1로 초기화되므로.
    if (lPtr < end - 1)     quick(lPtr, end);           // 보정: 조건식 end는 -1 하지 않아도 작동은 정상.
}