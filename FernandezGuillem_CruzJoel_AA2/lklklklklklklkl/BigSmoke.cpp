#include "BigSmoke.h"
#include "Globals.h"
#include "Player.h"

void BigSmoke::initBigSmoke(int newHp, int newPow)
{
    hp = newHp;
    maxHp = hp;
    pow = newPow;
}

void BigSmoke::spawnBS(Cell** map)
{
    int citySpace = (mapX - 4) / 3;

    int thirdCityStart = 2 * citySpace + 4;
    int thirdCityEnd = mapX - 2;

    bigSmokePos.x = thirdCityStart + (thirdCityEnd - thirdCityStart) / 2;
    bigSmokePos.y = mapY / 2;
    
    map[bigSmokePos.x][bigSmokePos.y] = Cell::BIGSMOKE;
}

void BigSmoke::dieBS(Cell** map, gameState& state)
{
    map[bigSmokePos.x][bigSmokePos.y] = Cell::VACIO;
    isAlive = false;

    system("CLS");
    std::cout << "\n==============================" << std::endl;
    std::cout << "         !GAME OVER!         " << std::endl;
    std::cout << "   Has asesinado a Big Smoke" << std::endl;
    std::cout << "          !YOU WIN!" << std::endl;
    std::cout << "==============================\n" << std::endl;
    state = gameState::MENU;
    return;
        
    
}

bool BigSmoke::isCloseToPlayerBS(Cell** map)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (map[bigSmokePos.x + j][bigSmokePos.y + i] == Cell::CJ)
                return true;
        }
    }
    return false;
}

void BigSmoke::moveBS(Cell** map, Player& player)
{
    if (!isAlive) return;

    if (isCloseToPlayerBS(map))
    {
        if (hp < maxHp)
        {
            player.setHp(player.getHp() - pow);
        }
        return;
    }

    int dir = randNum(1, 4);

    switch (dir)
    {
    case 1:
        if (!(map[bigSmokePos.x][bigSmokePos.y - 1] == Cell::PARED || map[bigSmokePos.x][bigSmokePos.y - 1] == Cell::COCHE))
        {
            map[bigSmokePos.x][bigSmokePos.y] = Cell::VACIO;
            bigSmokePos.y--;
            map[bigSmokePos.x][bigSmokePos.y] = Cell::BIGSMOKE;
        }
        break;
    case 2:
        if (!(map[bigSmokePos.x][bigSmokePos.y + 1] == Cell::PARED || map[bigSmokePos.x][bigSmokePos.y + 1] == Cell::COCHE))
        {
            map[bigSmokePos.x][bigSmokePos.y] = Cell::VACIO;
            bigSmokePos.y++;
            map[bigSmokePos.x][bigSmokePos.y] = Cell::BIGSMOKE;
        }
        break;
    case 3:
        if (!(map[bigSmokePos.x - 1][bigSmokePos.y] == Cell::PARED || map[bigSmokePos.x - 1][bigSmokePos.y] == Cell::COCHE))
        {
            map[bigSmokePos.x][bigSmokePos.y] = Cell::VACIO;
            bigSmokePos.x--;
            map[bigSmokePos.x][bigSmokePos.y] = Cell::BIGSMOKE;
        }
        break;
    case 4:
        if (!(map[bigSmokePos.x + 1][bigSmokePos.y] == Cell::PARED || map[bigSmokePos.x + 1][bigSmokePos.y] == Cell::COCHE))
        {
            map[bigSmokePos.x][bigSmokePos.y] = Cell::VACIO;
            bigSmokePos.x++;
            map[bigSmokePos.x][bigSmokePos.y] = Cell::BIGSMOKE;
        }
        break;
    }


}