#include <iostream>
#include <array>

// 기존의 정적배열과 유사하게 사이즈가 정해짐.
// 대신 iterator 와 algorithm 사용 가능 -cpp에선 안정성, 기능성으로 이쪽이 권장됨.
// raw array와 마찬가지로, 배열의 크기는 컴파일 시점에 정해져야 함.(런타임 사용시는 vector 권장) - 동적할당을 강제 해도 이 경우는 안됨

int main() {
    // array객체는 자료형과 사이즈(size_t) 를 입력받아서 초기화함.
    // raw array와 stl array는 둘다 사이즈 변경 불가
    std::array<int, 5> arr1{1,2,3,4,5};
    std::array<std::string, 3> arr2{"Kim", "Lee", "Park"};

    // 요소 길이
    std::cout << arr1.size() << std::endl;

    // 요소 접근
    std::cout << arr2[1] << std::endl;  //operator[] 가 작성되어있음.
    std::cout << arr2.at(1) << std::endl;

    std::cout << arr2.front() << std::endl;      // 첫요소 ( begin 반복자 아님 주의)
    std::cout << arr2.back() << std::endl;       // 마지막요소 ( end 반복자 아님 주의)

    // 기타 주요함수
    bool emp = arr1.empty();                // bool형식으로 비어있는지 반환
    size_t sz = arr1.max_size();             // 배열의 최대사이즈 반환
    arr1.fill(10);               // 모든 요소를 10으로 채움
    // arr1.swap(arr2);          // 두 배열을 swap
    int *data = arr1.data();     // 배열의 주소 반환
    

    *data = 1;                   // 주소반환 data() 덕분에 일반 배열처럼 포인터로 접근 가능
    *(data + 1) = 2;
    
    for (size_t i = 0; i < arr1.size(); i++) {      // size()함수는 size_t 타입이다. int로 i를 초기화 해도 작동은 되나, 경고가 계속 뜸.
        std::cout << arr1[i] << std::endl;
    }

    return 0;
}