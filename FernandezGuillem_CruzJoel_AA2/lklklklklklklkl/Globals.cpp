#include "Globals.h"

int mapX;
int mapY;

gameState state = gameState::START;

int randNum(int min, int max)
{
	return rand() % (max - min + 1) + min;
}