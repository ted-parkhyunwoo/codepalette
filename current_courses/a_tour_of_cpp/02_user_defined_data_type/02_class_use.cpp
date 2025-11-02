#include <iostream>


// 기본적인 double 배열을 기반한 Vector 클래스
class Vector{
public:
    Vector(int s) : elem{new double[s]}, sz{s} {}       // 생성자
    double& operator[](int i) { return elem[i]; }       // [] 접근
    int size() { return sz; }                           // sz 접근
    
private:
    double* elem;
    int sz;
};



int main() {

    Vector a(3);
    for (int i = 0; i < a.size(); i++) {
        a[i] = i+1;
    }

    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << std::endl;
    }

    return 0;
}