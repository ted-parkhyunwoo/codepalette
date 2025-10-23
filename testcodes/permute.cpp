#include <iostream>
#include <vector>
#include <sstream>

// 조합 2개는 완성
template <typename C>
std::vector<std::vector<int>> testCode(const C& arr) {
    std::vector<std::vector<int>> res;
    int sz = arr.size();
    for (int i = 0; i < sz; ++i) {
        for (int j = i + 1; j < sz; ++j) {
            res.push_back({arr[i], arr[j]});
        }
    }
    return res;
}

// 순열 2개도 비슷함
template <typename C>
std::vector<std::vector<int>> testCode2(const C& arr) {
    std::vector<std::vector<int>> res;
    int sz = arr.size();
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            if (i == j) continue;
            res.push_back({arr[i], arr[j]});
        }
    }
    return res;
}


//! 하려던 것은 r 개 만큼인데, 2개가 아닌 여러개를 받을 경우 백트래킹을 해야 한다 함.


template <typename T>
std::string toString(T t) {
    if (t.size() < 1) return "[]";
    std::stringstream ss;
    ss << "[";
    for (auto& e : t) 
        ss << e << ", ";
    std::string res = ss.str();
    res.pop_back(); res.pop_back();
    res += "]";
    return res;
}


void printVectorVector(auto arr) {
    for (auto& v : arr)
        std::cout << toString(v) << " ";
    std::cout << std::endl;    
}


int main() {
    std::vector<int> test = {1, 2, 3, 4};
    printVectorVector(testCode(test));
    printVectorVector(testCode2(test));

    return 0;
}