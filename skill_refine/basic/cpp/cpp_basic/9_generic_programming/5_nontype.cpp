#include <iostream>


// 동적할당이 아닌데도, 런타임 시점에서 array의 사이즈를 정할 수 있게 됨.
template<typename T, int N>
class myArray {
private:
    // int size = N;
    T values[N];
public:
    myArray() {
        std::cout << "init array start." << std::endl;
        for (int i = 0; i < N; i++) {
            std::cout << "index[" << i << "]: ";
            std::cin >> values[i];
        }
        std::cout << "init complete." << std::endl;
    }

    void printArray() {
        std::cout << "{";
        for (int i = 0; i < N; i++) {
            std::cout << values[i];
            if (i != N - 1) std::cout << ", ";
        }
        puts("}");

    }
};

int main() {
    myArray<std::string, 5> a;
    a.printArray();

    return 0;
}