#include <iostream>

template<typename T>
class Vector {
protected:
    int sz;
    T* elem;
public:
    explicit Vector(int sz) : sz{sz} {
        if (sz < 1) return;
        elem = new T[sz];
    }

    ~Vector() { delete[] elem; }

    int size() const {
        return sz;
    }

    T& operator[](int i) {
        if (i < 0 || i >= sz) throw std::out_of_range("Index out of range"); 
        //! throw 안하면 begin(), end() 작성해도 범위기반 for문 작동 안됨.
        return elem[i];
    } 


    
};


//! begin() 과 end()를 작성하면 범위기반 for문 사용이 가능해진다.

//! 주석추가: begin, end 함수 작성이 이리 간편한것은 포인터로 이터레이터를 쓰기 때문에 it++연산(ptr++)등이 가능하기 떄문이다. 전통적인 배열(연속된 메모리에 쓰여진 데이터집합)이 아닌 복잡한 자료구조라면, 이터레이터클래스를 따로 작성하여 구현해야 한다.
// std::begin(객체) 혹은 std::end(객체) 도 사용가능
//? class 내부구현으로 T* begin() { return elem; }, T* end() { return elem + sz; } 도 작동하는데 이것이 뭔차이인지 궁금.. -> 기능상 완전 동일. class 내부부터 begin()등을 찾고 전역에서 찾기 때문. 다만 코드스타일 차이.
//! 전역 구현.
template<typename T>
T* begin(Vector<T>& v) {
    return &v[0];
}
template<typename T>
T* end(Vector<T>& v) {
    return &v[0] + v.size();
}

int main() {

    // 다타입 T를 받는경우, <> 사이에 타입을 넣어 정의한다.
    Vector<int> a(3);
    for (int i = 0; i < a.size(); i++) {
        a[i] = i+1;
    }
    
    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << ' ';
    } 
    std::cout << std::endl;

    for (auto& e : a) {
        e += 1;
        std::cout << e << " ";
    }
    std::cout << std::endl;

    return 0;
}