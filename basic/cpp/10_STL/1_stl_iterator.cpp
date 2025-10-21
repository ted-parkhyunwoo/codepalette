#include <iostream>

// 컨테이너 종류에 상관 없이(구현 구조 알 필요 없이) 추상적 접근 가능. (요소 접근, 찾기 등)
// 포인터와 유사한 사용
// stack, queue 를 제외하고 반복자를 사용한 순차접근(순환) 가능

#include <iterator>
#include <vector>
#include <set>

int main()
{

    //컨테이너타입<자료형(템플릿이므로)> 객체;
    std::vector<int> vec{1, 2, 3};
    std::set<int> mySet{1,2, 3};

    // 컨테이너타입::이터레이터 객체이름;
    std::vector<int>::iterator it1;     
    // auto it1 = vec.begin(); 처럼 초기화 하면 auto 사용 가능. (우변의 타입에 따라 추론하므로) 
    std::set<int>::iterator it2;

    /*
    begin, end
    [1] [2] [3] []
    vec.begin() 은 1. vec.end() 는 3뒤 (마지막요소의 뒤)

    rbegin, rend
    [], [1], [2], [3]
    vec.rbegin() 은3, vec.end()는 [1]의 앞(첫번째 요소 앞)   //주의! it++ 를 사용하는건 똑같음. it-- 형태로 감소하여 사용하지 않음.

    cbegin, cend
    반복자를 사용하되, const로 사용되며 값을 바꾸지 않도록 하겠다는 것.(crbegin, crend 도 같음)

    auto IT = vec.cbegin();
    *IT = 3;           // 빨간 줄이 뜨며 바꿀 수 없다는 뜻.
    */


    // int result = mySet[1]; (set은 indexing 안됨)
    it2 = mySet.begin();
    int result =  *it2;
    int result2 = *(mySet.begin());
    std::cout << result<< result2 << std::endl;

    
    // 반복문에서 사용할 때. (set은  인덱싱이 안되니 이터럴로 함.- 엥간한 컨테이너는 동일 작동.)
    for(auto it= mySet.begin(); it != mySet.end(); it++) {
        std::cout << *it;
    }

    std::cout << std::endl;




    // 이터레이터 연산자

    // 인덱스변경. + 정수, ++it, it++ 로 활용. vec[i] 등 과 같은 효과이나 set에도 적용 가능함.
    auto it = vec.begin();
    it += 2;    
    std::cout << *it << std::endl;

    // 값을 변경
    it -= 2;
    std::cout << *it << std::endl;
    *it = 2;
    for (size_t i = 0; i < vec.size(); i++) {  //i 를 std::vector<int>::size_type, size_t로 선언하든가, vec.size()를 (int)vec.size()로 하면 경고 안뜸.
        std::cout << vec[i];
    }

    return 0;
}

