#include <iostream>
#include <set>
#include <list>
#include <algorithm>

/*
set(집합)
특징:
    중복요소 가지지 않음.
    unordered_set 이 아닌이상 자동 정렬됨.
    인덱스 접근 불가

    사용자정의타입 (class) 를 사용시 자동 비교연산 정렬기능 때문에
operator< 오버로딩 필요함.

함수:
    size, max_size(매우 클 때), clear(), empty(), count(1) 등 사용 가능 
    
    front, back 사용 불가

    find, insert, remove 등은 algorithm의 멤버함수가 아니라 set의 멤버함수임.

바리에이션:
    multiset            - 중복허용, key로 정렬
    unordered_set       - 중복불가,정렬X, 요소수정불가
    unordered_multiset  - 정렬X, 중복허용
*/

template <typename T>
void printContainer(T user_con) {
    for (auto it = user_con.begin(); it != user_con.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}


int main() {
    std::set<int> mySet{3,1,5,2,4};
    std::list<int> myList{3,1,5,4,2};
    printContainer<std::set<int>>(mySet);
    printContainer(myList);
    
    // 삽입과 삭제, find.
    mySet.insert(6);
    mySet.erase(6);
    auto it = mySet.find(4);


    std::cout << *it << std::endl;
    printContainer(mySet);
    

    return 0;
}