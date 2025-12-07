#include <thread>
#include <vector>
#include <iostream>
#include <unistd.h>

const size_t THREADS = std::thread::hardware_concurrency();

using std::vector;
using std::thread;
using std::string;
template <typename T> using Iter = typename vector<T>::iterator;

template <typename T> void swap(Iter<T> x, Iter<T> y);
template <typename T> void insert(Iter<T> start, Iter<T> end);
template <typename T> void quick(Iter<T> start, Iter<T> end);
template <typename T> void parallel(Iter<T> start, Iter<T> end);

vector<int> getRandIntVec(const int size, const int max);
vector<string> getRandStrVec(const int size, const int max);
template <typename T> void printVec(std::vector<T>& v);
template <typename T> void printParallelDebug(std::vector<T>& v);       // 쓰레드퀵 디버그 전용 배열출력

int main() {
    srand(time(NULL) ^ getpid());

    std::cout << "THREAD: " << THREADS << std::endl;
    // string sort test
    vector<string> strSample = {"f", "d", "a", "e", "c", "asuh", "weu", "A", "d", "aflsdjfe", "ioo", "fiow", "394uef", "48934a", "9efj100", "IAY(D)", "!@#*(@!)"};
    printVec(strSample);
    parallel<string>(strSample.begin(), strSample.end());
    printVec(strSample);

    // random int sort test
    int sampleSize = 1000000000;
    vector<int> sample = getRandIntVec(sampleSize, 10000);
    auto start = std::chrono::steady_clock::now();
    parallel<int>(sample.begin(), sample.end());
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(diff).count();
    
    double seconds = (double)us / 1000000.0;
    std::cout << seconds << "\n";
    
    return 0;
}



vector<int> getRandIntVec(const int size, const int max) {
    vector<int> res(size);
    for (int i = 0; i < size; ++i) 
        res[i] = rand() % max + 1;
    return res;
}

vector<string> getRandStrVec(const int size, const int max) {
    if (size <= 0 || max <= 0) {
        return vector<string>();
    }
    
    vector<string> res(size);
    
    const int MIN_CHAR_ASCII = 97;
    const int RANGE_CHAR = 26;
    
    for (int i = 0; i < size; ++i) {
        const int str_len = (rand() % max) + 1; 
        
        string s(str_len, ' ');
        
        for (int j = 0; j < str_len; ++j) {
            s[j] = (char)(rand() % RANGE_CHAR + MIN_CHAR_ASCII);
        }
        
        res[i] = s;
    }
    return res;
}


template <typename T> void printVec(std::vector<T>& v) {
    const size_t size = v.size();
    if (size) {
        std::cout << "{ " << v[0];
        for (size_t i = 1; i < size; ++i) 
            std::cout << "," << v[i];
        std::cout << " }\n";
    } else 
        std::cout << "{ }\n";
}

template <typename T> void printParallelDebug(std::vector<T>& v) {
    const size_t size = v.size();
    if (size) {
        std::cout << "{ " << v[0];
        
        const size_t chunk_size = size / THREADS; 

        for (size_t i = 1; i < size; ++i) {
            std::cout << ",";
            if (chunk_size > 0) 
                if (i % chunk_size == 0 && i < size - THREADS)  // 마지막 쓰레드는 연달아 표현
                    std::cout << "\n";
                
            std::cout << v[i];
        }
        std::cout << " }\n";
    } else 
        std::cout << "{ }\n";
}

template <typename T> void swap(Iter<T> x, Iter<T> y) {
    const T tmp = *x;
    *x = *y;
    *y = tmp;
}

template <typename T> void insert(Iter<T> start, Iter<T> end) {
    const int sz = end - start;
    if (sz <= 1) return;

    for (Iter<T> p = start + 1; p < end; p++) {
        const T bf = *p;
        Iter<T> q = p;

        for (; q > start && bf < *(q - 1); --q)
            *q = *(q - 1);

        if (q != p)
            *q = bf;
    }
}

template <typename T> void quick(Iter<T> start, Iter<T> end) {
    const int sz =      end - start;
    if (sz <= 1)        return;
    if (sz <= 256)      { insert<T>(start, end);       return; }

    Iter<T> lIt =         start;
    Iter<T> rIt =         end - 1;
    const T pivot =     *(start + ((sz) / 2));

    while (lIt <= rIt) {
        while (pivot > *lIt)    ++lIt;
        while (pivot < *rIt)    --rIt;
        if (lIt <= rIt) {
            swap<T>(lIt, rIt);
            ++lIt;
            --rIt;
        }
    }

    if (rIt > start)       quick<T>(start, rIt + 1);
    if (lIt < end - 1)     quick<T>(lIt, end);
}

template <typename T> void parallel(Iter<T> start, Iter<T> end) {
    const int sz =      end - start;
    if (sz <= THREADS || THREADS == 1) {
        quick<T>(start, end);
        return;
    }

    // chunk 분배는 현재 마지막 쓰레드가 나머지를 다 물려받는 형태 -> 1개씩 더 물려받고, 모자란만큼은 덜 받는게 더 적절하나, 12쓰레드로 치면 고작 11개 늘어나는것이라 무시해도 됨.
    const size_t chunk = (sz / THREADS);
    vector<thread> tasks(THREADS);
    Iter<T> it = start;
    
    for (int i = 0; i < THREADS - 1; ++i, it += chunk)
        tasks.at(i) = thread(quick<T>, it, it + chunk);

    tasks.at(THREADS - 1) = thread(quick<T>, it, end);      // 초과분

    for (thread& task: tasks)                           // 회수
        if (task.joinable()) task.join();


    // 병합
    // THREADS 만큼 나누어서(마지막쓰레드는 초과분까지) 정렬된 것을 올바르게 병합해야함.
    vector<T> bf(sz);                       // 임시저장할 버퍼
    Iter<T> bfIt = bf.begin();              // 버퍼의 이터레이터

    // 각 쓰레드의 시작/끝 위치 선언
    vector<Iter<T>> begins(THREADS);     // 쓰레드 퀵정렬 후의 각각의 시작점 이터레이터
    vector<Iter<T>> ends(THREADS);       // 각 쓰레드의 도달목표 (-1을 가리켜야 마지막요소임)

    // 위치 할당
    begins.at(0) = start;
    ends.at(0) = start + chunk;
    for (size_t i = 1; i < THREADS; ++i) {
        begins.at(i) = begins.at(i - 1) + chunk;        
        ends.at(i) = begins.at(i) + chunk;
        if (i == THREADS - 1)       ends.at(i) += sz % THREADS;
    }


    // 반복자들의 요소중 최소값 꺼내서 bf로 할당 (이 행동때문에 사실 2배의 메모리공간이 할당되고 2배의 시간이 걸리는중인것 같음.)
    // 기저조건 트리거들.
    std::vector<char> finished(THREADS, 0);      // begins가 ends를 가리키면 true로 전환됨. vector로 전환.bool로하면 어마어마하게 느려져서 바꿈.
    int minThreadIdx;                   // 최소값 쓰레드 인덱스

    // 메인루프
    while (minThreadIdx != -1) {
        minThreadIdx = -1;
        
        // 최소값 찾기
        for (int i = 0; i < THREADS; ++i) {
            // 끝난건 제끼기
            if (finished[i]) continue;
            // 최소값시도
            if (minThreadIdx == -1 || *begins.at(i) < *begins.at(minThreadIdx)) {
                minThreadIdx = i;
            }
        }
        
        // 결정 난 반복자 위치 조정 및 bf로 갱신
        if (minThreadIdx != -1) {
            *bfIt = *(begins.at(minThreadIdx));
            bfIt++;
            (begins.at(minThreadIdx))++;
            if (begins.at(minThreadIdx) == ends.at(minThreadIdx))
                finished[minThreadIdx] = 1;
        }

    }

    // 덮어씌우기
    std::copy(bf.begin(), bf.end(), start);

}
