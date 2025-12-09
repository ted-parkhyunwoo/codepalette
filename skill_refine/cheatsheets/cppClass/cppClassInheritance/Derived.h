#include "./Base.h"


// 자식(상속클래스)
class Derived : public Base {

    private:
        // 기본클래스에 없는 새로 추가된 멤버가 있다. private라 재상속시 height는 접근할 수 없다.
        double height;

    public:

        Derived(int id, std::string name) : Base{id, "derived " + name}, height{0} {
            // 여기에 Base를 넣으면 아무것도 안되고 파괴됨. 이때는 이니셜라이즈리스트를 적극 활용해야함.

            // 혹은 다음과 같이 쓸 수 있음(문법적으로 문제 없으며, 이렇게 작성하기도 함. )
            // this->id = id;
            // this->name = name;
            // this->height = height;
        }

        Derived(int id, std::string name, double height) : Base{id, "derived " + name} {
            this->height = height;      // 물론, 해당클래스의 멤버는 함수구현에 넣을 수 있다.
        }

        // 부모(기본) 메서드 재정의에 override 키워드를 쓰지 않음(virtual 에만 씀)
        void getInfo() {
            std::cout << "derived id: " << this->id << ", name: " << this->name << std::endl;
        }

        // 부모클래스에 없는 일부 행동을 추가할 수 있다.
        void sayHello() {
            std::cout << "Hello " << this->name << ". your height is " << this->height << ". \n";
        }

};