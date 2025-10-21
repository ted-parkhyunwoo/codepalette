//! 강의 내용 외 멋대로 적은 추가내용이 있음.

#include <iostream>

class Account {
public:
    //! 생성자- 자동호출.  def __init__ (self, name, balance): 같이 연관지어 생각하면 쉬움. 
    //생성자 선언 안하면 컴파일러 자동생성. 하지만 값이 초기화 되지 않은 쓰레기값으로 유지되므로 사용하지 않음.-디폴트컨스트럭터(기본생성자)로 부름

    /* 멤버 초기화 리스트를 사용하지 않을 때.
    Account() {
        name = "None";
        balance = 0.0;
    };   */

    //!자동으로 기본 값이 들어가도록하고, 멤버 이니셜라이저 리스트 적용하는게 실전권장방법임.
    Account() : name{"None"}, balance{0} {}


    // 모두 매개변수 직접 입력 받을 때.
    //!멤버 이니셜라이저 리스트 적용시.(권장)   - private에 정의된 변수와 매개변수는 : 뒤에 변수(매개변수) 이런식으로 쓰이는걸 주목.
    Account(std::string username, double first_balance) : name(username), balance(first_balance){
        std::cout << name << ":" << balance << " new account made successfully" << std::endl;
    }   // 생성자는 리턴이 없으므로 앞에 void와 같은 타입 지정도 안함.


    // username만 입력 받을 때.
    //!생성자 위임 - 사용조건으로 위와 같이 모든 값을 입력 받는 생성자가 있어야 함.
    //username만 매개변수로 입력 받은경우 오버로드 됨. 초기화 과정에는 매개변수 전체를 초기화 하는 생성자를 재사용함.
    Account(std::string username) : Account(username, 0) {
        std::cout << "생성자위임 작동." << std::endl;
    }
    
    /* 
    //!기본매개변수로 사용시. -일반 함수와 마찬가지로 비어있는 매개변수는 최우측부터 자동 채워짐.
    Account(std::string name = "None", int balance = 0) : name(name), balance(balance) {}
    */

    //!소멸자- destructor. 인스턴스가 소멸되면 자동호출되는 멤버 함수임.
    ~Account(){
        std::cout << name << " user account removed." << std::endl;
    }

    // 그냥 구현해본 멤버함수.
    void deposit(double price){
        balance += price;
        std::cout << price << " add your account success." << std::endl;
    }
    void setName(std::string userinput) {
        name = userinput;
        std::cout << name << " is your account name." << std::endl;
    }
    void accountInfo() {
        std::cout << "name : " << name << std::endl << "balance : " << balance << std::endl;
    }


private:
    std::string name;
    double balance;
};

int main() {

    //스택메모리에 인스턴스 생성.
    Account abc("ted", 100);    //명시적
    abc.accountInfo();

    Account park = {"park", 300};   //암시적
    park.accountInfo();

    Account kim {"KIM", 200};
    kim.accountInfo();


    //동적메모리 할당시. 여러가지 인스턴스 생성 방법.
    Account* heap = new Account("heap", 200);
    heap->accountInfo();
    delete heap;

    Account* yoo = new Account {"Yoo", 12000};
    yoo->accountInfo();
    delete yoo;

    Account* lee_ptr = new Account();
    lee_ptr->setName("lee");
    lee_ptr->deposit(200);
    lee_ptr->accountInfo();
    delete lee_ptr;

    Account test("생성자위임계정이름");

    return 0;
}