#include "Map.h"
#include "Globals.h"
#include "Player.h"

Map::Map(int w, int h, int cars)
{
    map = new Cell * [mapX];
    for (int i = 0; i < mapX; ++i) {
        map[i] = new Cell[mapY];
    }

    numCars = cars;
}

Map::~Map()
{
    for (int i = 0; i < mapX; ++i) {
        delete[] map[i];
    }
    delete[] map;
}

void Map::initMap(Player player)
{
    // Initialize all cells to VACIO
    for (int i = 0; i < mapY; i++)
    {
        for (int j = 0; j < mapX; j++)
        {
            map[j][i] = Cell::VACIO;
        }
    }

    // Set the borders to PARED
    for (int i = 0; i < mapX; i++)
    {
        map[i][0] = Cell::PARED;
        map[i][mapY - 1] = Cell::PARED;
    }

    for (int i = 0; i < mapY; i++)
    {
        map[0][i] = Cell::PARED;
        map[mapX - 1][i] = Cell::PARED;
    }

    //paredes ciudades

    int col1 = mapX / 3;
    int col2 = 2 * mapX / 3;

    for (int i = 1; i < mapY; i++)
    {
        for (int j = 6; j < mapX; j++)
        {
            if ((j == col1 || j == col2))
            {
                if (i != (mapY / 2) && i != ((mapY / 2) - 1) && i != ((mapY / 2) + 1))
                {
                    map[j][i] = Cell::PARED;
                }
                else
                {
                    map[j][i] = Cell::PEAJE;
                }
                
            }
            
        }
    }

    Position pos = player.getPosition();
    map[pos.x][pos.y] = Cell::CJ;

    for (int i = 0; i < numCars; i++)
    {
        bool cont = true;

        while (cont)
        {
            int randX = randNum(2, mapX - 2);
            int randY = randNum(2, mapY - 2);

            if (map[randX][randY] == Cell::VACIO)
            {
                map[randX][randY] = Cell::COCHE;
                cont = false;
            }

        }
    }

}

void Map::printMap(Player player)
{
    Position pos = player.getPosition();

    for (int i = pos.y - CAM_RAD; i < pos.y + CAM_RAD; i++)
    {
        for (int j = pos.x - CAM_RAD; j < pos.x + CAM_RAD; j++)
        {
            // Si está fuera del mapa, rellenar con ·
            if (j < 0 || j >= mapX || i < 0 || i >= mapY)
            {
                std::cout << " ";
                continue;
            }

            switch (map[j][i])
            {
            case Cell::PARED:
                std::cout << "X ";
                break;
            case Cell::CJ:
                if (player.isInCar())
                {
                    std::cout << "C ";
                    break;
                }
                switch (player.getDirection())
                {
                case Direction::UP:    std::cout << "^ "; break;
                case Direction::DOWN:  std::cout << "v "; break;
                case Direction::LEFT:  std::cout << "< "; break;
                case Direction::RIGHT: std::cout << "> "; break;
                }
                break;
            case Cell::PEATON:
                std::cout << "P ";
                break;
            case Cell::DINERO:
                std::cout << "$ ";
                break;
            case Cell::COCHE:
                std::cout << "C ";
                break;
            case Cell::BIGSMOKE:
                std::cout << "B ";
                break;
            case Cell::PEAJE:
                std::cout << "T ";
                break;
            default:
                std::cout << "  ";
                break;
            }
        }
        std::cout << std::endl;
    }
}
