#include "paimon.h"
#include <stdio.h>
#include <iostream>

void paimon::initPaimon()
{
    string paimon_path = "image/paimon.png";
    if (texture != NULL)
    {
        posPaimon.getPos(75, SCREEN_HEIGHT / 2 - 10);
        next = 0;
        angle = 0;
    }
    if (texture == NULL)
    {
        LoadImg(paimon_path.c_str(), 1);
    }
}

void paimon::Free()
{
    free();
}

void paimon::renderP()
{
    Render(posPaimon.x, posPaimon.y, angle);
}

void paimon::fall()
{
    if (Detail::die && posPaimon.y < SCREEN_HEIGHT - LAND_HEIGHT - PAIMON_HEIGHT)
    {
        if (time == 0)
        {
            now = posPaimon.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            posPaimon.y = now + time * time * 0.18 - 7.3 * time;
            time++;
        }
    }
    else return;
}

void paimon::update(int W, int H)
{
    if (!Detail::die)
    {
        if (time == 0)
        {
            now = posPaimon.y;
            angle = 0;
        }
        if (time >= 0)
        {
            posPaimon.y = now + time * time * 0.18 - 7.3 * time;
            time++;
        }

        if ((posPaimon.x + getWidth() > posPipe[next].x) && (posPaimon.x < posPipe[next].x + W) &&
                (posPaimon.y < posPipe[next].y + H || posPaimon.y  + getHeight() > posPipe[next].y + H + 170))
        {
            Detail::die = true;
        }
        else if (posPaimon.x > posPipe[next].x + W)
        {
            next = (next + 1) % 4;
            Detail::score++;
        }

        if (posPaimon.y > SCREEN_HEIGHT - LAND_HEIGHT - PAIMON_HEIGHT || posPaimon.y < 0)
        {
            Detail::die = true;
        }
    }
}
