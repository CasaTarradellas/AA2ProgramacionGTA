
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Walker.h"
#include "Player.h"
#include "Map.h"


int main()
{
    srand(time(NULL));

    //SETUP

    Player cj;
    cj.setPosition(3, 3);
    cj.setDir(Direction::UP);
    
    int numPeatonesLS = 0;
    int numPeatonesSF = 0;
    int numPeatonesLV = 0;
    int peaje1 = 0;
    int peaje2 = 0;
    int maxDinerosLS = 0;
    int maxDinerosSF = 0;
    int maxDinerosLV = 0;

    int playerHP = 0;
    int playerPow = 0;

    int peatones1Hp = 0;
    int peatones2Hp = 0;
    int peatones3Hp = 0;

    int peatones1Pow = 0;
    int peatones2Pow = 0;
    int peatones3Pow = 0;

    int numPeatones;

    bool cont = true;

    Input input = Input::NONE;



    std::ifstream config("config.txt");



    if (config.is_open())
    {

        while (config >> mapX >> mapY >> playerHP >> playerPow >> peaje1 >> peaje2 >> numPeatonesLS >> maxDinerosLS >> peatones1Hp >> peatones1Pow >> numPeatonesSF >> maxDinerosSF >> peatones2Hp >> peatones2Pow >> 
            numPeatonesLV >> maxDinerosLV >> peatones3Hp >> peatones3Pow) {}

    }
    config.close();

    cj.setHp(playerHP);
    cj.setPow(playerPow);

    Map map(mapX, mapY);
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
        system("CLS");

        //INPUT

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
            cj.atack(map.getMap(), peatones, numPeatones);
        }
        else if (GetAsyncKeyState(VK_ESCAPE))
        {
            cont = false;
        }
        else
        {
            input = Input::NONE;
        }

        //UPDATE

        for (int i = 0; i < numPeatones; i++)
        {
            peatones[i].move(map.getMap());
        }

        cj.movePosition(input, map.getMap());
        cj.movePlayer(map.getMap(), input, maxDinerosLS, maxDinerosSF);

        

        //RENDER

        map.printMap(cj);

        std::cout << '\n' << "                                   DINEROS: " << cj.getDineros() << std::endl;

        //FRAMECONTROL 
        Sleep(500);
    }
    

}

