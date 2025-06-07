#pragma once
#include "Globals.h"
#include "Player.h"

class Map
{

	Cell** map;

public:

	Cell** getMap() { return map; }
	Map(int w, int h, int cars);
	~Map();
	void initMap(Player player);
	void printMap(Player player);

	int numCars = 0;

};


