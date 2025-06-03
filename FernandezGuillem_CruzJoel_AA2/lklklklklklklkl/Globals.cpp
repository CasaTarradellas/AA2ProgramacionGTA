#pragma once
#include "Globals.h"

int mapX;
int mapY;

int randNum(int min, int max)
{
	return rand() % (max - min + 1) + min;
}