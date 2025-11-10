#include <stdio.h>

// algs/sort.cpp 를 복습겸 c로 구현. 정수형 배열이며, 전통적 배열을 사용.

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void printArr(int* arr, unsigned size) {
    printf("{%d", arr[0]);
    for (unsigned i = 1; i < size; ++i) {
        printf(", %d", arr[i]);
    }
    printf("}\n");
}


// 최소값 찾기지만, 큰 값을 찾아 배열 오른쪽으로 밀어냄. (거품이 교차되듯이)
void bubble(int* arr, unsigned size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}

// 0번 인덱스부터 최소값을 찾고(선택), 있다면 0번과 스왑. 바뀐건 다음 루프에서 처리.
void select(int* arr, unsigned size) {
    for (int i = 0; i < size; ++i) {
        int minIdx = i;                 // 인덱스로 저장하며 업데이트 후 , 최소값의 인덱스를 찾아 i와 minIdx를 스왑
        for (int j = i; j < size; ++j) {
            if (arr[minIdx] > arr[j])       minIdx = j;
        }
        if (minIdx != i)        swap(arr + i, arr + minIdx);
    }
}

void insert(int* arr, unsigned size) {
    for (int i = 1; i < size; ++i) {    // 코드가 배열을 i기준으로 나누어 좌측, 우측배열을 비교하는 방식이므로, 1부터 시작.
        int buffer = arr[i];           // 현재 요소 저장 (index로 사용하지 않는 이유는 j를 다루는 배열에서 이곳의 idx로 밀어낼 수 있음.)
        int j = i;
        // i 기준으로 좌우 배열 슬라이스. 이후 좌측배열의 마지막요소부터 0까지 점검후 밀어내기. 넣을곳이 있다면 삽입하고 루프종료
        for (; j > 0 && arr[j - 1] > buffer; --j) 
            arr[j] = arr[j - 1];
        if (j != i) arr[j] = buffer;        // j(삽입할 위치)를 다루는 반복문이 j를 초기값i에서 더 작은 idx값으로 업데이트 했다면, 버퍼에 저장한 값으로 덮어씌움(삽입)
    }
}

// 쉘정렬은 insert의 확장개념. insert에서 int i = 1과 arr[j - 1]에 해당하는 부분이 gap(step)으로 관리되며 크기는 아무렇게나 줄여도 상관없으나, 마지막엔 항상 1을 실행해야함.
void shell(int* arr, unsigned size) {
    int step = size / 2;
    while (step > 0) { 
        for (int i = step; i < size; ++i) {
            int buffer = arr[i];
            int j = i;
            for (; j >= step && arr[j - step] > buffer; j -= step) 
                arr[j] = arr[j - step];
            if (j != i) { arr[j] = buffer;}
        }
        step /= 2;
    }
}


int main() {
    int arr[10] = { 2, 3, 7, 1, 9, 6, 0, 5, 4, 8 };
    printArr(arr, 10);
    shell(arr, 10);
    printArr(arr, 10);

    return 0;
}