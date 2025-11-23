#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <algorithm> // std::sort, std::equal

// 1억개: 1.1초, 10억개: 17초, 25억개(위험!): 54초(거의 한계. cpu100%, 32기가 메모리 87%),  50억개(위험!:검증제외시 메모리2배 사용): 117초
// 검증은 모두 통과. 주석처리해도 됨.
// 쓰레드별로 shell 정렬을 실행함.
// 병합은 단일코어가 실행중.

inline void shell_sort(int* start, int* end) {
    int n = end - start;
    int gap = 1;
    while (gap < n / 3) gap = gap * 3 + 1;
    for (; gap > 0; gap /= 3) {
        for (int i = gap; i < n; ++i) {
            int tmp = start[i];
            int j = i;
            while (j >= gap && start[j - gap] > tmp) {
                start[j] = start[j - gap];
                j -= gap;
            }
            start[j] = tmp;
        }
    }
}

void parallel_insert_shell(int* arr, size_t n, unsigned num_threads) {
    if (n <= 1 || num_threads == 1) {
        shell_sort(arr, arr + n);
        return;
    }

    std::vector<std::thread> threads;
    size_t chunk_size = (n + num_threads - 1) / num_threads;
    auto worker = [](int* start, int* end) { shell_sort(start, end); };

    for (unsigned t = 0; t < num_threads; ++t) {
        int* start = arr + t * chunk_size;
        int* end = (t == num_threads - 1) ? arr + n : start + chunk_size;
        threads.emplace_back(worker, start, end);
    }
    for (auto& th : threads) th.join();

    size_t offset = chunk_size;
    while (offset < n) {
        size_t left = 0;
        while (left + offset < n) {
            size_t mid = left + offset;
            size_t right = std::min(left + 2 * offset, n);
            std::inplace_merge(arr + left, arr + mid, arr + right);
            left += 2 * offset;
        }
        offset *= 2;
    }
}

void run_parallel_sort(int* begin, int* end) {
    size_t n = end - begin;
    if (n <= 1) return; // 정렬할 요소가 없거나 하나뿐이면 리턴

    // 시스템의 하드웨어 스레드 수를 가져와서 사용
    unsigned num_threads = std::thread::hardware_concurrency();
    
    std::cout << "하드웨어 스레드 수: " << num_threads << "\n";
    std::cout << "총 요소 수: " << n << "\n";
    
    auto start_time = std::chrono::high_resolution_clock::now();

    // 핵심 병렬 정렬/병합 함수 호출
    parallel_insert_shell(begin, n, num_threads);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end_time - start_time;
    std::cout << "parallel_insert_shell 소요 시간: " << diff.count() << " s\n";
}

// 랜덤 배열 생성
int* getRandomIntArr(size_t n, int max_val = 10000) {
    int* arr = new int[n];
    for (size_t i = 0; i < n; ++i) arr[i] = rand() % max_val + 1;
    return arr;
}

int main() {
    // 난수 시드 설정
    srand(time(NULL) ^ getpid());
    
    // 1억 개 요소 배열 생성
    size_t n = 100000000; 
    std::cout << "배열생성/복사중 (N=" << n << ")\n";
    int* arr = getRandomIntArr(n);
    
    // 원본 복사본 생성 (std::sort 검증용) - 주석 해제하여 사용 가능
    // int* arr_copy = new int[n];
    // std::copy(arr, arr + n, arr_copy);

    std::cout << "정렬 시작...\n";
    
    run_parallel_sort(arr, arr + n);

    /*
    std::cout << "\n검증중...\n";
    // std::sort로 정렬 후 비교
    std::sort(arr_copy, arr_copy + n);
    bool ok = std::equal(arr, arr + n, arr_copy);
    std::cout << "정렬 결과: " << (ok ? "OK" : "FAIL") << "\n";
    */

    delete[] arr;
    // delete[] arr_copy; // 복사본 사용 시 주석 해제
    return 0;
}

/*
컴파일 방법:
g++ parallel_insert_shell.cpp -std=c++20 -O3 -pthread -o parallel_insert_shell
./parallel_insert_shell
- -O3 최적화 권장
- -pthread 필수 (멀티스레드 사용)
- 필요 시 배열 크기(n) 조정 가능
*/
