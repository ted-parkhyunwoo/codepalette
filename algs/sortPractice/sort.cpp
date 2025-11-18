#include <iostream>
#include <vector>

typedef unsigned uint;
using std::swap;
using std::vector;

// 단순 컨테이너 출력용
template <typename C> void printVector(const C& v);

// ascending = true 시 오름차순(default arg), a > b 일 경우 true 리턴.
template <typename T> bool condition(const T& a, const T& b, bool ascending = true);    // 오름,내림차순 정렬용 불리언
bool condition(const std::string& a, const std::string&b, bool ascending = true);       // 문자열 사전정렬용 불리언(사실 std::string 은 > 혹은 < 연산자가 이미 구현되어있음)

// 버블정렬: 바로 다음요소와 비교하여 swap. v[j] 와 v[j + 1] 을 비교후 swap
// 특징: 맨 뒤부터 정렬확정
template <typename C> void bubble(C& v, bool ascending = true);

// 선택정렬: 최소값/최대값 을 찾아 맨 앞으로 swap. i를 기준으로 시작하며 j가 최소값/최대값의 index로 업데이트 된다면 swap.
// 특징: 맨 앞부터 정렬 확정
template <typename C> void select(C& v, bool ascending = true);

// 삽입정렬 : 뽑은위치(i) 이전까지의 배열에서만 비교. 비교조건만족시 직전idx를 현재 idx로 밀어내기(swap사용안함) 후 삽입
// 특징: 0번은 정렬된 상태로 보고 1번 idx부터 비교조건검사와 배열 밀어내기 후 특정위치 삽입. 끝날때 까지 정렬이 확정되지 않음.
template <typename C> void insert(C& v, bool ascending = true);

// 쉘정렬 : 삽입정렬의 개선(증분, gap 활용). 삽입의 경우 매우 불량한 정렬에 진행하면 많은 이동이 일어남 -> shell sort로 해결
// 특징: step(gap) 만큼의 배열을 조작하며, step은 더 작게(/2)로 갱신(1이 될때 까지이며, 1일때 삽입정렬과 똑같아짐. 하지만 거의 정렬되어 빠름)
// step(gap)과 갱신은 둘다 /2로 제안됐으나, 마음대로 해도 됨. 다만, 크누스수열(3^k + 1), 치우라수열(실험검증수열)이 가장 빠르다고 알려짐.
// 크누스 수열은 knuth.c 참고
template <typename C> void shell(C& v, bool ascending = true);


// 사용예제 (필요에 따라 select, bubble, insert 변경, ascending 에 false등을 삽입하여 사용)
int main() {
    // 정수형 vector
    vector<int> a = {8, 4, 2, 5, 1, 7, 0, 3, 9, 6};
    shell(a);
    printVector(a);

    // 문자열 vector
    vector<std::string> b = {"a", "b", "aa", "cba", "bba"};
    insert(b, false);
    printVector(b);

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

bool condition(const std::string& a, const std::string& b, bool ascending) {
    const uint minSize = std::min(a.size(), b.size());
    for (uint i = 0; i < minSize; ++i) {
        if (a[i] == b[i]) continue;
        return ascending? a[i] > b[i] : a[i] < b[i];
    }
    return a.length() > b.length();             // 내림차순 정렬이라도, 짧은길이 문자열 우선으로 정렬시킴.
}

template <typename C>
void bubble(C& v, bool ascending) {
    const uint sz = v.size();
    for (uint i = 0; i < sz - 1; ++i) {
        for (uint j = 0; j < sz - i - 1; ++j)                 // 맨 뒤부터 확정정렬
            if (condition(v[j], v[j + 1], ascending))
                swap(v[j], v[j + 1]);
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