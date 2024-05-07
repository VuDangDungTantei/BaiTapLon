#include "pipe.h"
#include "stdio.h"

vector<position> posPipe;

bool pipe::initPipe()
{
    posPipe.clear();
    for (int i = 0; i < TOTAL_PIPE; i++)
    {
        position temp;
        temp.getPos(SCREEN_WIDTH + i * PIPE_DISTANCE + 350, (rand() % (randMax - randMin + 1)) + randMin);
        posPipe.push_back(temp);
    }
    if (Texture::texture == NULL)
    {
        if (LoadImg( "image/pipe.png", 1))
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
    for (int i = 0; i < TOTAL_PIPE; i++)
    {
        if (posPipe[i].x <= SCREEN_WIDTH && posPipe[i].x > -getWidth())
        {
            Render(posPipe[i].x, posPipe[i].y, 0, NULL, SDL_FLIP_NONE);
        }
        Render(posPipe[i].x, posPipe[i].y + getHeight() + PIPE_SPACE, 180, NULL, SDL_FLIP_NONE);
    }
}

void pipe::update()
{
    if (!Detail::die)
    {
        for (int i = 0; i < TOTAL_PIPE; i++)
        {
            if (posPipe[i].x < - getWidth())
            {
                posPipe[i].y = (rand() % (randMax - randMin + 1)) + randMin;
                posPipe[i].x = posPipe[(i + TOTAL_PIPE - 1) % TOTAL_PIPE].x + PIPE_DISTANCE;
            }
            else
            {
                posPipe[i].x -= 3;
            }
        }
    }
}
