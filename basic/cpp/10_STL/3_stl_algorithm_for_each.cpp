#include <iostream>
#include <algorithm>
#include <vector>

//for_each는 마지막 인자를 함수 자체로 넘겨야 함.

//functor - 함수를 가지고 있는 구조체, 함수처럼 사용 가능한 객체.
struct Func
{
    void operator()(int x) {
        std::cout << x*x << std::endl;
    }
    
};

// function pointer
void ff(int x) {
    std::cout << x*x << std::endl;
}


int main() {

    std::vector<int> vec{1,3,7,11,13};


    // functor 를 사용
    Func f;
    f.operator()(3);        //f(3)
    f(3);                   //f 는 객체이나, 함수처럼 사용 가능 
    std::for_each(vec.begin(), vec.end(), f);  


    // function pointer 를 사용. - 함수를 인자로 넘기되, 괄호를 넣지 않는다는 의미.
    ff(3);
    std::for_each(vec.begin(), vec.end(), ff);  
    //사실상 ff함수 자체는 포인터임 (gdb) print ff -> $1 = {void (int)} 0x1400016d0 <ff(int)>
    //std::cout << ff << std::endl;   // 이건 원래 함수 포인터 주소를 출력하나, 컴파일러에따라 출력이 안되거나 경고가 뜰 수 있음.


    // lambda를 사용.
    std::for_each(vec.begin(), vec.end(), 
        [](int x){
            std::cout << x*x << std::endl;
        });


    return 0;
}