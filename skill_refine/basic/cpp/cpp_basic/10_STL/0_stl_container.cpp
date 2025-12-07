#include <iostream>
#include <vector>

/* stl 컨테이너 종류.
sequential container - 순차
array, vector, list, forward_list, deque
삽입 순서 유지.

associative container - 관계
set, multi set, map, multi map
순서X or 규칙에 따라 저장

container adaptor
stack, queue, priority queue
변형 응용

공통 기능:

기본생성자, 오버로딩된 생성자, 복사생성자, 소멸자, 대입연산자 (포인터 자료형 깊은복사 됨.)

size(int), empty(bool), insert
비교연산자(<. <=, >, >=, ==) -> bool
swap, erase, clear
이터레이터(begin end, rbegin, rend, cbegin, cend, crbegin, crend)

*/



int main() {

    std::vector<int> a;
    a.push_back(3);
    
    for(int i = 0; i < a.size(); i++) {
        std::cout << a[i];
    }
}