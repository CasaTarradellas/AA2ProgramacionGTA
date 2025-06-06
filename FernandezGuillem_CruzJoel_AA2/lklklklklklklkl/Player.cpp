#include "Player.h"
#include "Globals.h"

void Player::movePosition(Input input, Cell** map)
{
    switch (input)
    {
    case Input::UP:
        if (!(map[playerPos.x][playerPos.y - 1] == Cell::PARED || map[playerPos.x][playerPos.y - 1] == Cell::PEATON || map[playerPos.x][playerPos.y - 1] == Cell::COCHE))
        {
            playerPos.y--;
        }
        playerDir = Direction::UP;
        break;
    case Input::DOWN:
        if (!(map[playerPos.x][playerPos.y + 1] == Cell::PARED || map[playerPos.x][playerPos.y + 1] == Cell::PEATON || map[playerPos.x][playerPos.y + 1] == Cell::COCHE))
        {
            playerPos.y++;
        }
        playerDir = Direction::DOWN;
        break;
    case Input::LEFT:
        if (!(map[playerPos.x - 1][playerPos.y] == Cell::PARED || map[playerPos.x - 1][playerPos.y] == Cell::PEATON || map[playerPos.x - 1][playerPos.y] == Cell::COCHE))
        {
            playerPos.x--;
        }
        playerDir = Direction::LEFT;
        break;
    case Input::RIGHT:
        if (!(map[playerPos.x + 1][playerPos.y] == Cell::PARED || map[playerPos.x + 1][playerPos.y] == Cell::PEATON || map[playerPos.x + 1][playerPos.y] == Cell::COCHE))
        {
            playerPos.x++;
        }
        playerDir = Direction::RIGHT;
        break;
    }
}

void Player::movePositionCar(Input input, Cell** map)
{
    switch (input)
    {
    case Input::UP:
        if (!(map[playerPos.x][playerPos.y - 1] == Cell::PARED || map[playerPos.x][playerPos.y - 1] == Cell::COCHE))
        {
            if (map[playerPos.x][playerPos.y - 1] == Cell::PEATON)
                overPOM = true;
            playerPos.y--;
        }
        playerDir = Direction::UP;
        break;
    case Input::DOWN:
        if (!(map[playerPos.x][playerPos.y + 1] == Cell::PARED || map[playerPos.x][playerPos.y + 1] == Cell::COCHE))
        {
            if (map[playerPos.x][playerPos.y + 1] == Cell::PEATON)
                overPOM = true;
            playerPos.y++;
        }
        playerDir = Direction::DOWN;
        break;
    case Input::LEFT:
        if (!(map[playerPos.x - 1][playerPos.y] == Cell::PARED || map[playerPos.x - 1][playerPos.y] == Cell::COCHE))
        {
            if (map[playerPos.x + -1][playerPos.y] == Cell::PEATON)
                overPOM = true;
            playerPos.x--;
        }
        playerDir = Direction::LEFT;
        break;
    case Input::RIGHT:
        if (!(map[playerPos.x + 1][playerPos.y] == Cell::PARED || map[playerPos.x + 1][playerPos.y] == Cell::COCHE))
        {
            if (map[playerPos.x + 1][playerPos.y] == Cell::PEATON)
                overPOM = true;
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
        if (isInCar())
        {
            overPOM = true;
        }
        else
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
        

    }

    switch (input)
    {
    case Input::UP:
        map[playerPos.x][playerPos.y] = Cell::CJ;
        if (overPOM)
        {
            map[playerPos.x][playerPos.y + 1] = Cell::DINERO;
            overPOM = false;
            break;
        }
        map[playerPos.x][playerPos.y + 1] = Cell::VACIO;
        break;
    case Input::DOWN:
        map[playerPos.x][playerPos.y] = Cell::CJ;
        if (overPOM)
        {
            map[playerPos.x][playerPos.y - 1] = Cell::DINERO;
            overPOM = false;
            break;
        }
        map[playerPos.x][playerPos.y - 1] = Cell::VACIO;
        break;
    case Input::LEFT:
        map[playerPos.x][playerPos.y] = Cell::CJ;
        if (overPOM)
        {
            map[playerPos.x + 1][playerPos.y] = Cell::DINERO;
            overPOM = false;
            break;
        }
        map[playerPos.x + 1][playerPos.y] = Cell::VACIO;
        break;
    case Input::RIGHT:
        map[playerPos.x][playerPos.y] = Cell::CJ;
        if (overPOM)
        {
            map[playerPos.x - 1][playerPos.y] = Cell::DINERO;
            overPOM = false;
            break;
        }
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

void Player::getInCar(Cell** map)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (map[playerPos.x + j][playerPos.y + i] == Cell::COCHE)
            {

                map[playerPos.x][playerPos.y] = Cell::VACIO;

                playerPos.x = playerPos.x + j;
                playerPos.y = playerPos.y + i;
                inCar = true;
                
                return;
            }

        }
    }
}

void Player::getOffCar(Cell** map)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (map[playerPos.x + j][playerPos.y + i] == Cell::VACIO)
            {

                map[playerPos.x][playerPos.y] = Cell::COCHE;

                playerPos.x = playerPos.x + j;
                playerPos.y = playerPos.y + i;

                map[playerPos.x][playerPos.y] = Cell::CJ;

                inCar = false;

                return;
            }

        }
    }
}