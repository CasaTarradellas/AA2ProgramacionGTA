#pragma once

#include "Globals.h"
class Player;

class BigSmoke
{
	int pow;
	int hp;
	int maxHp;
	bool isAlive = true;

public:

	Position bigSmokePos;
	City peatonCity;

	void initBigSmoke(int hp, int pow);
	void spawnBS(Cell** map);
	void dieBS(Cell** map);
	bool isCloseToPlayerBS(Cell** map);
	void moveBS(Cell** map, Player& player);

	void setPowBS(int newPow) { pow = newPow; }
	int getPowBS() { return pow; }
	void setHpBS(int newHp) { hp = newHp; }
	int getHpBS() { return hp; }
	bool getIsAlive() { return isAlive; }
	void setIsAlive(bool alive) { isAlive = alive; }
};

