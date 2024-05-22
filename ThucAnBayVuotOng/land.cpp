#include "land.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

bool land::initLand()
{
    //Render vị trí đầu là ở bên phải màn hình
    posLand.getPos(SCREEN_WIDTH, SCREEN_HEIGHT - LAND_HEIGHT);
    string land_path = "image/land.png";
    if (texture == NULL)
    {
        if (LoadImg(land_path.c_str(), 1)) return true;
        else return false;
    }
}

void land::Free()
{
    free();
}

void land::render()
{
    //Land trôi
    if(posLand.x < 0) posLand.x = SCREEN_WIDTH;
    Render(posLand.x, posLand.y);
    Render(posLand.x - SCREEN_WIDTH, posLand.y);
}

void land::velocity()
{
    //Tốc độ land trôi
    posLand.x -= 3;
}
