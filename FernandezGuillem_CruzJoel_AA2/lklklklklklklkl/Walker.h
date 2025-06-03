#pragma once
#include "Globals.h"
#include "Player.h"

enum class PeatonType { AGRESIVE, NEUTRAL };

class Peaton
{
	PeatonType type;
	int pow;
	int hp;
	int maxHp;

public:

	Position peatonPos;
	City peatonCity;

	void initPeaton(City city, int hp, int pow);
	void spawn(Cell** map);
	void die(Cell** map);
	bool isCloseToPlayer(Cell** map);
	void move(Cell** map, Player& player);

	void setPow(int newPow) { pow = newPow; }
	int getPow() { return pow; }
	void setHp(int newHp) { hp = newHp; }
	int getHp() { return hp; }

};