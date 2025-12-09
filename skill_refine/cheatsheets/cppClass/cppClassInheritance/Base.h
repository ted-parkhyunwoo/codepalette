#include <string>
#include <iostream>


// 부모(기본클래스). 자체로도 쓸수 있고, 자식(상속클래스)이 기능을 수정하거나 추가할 수 있음.
class Base {
    // 하위 클래스가 접근 할 수 있도록 private 가 아닌 protected 접근제한자를 사용
    protected:
        int id;
        std::string name;

    public:
        Base() {}
        Base(int userId, std::string userName) : id{userId}, name{userName} {}

        
        void getInfo() {
            std::cout << "id: " << this->id << ", name: " << this->name << std::endl;
        }

};
