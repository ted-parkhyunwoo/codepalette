//! 현재 PlayerHandler 는 플레이어만 관리되고 있음.
//! 만약 Player 뿐 아니라 , enemy나 NPC등이 추가된다면 GameHanlder로 바꾸고 모든걸 상속관리 해야함.
//! 그게 아니라면 PlayerHandler에 수많은 멤버함수들을 추가하고 관리해야함.

#include <iostream>

class Player
{
    private:
    int x,y;
    int speed;
    public:
    Player(int x, int y, int speed) : x{x}, y{y}, speed{speed}
    {

    }
    void Move(int dx, int dy) {
        x += dx * speed;
        y += dy * speed;
    }
    void ShowPosition() {
        std::cout << x << ", " << y << std::endl;
    }
};

/// @brief 플레이어 주소 출력.
class PlayerHandler
{
    private:
    Player* playerList[50]; //!이 부분이 에너미, npc 등이 또 추가가 되야함. 다른 멤버함수와 소멸자도 따로 작동.
    int playerNum;

    public:
    PlayerHandler() : playerNum{0} {}

    void AddPlayer(Player* p) {
        playerList[playerNum++] = p;
    }

    void ShowAllPlayerPosition() const {
        for (int i = 0; i < playerNum; i++) {
            playerList[i]->ShowPosition();
        }
    }
    ~PlayerHandler()
    {
        for (int i = 0; i < playerNum; i++) {
            delete playerList[i];
        }
    }

};



int main() {
    PlayerHandler playerHandler;
    playerHandler.AddPlayer(new Player(1, 1, 1));
    playerHandler.AddPlayer(new Player(5, 5, 1));
    playerHandler.AddPlayer(new Player(2, 3, 1));
    playerHandler.ShowAllPlayerPosition();

    return 0;
}