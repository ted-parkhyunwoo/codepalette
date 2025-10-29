#include <stddef.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int factorial(int num) {
    int res = 1;
    for (int i = 1; i <= num; ++i) res *= i;
    return res;
}

// n 개중 r개 =  n! / (n - r)!
int oldPermute(int n, int r)  {
    if (n <= 0 || r <= 0) return -1;
    if (r > n) return 0;

    int left = factorial(n);
    int right = factorial(n - r);
    return left / right;
}

// 5P2라 칠때 5*4*3*2*1 / 3*2*1  = 5 * 4 로 줄여짐을 고려한 새로운 순열함수
//! 표준 자료형중에 제일 큰 정수형데이터. 20! 까지 연산가능 (2432902008176640000)
unsigned long long int permute(int n, int r) {
    unsigned long long int t = n - r;
    if (n <= 0 || n < r) return 0;
    if (t < 0) return -1;

    long res = 1;
    for (int i = n; i > t; i--) {
        res *= i;
    }
    return res;
}

//!-------------------------------이하  ai:gemini 작성--------------------------------

// 순열을 재귀적으로 생성하는 핵심 함수 (백트래킹)
int** generatePermuteArr_internal(
    int* base, int n, int r,
    int* tmp, int tmpIdx,
    int* visited,
    int** res, int* resIdx
) {
    // 1. 순열 완성 조건 (재귀 종료)
    if (tmpIdx == r) {
        // 현재 완성된 순열(tmp)을 결과 배열(res)에 복사
        // res[0] = {1, 2}, res[1] = {1, 3}, ...
        res[*resIdx] = (int*)malloc(sizeof(int) * r);
        memcpy(res[*resIdx], tmp, sizeof(int) * r);
        
        // 완성된 순열의 개수 증가
        (*resIdx)++; 
        
        return res; // 반환값은 형식 유지를 위해 res를 따름 (실제 로직에는 영향 없음)
    }

    // 2. 탐색 (원소 선택)
    for (int i = 0; i < n; i++) {
        // 이미 사용된 원소는 건너뛰기
        if (visited[i] == 0) { 
            // 선택 (Choose)
            tmp[tmpIdx] = base[i];
            visited[i] = 1;

            // 재귀 호출 (Explore)
            generatePermuteArr_internal(base, n, r, tmp, tmpIdx + 1, visited, res, resIdx);

            // 복원/백트래킹 (Unchoose) - 다음 순열을 위해 선택 취소
            visited[i] = 0;
        }
    }
    
    return res;
}

// 사용자 친화적인 래퍼(Wrapper) 함수
// 이 함수가 메모리를 할당하고 재귀 함수를 호출합니다.
int** getPermuteArr(int* base, int n, int r, int* result_count) {
    if (n <= 0 || r <= 0 || r > n) return NULL;

    unsigned long long total_permutations = permute(n, r);
    if (total_permutations == 0) return NULL;
    
    // 1. 최종 결과 배열 (res) 메모리 할당
    int** res = (int**)malloc(sizeof(int*) * total_permutations);
    
    // 2. 임시 배열 (tmp) 및 방문 배열 (visited) 메모리 할당
    int* tmp = (int*)malloc(sizeof(int) * r);
    int* visited = (int*)calloc(n, sizeof(int)); // 0으로 초기화
    
    int resIdx = 0; // 현재 완성된 순열의 개수 카운터

    // 3. 재귀 함수 호출
    generatePermuteArr_internal(base, n, r, tmp, 0, visited, res, &resIdx);
    
    // 4. 임시 메모리 해제
    free(tmp);
    free(visited);
    
    // 5. 최종 결과 개수 반환 (선택 사항)
    if (result_count != NULL) {
        *result_count = resIdx;
    }
    
    return res;
}


int main() {
    int test[] = {1, 2, 3, 4, 5};
    int n = 5; // 원본 배열 크기
    int r = 2; // 선택할 원소 개수
    printf("%llu\n", permute(n, r));

    // 1. 순열의 총 개수를 저장할 일반 정수 변수 선언
    int total_count = 0; 
    
    // 2. getPermuteArr 호출 시, total_count 변수의 '주소'(&)를 전달
    //    함수가 실행을 마친 후 이 주소에 nPr 결과(20)를 저장합니다.
    int** res = getPermuteArr(test, n, r, &total_count);

    
    printf("총 순열 개수 (%dP%d): %d\n", n, r, total_count);
    
    // 3. 순열 결과 출력 (total_count 변수 사용)
    for (int i = 0; i < total_count; ++i) { // i < total_count
        int* tmp = res[i];
        printf("[ %d", tmp[0]);
        for (int j = 1; j < r; ++j) { // j < r (순열의 길이)
            printf(", %d", tmp[j]);
        }
        printf(" ]\n");
    }

    // 4. 메모리 해제 (매우 중요!)
    //    각 순열 배열 (tmp)을 먼저 해제하고, 그 다음 res 배열을 해제해야 합니다.
    for (int i = 0; i < total_count; ++i) {
        free(res[i]); // 각 행(순열 1개) 해제
    }
    free(res); // 전체 배열 해제


    return 0;
}