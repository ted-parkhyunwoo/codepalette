#include <iostream>

class Position {
private:
    int x_pos;
    int y_pos;

public:
    Position(int x, int y): x_pos(x), y_pos(y) {}
    
    void PrintPos() {
        std::cout << "[" << x_pos << "," << y_pos << "]" << std::endl;
    }

    // obj1.operator+(obj2);
    Position operator+(const Position& obj) const {
        return Position{x_pos + obj.x_pos, y_pos + obj.y_pos};
    }

    Position operator-(const Position& obj) const {
        return  Position{x_pos - obj.x_pos, y_pos - obj.y_pos};
    }

    bool operator==(const Position& obj) const {
        return (x_pos == obj.x_pos || y_pos == obj.y_pos);
    }

    bool operator!=(const Position& obj) const {
        return (x_pos == obj.x_pos || y_pos == obj.y_pos);
    }

    // obj.operator+(3)
    Position operator+(int val) const {
        return Position{x_pos + val, y_pos + val};
    }

    // operator+(3, obj);
    friend Position operator+(int val, const Position& obj) {
        return Position(val + obj.x_pos, val + obj.y_pos);
    }



};

int main() {
    Position a{1,3};
    Position b{3,2};
    Position c = a+b;
    c.PrintPos();
    c = c + 3;
    c.PrintPos();
    c = 3 + c;
    c.PrintPos();

    // 스트림 삽입 사용불가. (구현안했음.)
    //std::cout << a == c << a != c << std::endl;


    return 0;
}