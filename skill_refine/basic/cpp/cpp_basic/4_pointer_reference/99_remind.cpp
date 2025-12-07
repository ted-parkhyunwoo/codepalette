#include <iostream>


    // 포인터(역참조) * 과 참조자 &
    // ptr로 리턴하는 함수는 동적할당 해야하는 이유.
    // array와 pointer의 유사성
    // pointer의 상수선언


int* makePtr(int n);        // 아래 2번 예제를 위한 함수 프로토타입
void changeValue (int &n);  // 아래 5번 예제를 위한 함수 프로토타입

int main() {


    //! 1. 비어있는 값으로 포인터 초기화시.
    int* ptr = nullptr; 
    int num = 100;
    ptr = &num;         // 대입은 참조자&사용. (주소를 변경한다는 의미로 생각할 것.)
    *ptr /= 2;          // 값 변경시 *ptr

    std::cout << *ptr << std::endl;

    //! 2. ptr로 리턴받는 함수를 사용시에는 동적할당을 해야함.(그냥 쓰면 값 보전이 안됨.)
    int* ptr2 = makePtr(3);
    std::cout << *ptr2 << std::endl;

    delete ptr2;


    //! 3. C스타일 array를 포인터로 전환
    int myArray[] = {1,2,3,4,5};
    int* arrPtr = myArray;

    // 배열 or 포인터의 요소 접근
    for (int i = 0; i < 5; i++) {

        // 수정
        arrPtr[i] = i;
        // myArray[i] = i;  //어차피 같음.

        // 출력
        std::cout << *(arrPtr + i);
        std::cout << *(myArray + i);
        std::cout << arrPtr[i];
        std::cout << myArray[i];
    }
    puts("");

    // array를 포인팅 했었지만, int* 라서 그냥 int로 전환도 가능.
    arrPtr = &num;
    std::cout << *arrPtr;
    puts("");


    //! 4. 포인터와 상수선언.
    int temp = 1;
    int temp2 = 2;
    // 1. const int*        가리키는 값을 상수화. 주소변경은 가능.
    const int* tmpPtr = &temp;
    // *tmpPtr = 3;         //사용불가.
    tmpPtr = &temp2;        //사용가능.

    // 2. int* const        포인팅 주소를 상수화(주소 고정). 값 변경은 가능.
    int* const tmpPtr2 = &temp;
    *tmpPtr2 += 1;          // 사용가능

    // 3. const int* const  주소, 값 고정.
    const int* const holdPtr = &temp;


    //! 5. 참조자 (상수 포인터 같은 간소화버전, 함수 매개변수로 자주 사용)

    // b의 값을 변경하면 a도 같이 변경됨.
    int a = 1;
    int& b = a;
    b = 3;      // 사용시 변수처럼 씀. 포인터처럼 *b로 하지 않음.
    std::cout << a << " " << b << std::endl;

    // 참조자를 매개 변수로 받는 함수를 통해 값 변경.(복사생성 하지 않고 값 변경.)
    changeValue(a);
    std::cout << a << std::endl;


    // 참고사항(중요한것 아님.)
    // l-value 와 r-value
    int x = 100;    // l-value 는 x, r-value 는 100 임.
    // 기본적으로 참조자는 l-value만 사용 가능.

    // r-value 사용시 예제 (중요한건 아님.)
    int&& myref = 100;      // r-value reference.
    const int& myref2 = 100;

    /* 메모리 값은 다음과 같이 이루어짐. (stack영역에 저장됨.)
    -exec print myref
    $1 = (int &&) @0x5ffde0: 100
    -exec print x
    $2 = 100
    -exec print myref2
    $3 = (const int &) @0x5ffddc: 100
    */


    return 0;
}

int* makePtr(int n) {
    int* result = new int{n};
    return result;
}

void changeValue (int &n) {
    n++;
}