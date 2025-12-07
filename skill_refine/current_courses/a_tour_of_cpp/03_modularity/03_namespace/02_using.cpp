#include <iostream>
#include <vector>

int main() {
    // using 은 현재 스코프 내 이름을 반복적으로 사용하는것을 피할 수 있다.
    {
        using std::cout;
        using std::endl;
        
        // 다음과 같이 사용 가능.
        cout << "Hello, World!" << endl;
    }

    {
        // 또한 using namespace 를 통해 라이브러리 전체를 사용할 수 있다.
        using namespace std;        // using-directive

        // std:: 와 같은 한정자 생략 가능.
        vector<int> v = {1, 2, 3, 4, 5};
        cout << "Vector: ";
        for (int i : v) {
            cout << i << " ";
        }

    }
    
    
    return 0;
}