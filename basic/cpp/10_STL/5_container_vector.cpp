#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec{1, 2, 4};
    
    // 1. 요소 접근
    // 인덱스로 접근: vec[i], vec.at(i)
    // 잘못된 인덱스 접근 시: vec[i]는 런타임 오류 발생, vec.at(i)는 예외 발생

    // 처음과 끝 요소 접근 및 수정
    vec.front() = 3;  // 첫 번째 요소를 3으로 수정
    vec.back() = 7;  // 마지막 요소를 7로 수정
    int f = vec.front(); // 첫 번째 요소를 변수 f에 저장
    std::cout << f << std::endl;

    // 2. 요소 삽입과 삭제
    // 끝 위치 삽입
    vec.push_back(5);          // 임시 객체를 생성 후 삽입
    vec.emplace_back(99);      // 직접 할당된 공간에 삽입

    // 특정 위치 삽입
    vec.insert(vec.begin() + 2, 3);

    // 끝 위치 삭제
    vec.pop_back();

    // 특정 위치 삭제
    vec.erase(vec.begin() + 4);

    // 3. 기타 응용
    // 벡터 스왑: vec.swap(other_vector)
    // 벡터 정렬: std::sort(vec.begin(), vec.end())
    // 벡터가 비어 있는지 확인: vec.empty()

    // find와 insert 응용
    auto it = std::find(vec.begin(), vec.end(), 7); // 7을 찾음
    vec.insert(it + 1, 5); // 7 다음 위치에 5 삽입


    // 벡터 출력문
    for (auto num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;


    /* 
    4. 동적 배열이고, 크기가 유동적인 특징:
    
    배열이 capacity보다 size가 커지면 heap에서 더 큰 사이즈로 새로 할당 후 이전 것은 delete 자동 처리됨. vec은 다시 새로 할당된 heap 공간으로 포인팅 됨.

    size()와 capacity()의 관계:
    size가 더 커지는 순간 새로 할당됨.
    이전에 설정한 iterator나 data() 함수로 지정한 포인터가 무효화됨.
    */

    // capacity - 추가할 수 있는 최대 수량
    std::cout << vec.capacity() << std::endl;


    // 주의! 값이 자주 삽입, 삭제되면 포인터가 무효화되므로 안정적으로 사용할 수 없음
    // 따라서, 다음 코드는 보장되지 않음
    // 반복자도 같은 원리로 무효화될 가능성이 높음. 필요시 계속 갱신해서 사용해야 함
    int *data = vec.data();
    std::cout << *(data + 3) << std::endl;

    return 0;
}
