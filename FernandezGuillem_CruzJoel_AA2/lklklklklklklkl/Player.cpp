#include "Player.h"
#include "Globals.h"

void Player::movePosition(Input input, Cell** map)
{
    switch (input)
    {
    case Input::UP:
        if (!(map[playerPos.x][playerPos.y - 1] == Cell::PARED || map[playerPos.x][playerPos.y - 1] == Cell::PEATON))
        {
            playerPos.y--;
        }
        playerDir = Direction::UP;
        break;
    case Input::DOWN:
        if (!(map[playerPos.x][playerPos.y + 1] == Cell::PARED || map[playerPos.x][playerPos.y + 1] == Cell::PEATON))
        {
            playerPos.y++;
        }
        playerDir = Direction::DOWN;
        break;
    case Input::LEFT:
        if (!(map[playerPos.x - 1][playerPos.y] == Cell::PARED || map[playerPos.x - 1][playerPos.y] == Cell::PEATON))
        {
            playerPos.x--;
        }
        playerDir = Direction::LEFT;
        break;
    case Input::RIGHT:
        if (!(map[playerPos.x + 1][playerPos.y] == Cell::PARED || map[playerPos.x + 1][playerPos.y] == Cell::PEATON))
        {
            playerPos.x++;
        }
        playerDir = Direction::RIGHT;
        break;
    }
}

void Player::movePlayer(Cell** map, Input input, int maxDinerosLS, int maxDinerosSF)
{

    if (input == Input::NONE)
        return;

    if (map[playerPos.x][playerPos.y] == Cell::DINERO)
    {
        if (playerPos.x <= mapX / 3)
        {
            dinero += randNum(5, maxDinerosLS);
        }
        else
        {
            dinero += randNum(5, maxDinerosSF);
        }

    }

    switch (input)
    {
    case Input::UP:
        map[playerPos.x][playerPos.y] = Cell::CJ;
        map[playerPos.x][playerPos.y + 1] = Cell::VACIO;
        break;
    case Input::DOWN:
        map[playerPos.x][playerPos.y] = Cell::CJ;
        map[playerPos.x][playerPos.y - 1] = Cell::VACIO;
        break;
    case Input::LEFT:
        map[playerPos.x][playerPos.y] = Cell::CJ;
        map[playerPos.x + 1][playerPos.y] = Cell::VACIO;
        break;
    case Input::RIGHT:
        map[playerPos.x][playerPos.y] = Cell::CJ;
        map[playerPos.x - 1][playerPos.y] = Cell::VACIO;
        break;
    }



}

void Player::atack(Cell** map, Peaton* peatones, int numPeatones)
{

    int posX = 0;
    int posY = 0;

    switch (playerDir)
    {
    case Direction::UP:
        posX = playerPos.x;
        posY = playerPos.y - 1;
        break;
    case Direction::DOWN:
        posX = playerPos.x;
        posY = playerPos.y + 1;
        break;
    case Direction::LEFT:
        posX = playerPos.x - 1;
        posY = playerPos.y;
        break;
    case Direction::RIGHT:
        posX = playerPos.x + 1;
        posY = playerPos.y;
        break;
    }

    if (map[posX][posY] == Cell::PEATON)
    {
        for (int i = 0; i < numPeatones; i++)
        {
            if (peatones[i].peatonPos.x == posX && peatones[i].peatonPos.y == posY)
            {
                peatones[i].setHp(peatones[i].getHp() - 1);
                if (peatones[i].getHp() == 0)
                {
                    peatones[i].die(map);
                }
            }
        }
    }

}