#ifndef PIPE_H
#define PIPE_H

#include "Graphics.h"
#include <iostream>
#include <vector>

using namespace std;

struct pipe:Texture
{
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

extern vector<pos> posPipe;

#endif
