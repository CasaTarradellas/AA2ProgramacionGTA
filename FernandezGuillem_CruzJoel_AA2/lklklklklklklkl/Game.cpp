
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Globals.h"
#include "Walker.h"
#include "Player.h"
#include "Map.h"
#include "BigSmoke.h"


int main()
{
    srand(time(NULL));

    //SETUP

    gameState state = gameState::START;

    Player cj;
    cj.setPosition(3, 3);
    cj.setDir(Direction::UP);
    BigSmoke BS;
    
    int numPeatonesLS = 0;
    int numPeatonesSF = 0;
    int numPeatonesLV = 0;
    int peaje1 = 0;
    int peaje2 = 0;
    int maxDinerosLS = 0;
    int maxDinerosSF = 0;
    int maxDinerosLV = 0;

    int menu = 0;

    int playerHP = 0;
    int playerPow = 0;

    int peatones1Hp = 0;
    int peatones2Hp = 0;
    int peatones3Hp = 0;

    int peatones1Pow = 0;
    int peatones2Pow = 0;
    int peatones3Pow = 0;

    int BSPow = 2;
    int BSHp = 6;

    int numPeatones;

    bool cont = true;

    int cars = 0;

    Input input = Input::NONE;

    std::ifstream config("config.txt");

    if (config.is_open())
    {

        while (config >> mapX >> mapY >> playerHP >> playerPow >> peaje1 >> peaje2 >> numPeatonesLS >> maxDinerosLS >> peatones1Hp >> peatones1Pow >> numPeatonesSF >> maxDinerosSF >> peatones2Hp >> peatones2Pow >> 
            numPeatonesLV >> maxDinerosLV >> peatones3Hp >> peatones3Pow >> cars) {}

    }
    config.close();

    cj.setHp(playerHP);
    cj.setPow(playerPow);

    Map map(mapX, mapY, cars);
    numPeatones = numPeatonesLS + numPeatonesSF;

    Peaton* peatones = new Peaton[numPeatones];
    for (int i = 0; i < numPeatonesLS; i++)
    {
        peatones[i].initPeaton(City::LOSSANTOS, peatones1Hp, peatones1Pow);
    }
    for (int i = numPeatonesLS; i < numPeatones; i++)
    {
        peatones[i].initPeaton(City::SANFIERRO, peatones2Hp, peatones2Pow);
    }

    map.initMap(cj);

    for (int i = 0; i < numPeatones; i++)
    {
        peatones[i].spawn(map.getMap());
    }

    //-------GAMELOOP------

    while (cont)
    {

        if (state == gameState::START)
        {
            std::cout << "                 GTA                    " << std::endl;
            std::cout << "              ENTI CITY                " << std::endl;
            Sleep(3000);
            state = gameState::MENU;
        }

        system("CLS");

        //INPUT
        if (state == gameState::MENU)
        {
            if (GetAsyncKeyState(VK_UP))
            {
                menu = 0;
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
                menu = 1;
            }
            else if (GetAsyncKeyState(VK_SPACE))
            {
                if (menu == 0)
                {
                    for (int i = 0; i < numPeatonesLS; i++)
                    {
                        peatones[i].initPeaton(City::LOSSANTOS, peatones1Hp, peatones1Pow);
                    }
                    for (int i = numPeatonesLS; i < numPeatones; i++)
                    {
                        peatones[i].initPeaton(City::SANFIERRO, peatones2Hp, peatones2Pow);
                    }

                    map.initMap(cj);

                    for (int i = 0; i < mapY; i++)
                    {
                        for (int j = 0; j < mapX; j++)
                        {
                            if (map.getMap()[j][i] == Cell::CJ || map.getMap()[j][i] == Cell::BIGSMOKE)
                            {
                                map.getMap()[j][i] = Cell::VACIO;
                            }
                        }
                    }

                    cj.setHp(playerHP);
                    cj.setPow(playerPow);
                    cj.setDineros(0);
                    cj.setPosition(3, 3);
                    map.getMap()[cj.getPosition().x][cj.getPosition().y] = Cell::CJ;
                    cj.setDir(Direction::UP);
                    BS.initBigSmoke(BSHp, BSPow);
                    BS.spawnBS(map.getMap());
                    state = gameState::GAME;
                }
                else
                {
                    cont = false;
                }
            }
        }
        else
        {
            if (GetAsyncKeyState(VK_UP))
            {
                input = Input::UP;
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
                input = Input::DOWN;
            }
            else if (GetAsyncKeyState(VK_LEFT))
            {
                input = Input::LEFT;
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
                input = Input::RIGHT;
            }
            else if (GetAsyncKeyState(VK_SPACE))
            {
                cj.atack(map.getMap(), peatones, numPeatones, &BS, state);
            }
            else if (GetAsyncKeyState(VK_ESCAPE))
            {
                cont = false;

            }
            else if (GetAsyncKeyState('E'))
            {

                if (cj.isInCar())
                {
                    cj.getOffCar(map.getMap());
                }
                else
                {
                    cj.getInCar(map.getMap());
                }

            }
            else
            {
                input = Input::NONE;
            }
        }

        //UPDATE

        if (state == gameState::GAME)
        {
            for (int i = 0; i < numPeatones; i++)
            {
                peatones[i].move(map.getMap(), cj);
            }

            BS.moveBS(map.getMap(), cj);

            if (cj.isInCar())
            {
                cj.movePositionCar(input, map.getMap());
            }
            else
            {
                cj.movePosition(input, map.getMap());
            }

            cj.movePlayer(map.getMap(), input, maxDinerosLS, maxDinerosSF, peaje1, peaje2, state);

            if (cj.getHp() <= 0)
            {
                state = gameState::MENU;
            }
        }
        
        //RENDER

        if (state == gameState::MENU)
        {
            if (menu == 0)
            {
                std::cout << ">> START" << std::endl;
                std::cout << "   EXIT" << std::endl;
            }
            else
            {
                std::cout << "   START" << std::endl;
                std::cout << ">> EXIT" << std::endl;
            }
        }
        else if (state == gameState::GAME)
        {
            map.printMap(cj);

            std::cout << '\n' << "               DINEROS: " << cj.getDineros() << std::endl;
            std::cout << '\n' << "               VIDA: " << cj.getHp() << std::endl;
            std::cout << '\n' << "               VIDA BIG SMOKE: " << BS.getHpBS() << std::endl;
        }


        //FRAMECONTROL 
        Sleep(500);
    }
    

}

