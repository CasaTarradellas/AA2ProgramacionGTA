#pragma once
#include "Globals.h"
#include "Walker.h"

class Player
{

    Position playerPos;
    Direction playerDir;
    int dinero = 0;
    int hp = 0;
    int pow = 0;

public:

    Position getPosition() const { return playerPos; }
    void setPosition(int x, int y) { playerPos.x = x; playerPos.y = y; }
    Direction getDirection() const { return playerDir; }
    void setDir(Direction dir) { playerDir = dir; }
    int getDineros() { return dinero; }
    void setPow(int newPow) { pow = newPow; }
    int getPow() { return pow; }
    void setHp(int newHp) { hp = newHp; }
    int getHp() { return hp; }

    void movePosition(Input input, Cell** map);
    void movePlayer(Cell** map, Input input, int maxDinerosLS, int maxDinerosSF);
    void atack(Cell** map, Peaton* peatones, int numPeatones);


};

