#pragma once
#include "Globals.h"
#include "Player.h"

class Map
{

	Cell** map;

public:

	Cell** getMap() { return map; }
	Map(int w, int h);
	~Map();
	void initMap(Player player);
	void printMap(Player player);

};

