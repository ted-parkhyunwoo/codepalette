#include <iostream>
#include <stdexcept>

//! 구체타입: concrete class.  : 내장타입 (int[], double 등) 처럼 작동하게끔 구현한 데이터타입 클래스.

/*
구체타입의 객체를 스택, 정적메모리, 다른객체 내에 둘 수 있다.
객체를 (포인터나 참조를 통해서만이 아니라) 직접 참조할 수 있다.
객체를 즉시 그리고 완전하게 초기화 할 수 있다(예를들어 생성자를통해).
객체를 복사하고 이동할 수 있다.
*/

class myVector {
public:
    // 생성자
    myVector(int size) : sz(size), data(new int[size]) {
        for (int i = 0; i < sz; ++i) {
            data[i] = 0; // 모든 요소를 0으로 초기화
        }
    }

    //! 소멸자 : RAII  원칙에 따라 생성자에서 획득한 자원은 사용후 회수되도록 해제한다.
    ~myVector() { delete[] data; }

    // 복사 생성자
    myVector(const myVector& other) : sz(other.sz), data(new int[other.sz]) {
        for (int i = 0; i < sz; ++i) {
            data[i] = other.data[i];
        }
    }

    // 이동 생성자
    myVector(myVector&& other) noexcept : sz(other.sz), data(other.data) {
        other.sz = 0;
        other.data = nullptr;
    }

    // 복사 대입 연산자
    myVector& operator=(const myVector& other) {
        if (this == &other) return *this; // 자기 자신을 대입하는 경우 방지
        delete[] data; // 기존 데이터 해제
        sz = other.sz;
        data = new int[sz];
        for (int i = 0; i < sz; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    // 이동 대입 연산자
    myVector& operator=(myVector&& other) noexcept {
        if (this == &other) return *this; // 자기 자신을 대입하는 경우 방지
        delete[] data; // 기존 데이터 해제
        sz = other.sz;
        data = other.data;
        other.sz = 0;
        other.data = nullptr;
        return *this;
    }

    // 인덱스 연산자
    int& operator[](int index) {
        if (index < 0 || index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const int& operator[](int index) const {
        if (index < 0 || index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 크기 반환
    int size() const { return sz; }

    // 크기 변경
    void setSize(int newSize) {
        int* newData = new int[newSize];
        for (int i = 0; i < sz && i < newSize; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        sz = newSize;
    }

private:
    int sz;
    int* data;
};

// 다른 객체 내에 포함된 myVector 테스트용 클래스
class Container {
public:
    Container() : vec(3) {}
    myVector vec;
};

int main() {
    // 스택에 생성
    myVector vec1(5);
    for (int i = 0; i < vec1.size(); ++i) {
        vec1[i] = i + 1;
    }

    // 복사 생성자 테스트
    myVector vec2 = vec1;

    // 이동 생성자 테스트
    myVector vec3 = std::move(vec1);

    // 정적 메모리에 생성
    static myVector staticVec(3);

    // 다른 객체 내에 포함된 myVector 테스트
    Container container;
    container.vec[0] = 42;

    // 출력
    for (int i = 0; i < vec2.size(); ++i) {
        std::cout << vec2[i] << " ";
    }
    std::cout << std::endl;

    
    std::cout << "size: " << container.vec.size() << std::endl;
    for (int i = 0; i < container.vec.size(); ++i) {
        std::cout << container.vec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}