#include <iostream>
#include <unordered_map>
#include "myUtils.h"

/*
순서가 보장되지 않는 해시맵 unordered_map. 가장 많이 쓰이는 해시테이블 자료구조.
데이터는 키: 밸류 형태로 저장되며, 키는 중복될 수 없음. 밸류는 중복가능한 데이터.
연속된 메모리공간이 아님. 따라서 굳이 순회하려면 반복자를 사용해야 함.
해시기반 탐색. map같은경우는 이진트리.
*/

// unordered_map 예제 출력용 개인 작성 유틸 함수.
template <typename T>
void printMap(T map, std::string msg = "") {
    std::cout << msg << umapToString(map) << std::endl;
}

int main() {
    std::unordered_map<std::string, std::string> m;


    // 1. 키 혹은 키-값 추가.
    // 키값으로 추가
    m["test"] = "test's value.";
    m["test2"] = "test2's value.";
    printMap(m, "키,값으로 추가: ");

    // std::pair로 insert하여 추가
    std::pair<std::string, std::string> tmp = {"Hello", "World"};
    m.insert(tmp);

    // 조회목적 등이라도 없는 키-값쌍이라면 키 생성됨. 존재 확인하고싶다면 count 혹은 find사용.
    std::string t = m["empty"];
    m["empty2"];    // 이런식으로 하더라도 empty2라는 키-값(빈값) 생성됨.
    printMap(m, "추가 후 모두 조회: ");


    // 2. 키 존재여부
    // 키가 있는지 없는지 확인할 때는 count(키) -> 0 or 1 를 사용.
    bool hasKey = m.count("empty");
    int hasKey2 = m.count("empty");

    // find(키) 는 반복자를 리턴.
    const auto empty3It = m.find("empty3");
    std::cout << "empty3 존재여부: " << ((empty3It != m.end())? "있음" : "없음") << std::endl;

    // key-value pair(키-값 쌍) 총 갯수 조회
    std::cout << "m의 size: "<< m.size() << std::endl;


    // 3. 삭제.
    // 키 기반 key-value pairs 삭제.
    m.erase("empty");

    // 반복자 기반 삭제.
    auto it = m.find("empty2");
    it = m.erase(it);       //! 지우면서 it에 다음요소를 리턴받고 삭제하는 두가지 역할을 하는 erase().
    printMap(m, "삭제 후 남은 키밸류: ");

    // +@. 삭제 후 it 반복자가 가리키는 값을 출력해봄.
    std::cout << "it의 다음요소: " << it->first << ": " << it->second << std::endl;
    //? 만약 find의 매개변수로 일반적인 키가 들어간다면... -> 실패함. erase함수는 타입별로(반복자, 스트링 등) 오버로딩작성된 것으로 보임.
    

    // 4. for문, 반복자등을 응용하여 사용.
    // 범위기반 for문 사용시 pair로 사용(자료구조가 index기반이 아니라 전통적 for문 사용불가, 반복자는 가능.) 다만 const auto& pari로 축약가능.
    std::cout << "범위기반 map의 키값들 조회: \n";
    for (const std::pair<std::string, std::string>& pair: m) { std::cout << pair.first << std::endl; }

    // 범위기반 반복문에서 구조적 바인딩(structured binding, C++17)을 이용한 pair의 key, value 분해.
    for (const auto& [key, value] : m) { std::cout << key << " => " << value << std::endl; }

    //? 구조적바인딩에 대해 혹시 모른다면:
    const auto& [key, val] = std::tuple<int, int>(111, 222);
    std::cout << "구조적바인딩테스트: " << key << val << std::endl;

    // 반복자를 이용한 조건기반 삭제- "Hello": "World" 를 삭제
    //! 코드 분석: it = m.erase(it)에서 erase는 첫번째로 map에서 it으로 설정된 값을 지우지만, 두번째로 다음 반복자를 리턴함.
    for (auto it = m.begin(); it != m.end(); ) {
        if (it->second.find("World") != std::string::npos) {
            it = m.erase(it);       // 모범적인 반복자 사용코드예제라 함.
        } else {
            ++it;
        }
    }

    printMap(m, "현재 키밸류: ");

    return 0;
}