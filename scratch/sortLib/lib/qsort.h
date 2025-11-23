#ifndef QSORT_H
#define QSORT_H

/* 
    매개변수는 반복자의 사용과 동일
        start : 배열 자체를 pointing 하지만, *(array + 0) == array[0] 처럼 첫번째 요소를 가리킴
        end   : 배열의 끝을 포인팅(end 요소는 마지막 요소가 아님! end - 1이 마지막 요소임)
*/

void swap(int* x, int* y);              // swap이 필요할 수 있어서 삽입
void quick(int* start, int* end);       // 퀵정렬(일정 크기의 임계점 도달시 삽입정렬이 대체 실행됨)

#endif