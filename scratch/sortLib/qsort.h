// qsort.c

int QUICK_MIN_SIZE = 384;                   // insertion sort로 전환될 배열크기 임계값 상수

void swap(int* x, int* y);
void insert(int* start, int* end);
void quick(int* start, int* end);
