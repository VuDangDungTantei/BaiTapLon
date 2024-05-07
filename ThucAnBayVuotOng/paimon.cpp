#include "paimon.h"
#include <stdio.h>
#include <iostream>

bool paimon::init(bool LPaimon)
{
    string paimon_path = "image/paimon.png";
    if (saved_path == paimon_path)
    {
        posPaimon.getPos(75, SCREEN_HEIGHT / 2 - 10);
        ahead = 0;
        angle = 0;
    }
    if (texture == NULL || saved_path != paimon_path)
    {
        saved_path = paimon_path;
        if (LoadImg(paimon_path.c_str(), 1))
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    return false;
}

void paimon::Free()
{
    free();
}

void paimon::render()
{
    Render(posPaimon.x, posPaimon.y, angle);
}

void paimon::fall()
{
    if (Detail::die && posPaimon.y < SCREEN_HEIGHT - LAND_HEIGHT - PAIMON_HEIGHT - 5)
    {
        if (time == 0)
        {
            x0 = posPaimon.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            posPaimon.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }
    }
    else return;
}

void paimon::update(int pipeWidth, int pipeHeight)
{
    if (!Detail::die)
    {
        if (time == 0)
        {
            x0 = posPaimon.y;
            angle = 0;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            posPaimon.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }

        if ( (posPaimon.x + getWidth() > posPipe[ahead].x + 5) && (posPaimon.x + 5 < posPipe[ahead].x + pipeWidth) &&
                (posPaimon.y + 5 < posPipe[ahead].y + pipeHeight || posPaimon.y  + getHeight() > posPipe[ahead].y + pipeHeight + PIPE_SPACE + 5) )
        {
            Detail::die = true;
        }
        else if (posPaimon.x > posPipe[ahead].x + pipeWidth )
        {
            ahead = ( ahead + 1 ) % TOTAL_PIPE;
            Detail::score++;
        }

        if (posPaimon.y > SCREEN_HEIGHT - LAND_HEIGHT - PAIMON_HEIGHT - 5 || posPaimon.y < - 10 )
        {
            Detail::die = true;
        }
    }
}
