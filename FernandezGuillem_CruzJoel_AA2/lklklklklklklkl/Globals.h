#pragma once

#include <iostream>

// Game constants
const int CAM_RAD = 20;

extern int mapX;
extern int mapY;

// Enums
enum class City { LOSSANTOS, SANFIERRO, LASVENTURAS };
enum class Cell { CJ, PARED, PEATON, DINERO, VACIO, COCHE, BIGSMOKE };
enum class Input { UP, DOWN, LEFT, RIGHT, NONE };
enum class Direction { UP, DOWN, LEFT, RIGHT };

struct Position
{
    int x;
    int y;
};

// Utility functions
int randNum(int min, int max); 
