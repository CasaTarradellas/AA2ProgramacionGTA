#pragma once
#include "Globals.h"
#include "Walker.h"
#include "Map.h"
#include "BigSmoke.h"

class Player
{
    Position playerPos;
    Direction playerDir;
    int dinero = 0;
    int hp = 0;
    int pow = 0;
    bool inCar = false;
    bool overPOM = false;
    

public:

    bool hasPaid1 = false;
    bool hasPaid2 = false;

    Position getPosition() const { return playerPos; }
    void setPosition(int x, int y) { playerPos.x = x; playerPos.y = y; }
    Direction getDirection() const { return playerDir; }
    void setDir(Direction dir) { playerDir = dir; }
    int getDineros() { return dinero; }
    void setDineros(int dineros) { dinero = dineros; }

    void getInCar(Cell** map);
    void getOffCar(Cell** map);

    bool isInCar() { return inCar; }

    void setPow(int newPow) { pow = newPow; }
    int getPow() { return pow; }
    void setHp(int newHp) { hp = newHp; }
    int getHp() { return hp; }

    

    void movePosition(Input input, Cell** map);
    void movePositionCar(Input input, Cell** map);
    void movePlayer(Cell** map, Input input, int maxDinerosLS, int maxDinerosSF, int peaje1, int peaje2, gameState& state);
    void atack(Cell** map, Peaton* peatones, int numPeatones, BigSmoke* BS, gameState& state);


};

