//! 현재 편집한 환경이 (win11, mingw64) C++20을 완벽 지원하지 않아 확인 불가.
//! 컴파일 방식도 약간 다른듯 하다.

import Vector;
#include <cmath>

double sqrt_sum(Vector& v) {
    double sum = 0;
    for (int i = 0; i != v.size(); ++i) {
        sum += std::sqrt(v[i]);
    }
    return sum;
}
