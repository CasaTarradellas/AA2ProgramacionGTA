#include "Walker.h"
#include "Globals.h"
#include "Player.h"

void Peaton::initPeaton(City city, int newHp, int newPow)
{
    int randType = randNum(1, 2);
    if (randType == 1)
    {
        type = PeatonType::NEUTRAL;
    }
    else
    {
        type = PeatonType::AGRESIVE;
    }
    peatonCity = city;
    hp = newHp;
    maxHp = hp;
    pow = newPow;
}

void Peaton::spawn(Cell** map)
{
    int citySpace = (mapX - 4) / 3;
    bool cantSpawn = true;

    while (cantSpawn)
    {
        switch (peatonCity)
        {
        case City::LOSSANTOS:

            peatonPos.x = randNum(1, citySpace - 1);
            peatonPos.y = randNum(1, mapY - 2);
            break;
        case City::SANFIERRO:

            peatonPos.x = randNum(citySpace + 1, 2 * citySpace - 1);
            peatonPos.y = randNum(1, mapY - 2);
            break;
        default:
            break;
        }

        if (map[peatonPos.x][peatonPos.y] == Cell::VACIO)
        {
            cantSpawn = false;
        }
    }
    map[peatonPos.x][peatonPos.y] = Cell::PEATON;
}

void Peaton::die(Cell** map)
{
    hp = maxHp;
    map[peatonPos.x][peatonPos.y] = Cell::DINERO;
    spawn(map);
}

bool Peaton::isCloseToPlayer(Cell** map)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (map[peatonPos.x + j][peatonPos.y + i] == Cell::CJ)
                return true;
        }
    }
    return false;
}

void Peaton::move(Cell** map, Player& player)
{
    if (isCloseToPlayer(map))
    {
        if (type == PeatonType::AGRESIVE && hp < maxHp)
        {
            player.setHp(player.getHp() - pow);
        }
        return;
    }

    int dir = randNum(1, 4);

    switch (dir)
    {
    case 1:
        if (!(map[peatonPos.x][peatonPos.y - 1] == Cell::PARED))
        {
            map[peatonPos.x][peatonPos.y] = Cell::VACIO;
            peatonPos.y--;
            map[peatonPos.x][peatonPos.y] = Cell::PEATON;
        }
        break;
    case 2:
        if (!(map[peatonPos.x][peatonPos.y + 1] == Cell::PARED))
        {
            map[peatonPos.x][peatonPos.y] = Cell::VACIO;
            peatonPos.y++;
            map[peatonPos.x][peatonPos.y] = Cell::PEATON;
        }
        break;
    case 3:
        if (!(map[peatonPos.x - 1][peatonPos.y] == Cell::PARED))
        {
            map[peatonPos.x][peatonPos.y] = Cell::VACIO;
            peatonPos.x--;
            map[peatonPos.x][peatonPos.y] = Cell::PEATON;
        }
        break;
    case 4:
        if (!(map[peatonPos.x + 1][peatonPos.y] == Cell::PARED))
        {
            map[peatonPos.x][peatonPos.y] = Cell::VACIO;
            peatonPos.x++;
            map[peatonPos.x][peatonPos.y] = Cell::PEATON;
        }
        break;
    }


}