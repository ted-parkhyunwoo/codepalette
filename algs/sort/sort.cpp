#include <iostream>
#include <vector>
#include <algorithm>

/*  DESC:
        cpp를 최대한 활용하며, STL Container(가능하면 std::vector)와 제네릭을 구현.
        오름차순/내림차순 선택 가능

    TODO:
        merge 구현

*/ 

typedef unsigned uint;
using std::swap;
using std::vector;
using std::cout;
using std::string;

// 단순 컨테이너 출력용
template <typename C>   void printVector(const C& v);
template <typename T>   bool condition(const T& a, const T& b, bool ascending = true);    // ascending = true: 오름차순(default arg), a > b  -> true
template <typename C>   void printValidateSort(void(*sort)(C&, bool));      // std::sort와 정렬함수를 비교하여 신뢰검사
bool condition(const string& a, const string&b, bool ascending = true);     // 문자열 사전정렬용 불리언(사실 std::string 은 > 혹은 < 연산자가 이미 구현되어있음)
vector<int> getRandIntVec(const int size, const int max);                   // 정수형 벡터 무작위배열 리턴
void bench(void (*sorting)(vector<int>&, bool), const int size);                  // 정렬시간측정(정수형 무작위 배열)
void bench(const int size);                                                       // 기본정렬 사용(std::sort)


// 정렬
template <typename C>   void bubble (C& v, bool ascending = true);
template <typename C>   void select (C& v, bool ascending = true);
template <typename C>   void insert (C& v, bool ascending = true);
template <typename C>   void shell  (C& v, bool ascending = true);
template <typename C>   void quick  (C& v, bool ascending = true);
template <typename C>   void merge  (C& v, bool ascending = true);



int main() {
    srand(time(NULL));


    // 정수형 vector
    vector<int> a = {8, 4, 2, 5, 1, 7, 0, 3, 9, 6};
    bubble(a);
    // _insert(a, 0, 4, true);
    printVector(a);
    

    // 문자열 vector
    vector<string> b = {"a", "b", "aa", "cba", "bba"};
    bubble(b, false);
    printVector(b);


    // 무작위배열 성능검증
    {
        cout << "\n---benchmark---\n";
        void (*funcs[])(vector<int>& v, bool) = {
            bubble, select, insert, shell, quick, //merge
        };
        // 정렬신뢰검사
        cout << "정렬검증중...\n";
        for (auto& f : funcs) {
            printValidateSort(f);
        }
        // 벤치마크
        cout << "시간측정중...\n";
        for (auto& f : funcs)
            bench(f, 100000);
        cout << "---완료!---\n";
    }


    // 고성능 테스트
    int LargeSize = 100000000;
    bench(quick, LargeSize);
    bench(LargeSize);


    return 0;
}


// 함수구현부
template <typename C>
void printVector(const C& v) {
    using std::cout;
    const uint sz = v.size();
    cout << '{' << v[0];
    for (uint i = 1; i < sz; ++i) {
        cout << ',' << ' ' << v[i];
    }
    cout << '}' << '\n';
}

template <typename T>
bool condition(const T& a, const T& b, bool ascending) {
    return ascending? a > b : a < b;
}

bool condition(const string& a, const string& b, bool ascending) {
    const uint minSize = std::min(a.size(), b.size());
    for (uint i = 0; i < minSize; ++i) {
        if (a[i] == b[i]) continue;
        return ascending? a[i] > b[i] : a[i] < b[i];
    }
    return a.length() > b.length();             // 내림차순 정렬이라도, 짧은길이 문자열 우선으로 정렬시킴.
}

vector<int> getRandIntVec(const int size, const int max) {
    vector<int> res(size);
    for (int i = 0; i < size; ++i) 
        res[i] = rand() % max + 1;
    return res;
}

void bench(void (*sorting)(vector<int>&, bool), const int size) {
    auto sample = getRandIntVec(size, 10000);
    
    clock_t sTime = clock();
    sorting(sample, true);
    const double res = (double)(clock() - sTime) / CLOCKS_PER_SEC;
    printf("%.6f s\n", res);
}

void bench(const int size) {
    auto sample = getRandIntVec(size, 10000);
    
    clock_t sTime = clock();
    std::sort(sample.begin(), sample.end());
    const double res = (double)(clock() - sTime) / CLOCKS_PER_SEC;
    printf("%.6f s\n", res);
}

template <typename C>   void printValidateSort(void(*sort)(C&, bool)) {
    const int sz = 10000;
    auto sample = getRandIntVec(sz, 10000);
    auto cp = sample;

    sort(sample, true);
    std::sort(cp.begin(), cp.end());
    bool res = true;
    for (int i = 0; i < sz; ++i) {
        if (sample[i] != cp[i]) {
            res = false;
            break;
        }
    }

    if (res)        cout << sz << "회 검증 성공!\n";
    else            cout << "실패\n";
}




template <typename C>
void bubble(C& v, bool ascending) {
    const uint sz = v.size();
    for (uint i = 0; i < sz - 1; ++i) {
        bool swapped = false;
        for (uint j = 0; j < sz - i - 1; ++j)                 // 맨 뒤부터 확정정렬
            if (condition(v[j], v[j + 1], ascending)) {
                swap(v[j], v[j + 1]);
                swapped = true;
            }
        if (!swapped) break;
    }
}

template <typename C>
void select(C& v, bool ascending)  {
    const uint sz = v.size();
    for (uint i = 0; i < sz - 1; ++i) {
        uint targetIdx = i;                                   // 업데이트될 인덱스 저장.
        for (uint j = i; j < sz; ++j)
            if (condition(v[targetIdx], v[j], ascending))
                targetIdx = j;                                // 비교 만족시 인덱스 업데이트
        if (targetIdx != i)
            swap(v[i], v[targetIdx]);           // 업데이트 발생시 swap
    }
}

template <typename C>
void insert(C& v, bool ascending) {
    const uint sz = v.size();
    for (uint i = 1; i < sz; i++) {         // 0번은 정렬된 상태로 봄.
        const auto mem = v[i];              // 삽입대상 저장
        uint j = i;                         // 비교대상 인덱스
        while (j > 0 && condition(v[j - 1], mem, ascending)) {
            v[j] = v[j - 1];                // 비교조건만족 발생시 배열 밀어내기: 삽입대상을 사이에 집어넣기 위해(j-1은 더미상태)
            --j;                            // 비교대상 인덱스 업데이트
        }
        v[j] = mem;                         // 삽입대상을 비교대상 인덱스(밀어내기 후)에 삽입.
    }
}

template <typename C>
void shell(C& v, bool ascending) {
    const uint sz = v.size();
    uint step = sz / 2;
    while (step > 0) {
        for (uint i = step; i < sz; ++i) {      // 삽입정렬처럼 v[i] 는 삽입대상. i - step만큼의 배열들이 비교대상(i 대신 j로 할당하며 j -= step으로 업데이트)
            const auto mem = v[i];
            uint j = i;
            while (j >= step && condition(v[j - step], mem, ascending)) {       // j 와 step이 같은경우(>=)도 포함해야 j - step으로 idx: 0 까지 접근 된다.
                v[j] = v[j - step];
                j -= step;
            }
            v[j] = mem;
        }
        step /= 2;
    }
}

template <typename C>
void _insert(C& v, int start, int end, bool ascending) {
    // 인덱스 기반의 삽입정렬. 부분정렬 혹은 quick의 최적화 등에 사용
    for (uint i = start + 1; i <= end; ++i) {
        const auto bf = v[i];
        uint j = i;

        while (j > start && condition(v[j - 1], bf, ascending)) { 
            v[j] = v[j - 1];
            --j;
        }
        if (j != i)     v[j] = bf;
    }
}

template <typename C>
void _quick(C& v, int left, int right, bool ascending) {
    if (left >= right) return;
    if (right - left <= 384) {
        _insert(v, left, right, ascending);
        return;
    }

    int pL = left, pR = right;
    const auto pivot =    v[(left + right) / 2]; 
    while (pL <= pR) {
        while (condition(pivot, v[pL], ascending))  ++pL;
        while (condition(v[pR], pivot, ascending))  --pR;
        if (pL <= pR)       swap(v[pL++], v[pR--]);
    }
    if (left < pR)  _quick(v, left, pR, ascending);
    if (pL < right) _quick(v, pL, right, ascending);
}

template <typename C>
void quick(C& v, bool ascending) {
    _quick(v, 0, (int)v.size() - 1, ascending);
}


template <typename C>
void merge  (C& v, bool ascending) {}