#include <iostream>


// 전통적인 C 방식의 구조체.
struct Vector
{
    double* elem;
    int sz;
};

void vector_init(Vector& v, int s) {
    v.elem = new double[s]; // 배열로 할당.
    v.sz = s;
}

double read_and_sum(int s) {
    Vector v;
    vector_init(v, s);

    for (int i = 0; i!=s; ++i) {
        std::cin>>v.elem[i];
    }

    double sum = 0;
    for (int i = 0; i!=s; ++i) {
        sum += v.elem[i];
    }
    return sum;
}

int main() {
    double res = read_and_sum(5);
    std::cout << res;
    return 0;
}