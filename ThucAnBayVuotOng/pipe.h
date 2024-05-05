#ifndef PIPE_H
#define PIPE_H

#include "Graphics.h"
#include <iostream>
#include <vector>

using namespace std;

extern vector<position> posPipe;

class pipe:Texture
{
private:
    const short int randMin = -373 + 30;
    const short int randMax = SCREEN_HEIGHT - LAND_HEIGHT - 373 - PIPE_DISTANCE - 30;
public:
    bool init();

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

#endif
