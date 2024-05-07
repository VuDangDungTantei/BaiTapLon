#ifndef PIPE_H
#define PIPE_H

#include "Graphics.h"
#include <iostream>
#include <vector>

using namespace std;

class pipe:Texture
{
private:
    const int randMin = -370 + 30;//-340
    const int randMax = SCREEN_HEIGHT - LAND_HEIGHT - 370 - PIPE_DISTANCE - 30;//-135
public:
    bool initPipe();

    void Free();

    void render();

    void update();

    int width()
    {
        return getWidth();
    }

    int height()
    {
        return getHeight();
    }
};

extern vector<position> posPipe;

#endif
