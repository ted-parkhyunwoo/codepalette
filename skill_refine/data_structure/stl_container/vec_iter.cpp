#include <iostream>
#include <vector>
#include "myUtils.h"
#include <algorithm>    // std::find를 쓰기 위해.


// 예제 출력용 개인 작성 유틸 함수.
template <typename T>
void printVec(T map, std::string msg = "") {
    std::cout << msg << vecToString(map) << std::endl;
}


/*
std::vector 는 인덱스기반보다 반복자기반으로 다룰 일이 많으므로, 반복자 설명을 곁들임.

반복자는 컨테이너의 요소를 가리킨다. 배열의 포인터와 유사한 개념으로 생각할 수 있다.

1. 반복자 함수:

- begin() / end(): 컨테이너의 처음과 끝을 가리키는 반복자를 반환한다. begin()은 첫 번째 요소를, end()는 마지막 요소의 다음 위치를 가리킨다.
- rbegin() / rend(): 컨테이너의 역순 반복자를 반환한다. rbegin()은 마지막 요소를, rend()는 첫 번째 요소의 이전 위치를 가리킨다.
- cbegin() / cend(): 상수 반복자를 반환한다. cbegin()은 첫 번째 요소를, cend()는 마지막 요소의 다음 위치를 가리킨다.
- crbegin() / crend(): 상수 역순 반복자를 반환한다. crbegin()은 마지막 요소를, crend()는 첫 번째 요소의 이전 위치를 가리킨다.

반복자를 사용하여 수행할 수 있는 주요 작업:
1. 접근 (Access):
   - find(): 특정 값을 찾아 첫 번째로 발견된 위치의 반복자를 반환한다.
   - 특정 값의 위치 찾기: find()
   - 특정 인덱스로 이동하기: advance(), next(), prev()
   - 첫 번째 또는 마지막 요소 가리키기: front(), back(), begin(), end()

2. 수정 (Modify):
   - 특정 위치의 값을 변경하기: *(iterator) = value

3. 추가 (Add):
   - 특정 위치에 값 추가 (시작, 끝, 또는 지정된 인덱스에): push_back(), push_front(), insert(), emplace(), emplace_back(), emplace_front()

4. 삭제 (Delete):
   - 특정 위치의 값 삭제 (시작, 끝, 또는 특정 인덱스에서): erase(), pop_back(), pop_front()

2. 벡터 함수:

- push_back() / push_front(): 컨테이너의 끝/앞에 요소를 추가한다.
- pop_back() / pop_front(): 컨테이너의 끝/앞 요소를 제거한다.
- front(): 첫 번째 요소를 반환한다.
- back(): 마지막 요소를 반환한다.
- insert(): 지정된 위치에 요소를 삽입한다.
- erase(): 지정된 위치의 요소를 제거한다.
- emplace(): 지정된 위치에 요소를 생성하고 삽입한다.
- emplace_back() / emplace_front(): 컨테이너의 끝/앞에 요소를 생성하고 삽입한다.
- at(): 특정 위치의 요소에 대한 참조를 반환한다. 범위 검사를 수행하므로 안전한 접근이 가능하다.

추가적인 주요 함수:
- size(): 현재 컨테이너에 있는 요소의 개수를 반환한다.
- empty(): 컨테이너가 비어 있는지 확인한다.
- clear(): 컨테이너의 모든 요소를 제거한다.
- reserve(): (주로 벡터에서) 성능 향상을 위해 메모리를 미리 할당한다.
- resize(): 컨테이너의 크기를 조정한다.
- swap(): 두 컨테이너의 내용을 교환한다.
- capacity(): (주로 벡터에서) 현재 할당된 메모리 용량을 반환한다.
- max_size(): 컨테이너가 가질 수 있는 최대 요소 수를 반환한다.
*/



int main() {
    // 벡터 선언 및 초기화
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 반복자 함수 예제
    std::vector<int>::iterator it = vec.begin(); // 첫 번째 요소를 가리키는 반복자
    std::vector<int>::const_iterator cit = vec.cbegin(); // 상수 반복자
    std::vector<int>::reverse_iterator rit = vec.rbegin(); // 마지막 요소를 가리키는 역순 반복자
    std::vector<int>::const_reverse_iterator crit = vec.crbegin(); // 상수 역순 반복자

    // 특정 값 찾기: find(시작반복자, 끝반복자, 요소) -> 반복자 리턴.
    std::vector<int>::iterator it_find = find(vec.begin(), vec.end(), 3);
    if (it_find != vec.end()) {
        std::cout << "값 3을 찾았습니다: " << *it_find << std::endl;
    }

    // 반복자 이동
    std::advance(it, 2); // it를 세 번째 요소로 이동
    std::cout << "세 번째 요소: " << *it << std::endl;
    it++;       // it를 다음요소로 가리킴.
    std::cout << "네 번째 요소: " << *it << std::endl;


    // 첫 번째 및 마지막 요소 리턴: front(), back()
    std::cout << "첫 번째 요소: " << vec.front() << std::endl;
    std::cout << "마지막 요소: " << vec.back() << std::endl;

    // 값 추가 (끝에, 앞에, 중간에)
    vec.push_back(6); // 끝에 추가
    vec.insert(vec.begin(), 0); // 앞에 추가
    vec.emplace(vec.begin() + 3, 10); // 중간에 추가

    // 값 수정
    *(vec.begin() + 1) = 20; // 두 번째 요소를 20으로 변경

    // 값 삭제 (끝에서, 앞에서, 특정 위치에서)
    vec.pop_back(); // 끝의 요소 삭제
    vec.erase(vec.begin()); // 앞의 요소 삭제
    vec.erase(vec.begin() + 2); // 세 번째 요소 삭제

    // 벡터 관련 함수 예제
    std::cout << "벡터의 크기: " << vec.size() << std::endl; // 현재 크기
    std::cout << "벡터가 비어 있습니까? " << (vec.empty() ? "예" : "아니오") << std::endl; // 비어 있는지 확인

    // 벡터 요소 출력
    for (std::vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    // 역순 반복자 사용 예제
    for (std::vector<int>::reverse_iterator riter = vec.rbegin(); riter != vec.rend(); ++riter) {
        std::cout << *riter << " ";
    }
    std::cout << std::endl;

    // at() 함수 사용
    try {
        std::cout << "세 번째 요소 (at() 사용): " << vec.at(2) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "범위를 벗어났습니다: " << e.what() << std::endl;
    }

    // reserve()와 capacity() 사용
    vec.reserve(20); // 20개의 요소를 담을 수 있도록 메모리 예약
    std::cout << "벡터의 용량: " << vec.capacity() << std::endl;

    // resize() 사용
    vec.resize(10, 100); // 크기를 10으로 조정하고 새 요소를 모두 100으로 초기화(비우면 0)
    std::cout << "리사이즈 후 벡터의 크기: " << vec.size() << std::endl;

    // swap() 사용
    std::vector<int> vec2 = {7, 8, 9};
    vec.swap(vec2); // vec와 vec2의 내용을 교환
    std::cout << "교환 후 vec의 첫 번째 요소: " << vec.front() << std::endl;

    // clear() 사용
    vec.clear(); // 모든 요소 제거
    std::cout << "클리어 후 벡터가 비어 있습니까? " << (vec.empty() ? "예" : "아니오") << std::endl;

    return 0;
}
