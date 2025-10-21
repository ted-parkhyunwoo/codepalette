#include <iostream>
#include <map>

// python의 dict 처럼 key,value 로 사용.
// 중복허용 X
// 자동 정렬

// 바리에이션
// multimap (중복O)                 <map>에 포함.
// unordered map(정렬X)             #include <unordered_map> 으로 사용
// unordered multimap               <unordered_map> 으로 사용

int main() {
    std::map<std::string, int> age{{"Kim", 30}, {"Park", 24}};

    // 단순 value 출력
    std::cout << age["Kim"] << std::endl;

    // 키-밸류 쌍 추가(insert)
    age["Lee"] = 20;
    age.insert(std::pair<std::string, int>{"Yoo", 30});
    age.insert(std::make_pair("Choi", 36));
    std::cout << age["Lee"] << std::endl;

    // 삭제
    age.erase("Lee");

    // 검색은 map의 멤버함수 find로 사용하고 이터레이터로 반환받음.
    auto findIt = age.find("Yoo");
    if (findIt == age.end())
        std::cout << "No" << std::endl;
    else
        std::cout << "Found" << std::endl;

    // 존재여부 0 or 1;
    std::cout << age.count("Kim") << std::endl;

    // 각 요소의 Key들을 출력. (const auto& pair: age) 로 사용함.
    for (const std::pair<const std::string, int>& p : age) {
        std::cout << p.first << std::endl;
    }
    return 0;
}
