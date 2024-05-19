#include "pipe.h"
#include <stdio.h>

vector<pos> posPipe;

bool pipe::initPipe()
{
    posPipe.clear();
    for (int i = 0; i < 4; i++)
    {
        pos temp;
        temp.getPos(700 + i * 220, (rand() % 206 - 343));
        posPipe.push_back(temp);
    }
    if (Texture::texture == NULL)
    {
        if (LoadImg("image/pipe.png", 1))
        {
            return true;
        }
    }
    return false;
}

void pipe::Free()
{
    free();
}

void pipe::render()
{
    for (int i = 0; i < 4; i++)
    {
        if (posPipe[i].x <= SCREEN_WIDTH && posPipe[i].x > -65)
        {
            Render(posPipe[i].x, posPipe[i].y, 0, NULL, SDL_FLIP_NONE);
            Render(posPipe[i].x, posPipe[i].y + 373 + PIPE_SPACE, 180, NULL, SDL_FLIP_NONE);
        }
    }
}

void pipe::update()
{
    if (!Detail::die)
    {
        for (int i = 0; i < 4; i++)
        {
            if (posPipe[i].x < -65)
            {
                posPipe[i].y = (rand() % 206) - 343;
                posPipe[i].x = posPipe[(i + 3) % 4].x + 220;
            }
            else
            {
                posPipe[i].x -= 3;
            }
        }
    }
}
