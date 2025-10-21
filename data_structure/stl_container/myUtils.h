#pragma once

#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <vector>

//! T 등 타입은 stringstream << 로 넣을수 있는 '<<'연산자 오버로딩이 되어있어야 함.

template <typename T>
std::string vecToString(const std::vector<T>& container) {
    std::ostringstream ss;
    ss << '[';

    if (!container.empty()) { 
        ss << container[0]; 
        for (auto it = container.begin() + 1; it != container.end(); it++) { ss << ", " << *it; }
    }

    ss << ']';
    return ss.str();
}


template <typename T, typename T2>
std::string umapToString(const std::unordered_map<T, T2>& container) {
    auto it = container.begin();
    if (it == container.end()) return "{}";
    std::ostringstream ss;
    ss << '{' << '\n';
    for (; it != container.end(); it++) {
        T key = it->first;
        T2 val = it->second;
        ss << "  " << key << ": " << val << '\n';
    }
    ss << '}';
    return ss.str();
}