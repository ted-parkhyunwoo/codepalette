#include <iostream>
#include <unistd.h>
#include <ctime>
#include <cstdlib>

static int initSeed = 0;

void initRandomSeed() {
    if (!initSeed) {
        srand(time(NULL) ^ getpid());
        initSeed = 1;
    } 
}

int getRandInt(int max) {
    return rand() % max + 1;
}

int* getRandIntegerArray(int size, int maxInt) {
    int* res = new int[size];
    for (int i = 0; i < size; ++i)
        *(res + i) = getRandInt(maxInt);
    return res;
}

void freeArray(int* arr) {
    delete[] arr;
}

void printArr(int* begin, int* end) {
    int size = end - begin;
    if (size < 1) std::cout << "[";
    else if (size >= 1)  std::cout << "[" << *begin;
    
    for (int* p = begin + 1; p < end; ++p) 
        std::cout << ", " << *p;

    std::cout << "]\n";
}

inline void swapPtr(int* p, int* q) {
    int bf = *p;
    *p = *q;
    *q = bf;
}

inline bool validSort(int* begin, int* end) {
    // nullptr check.
    if (begin == nullptr) return false;
    // range check. (사실상 아래 Size check가 이 기능까지 다 하는중이므로 굳이 따지자면 필요는 없음. 가장 크리티컬 한 순서로 배치했을 뿐)
    if (end <= begin) return false;
    // size check.
    if (end - begin <= 1) return false;
    
    return true;
}

void bubble(int* begin, int* end) {
    // 개념: begin, begin + 1 값비교 스왑. 좌측부터 선택하여 다음카드와 비교후 뒤바꿈. 이것을 연속적으로 진행하여 우측부터 확정정렬
    // 첫번째 반복문에서의 기저조건은 begin + 1을 비교하기 위해 end - 1 보다 작을때 까지만 진행
    // 두번째 반복문에서의 기저조건은 우측부터 정렬확정이라 하나씩 줄어들도록 함
    if (!validSort(begin, end)) return;

    for (int* p = begin; p < end - 1; ++p) {
        bool swapped = false;
        for (int* q = begin; q < end - 1 - (p - begin); ++q) 
            if (*q > *(q + 1)) {
                swapPtr(q, q + 1);
                swapped = true;
            }
        // 최적화: 버블에서 swap이 한번도 안일어났다면 이미 정렬됐다는 뜻이므로 루프종료 
        if (!swapped)   break;
    }
}

void select(int* begin, int* end) {
    // 개념: 배열 처음부터 끝까지 좌측부터 탐색하여 최소값을 찾아 좌측부터 확정. 제일 작은것을 뽑아 좌측부터 순서대로 놓는다 생각하면 됨.
    // 첫번째 반복문은 전체 반복. p는 비교대상 bf를 타게팅하기도 하고, 탐색시작점을 q로(정확히는 p+1부터 탐색) 설정하기도 함. (bf선택과 q범위 설정용이란 뜻)
    // 두번째 반복문은 q부터 end까지 탐색함. (좌측부터 확정정렬이기 때문)
    if (!validSort(begin, end)) return;

    for (int* p = begin; p < end; ++p) {
        int* bf = p;    // minimum으로 확정시킬 버퍼
        for (int* q = p + 1; q < end; ++q) 
            if (*bf > *q)
                bf = q;        

        // bf 변동사항 생기면(최소값이 갱신되었다면) 스왑
        if (bf != p)    swapPtr(bf, p);
    }
}

void insert(int* begin, int* end) {
    // 개념: begin + 1 기준 좌측배열로 만들고 그 배열에서 밀어내기 작업으로 정렬. 하나씩 뽑아(bf) 적절한 위치로 밀어내기(q = q - 1) 후 삽입(*q = bf). p 기준 좌측배열이 정렬확정은 안됨, 하지만 어느시점에서든 오름차순만큼은 보장.
    // 첫번째 반복문은 p 기준 좌측배열 구분을 위해 쓰이기도 하고, bf를 저장하기 위해 쓰이기도 함. 최소 좌측배열 요소 하나는 필요하므로 begin + 1로 지정
    // 두번째 반복문은 좌측배열의 끝부터 탐색 후, 위에서 임시 저장된 bf가 비집고 들어갈 위치가 확정되기 전까지 begin쪽으로 향해 하나씩 밀어내는 역할을 함.

    if (!validSort(begin, end)) return;

    for (int* p = begin + 1; p < end; ++p) {
        // 임시저장
        const int bf = *p;
        // 임시저장한 값을 begin ~ p 에서 적절한 위치 삽입하기 위해 지정
        int* q = p;

        // 기저조건 두가지: begin에 도달하기 직전까지만(q - 1을 염두), 임시저장 값이 이미 최소값일경우 
        // 그때까지 p기준 좌측배열에서 bf를 집어넣기 위해 한칸씩 우측으로 밀어냄
        for (; q > begin && bf < *(q - 1); --q)
            *q = *(q - 1);
        
        // q가 변동되었다는 것은 q반복문에서 밀어내기 발생했다는 뜻이므로 bf로 대체
        if (q != p) *q = bf;
    }
}

void sortArr(int* begin, int* end) {

}



int main() {
    initRandomSeed();
    int sz = 10, max = 100;

    int* arr = getRandIntegerArray(sz, max);

    int* begin = arr;
    int* end = begin + sz;

    printArr(begin, end);
    insert(begin, end);
    printArr(begin, end);


    freeArray(arr);

    return 0;
}