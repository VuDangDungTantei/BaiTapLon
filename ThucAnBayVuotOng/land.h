#ifndef LAND_H
#define LAND_H

#include "Graphics.h"
#include <vector>

using namespace std;

class land : Texture
{
public:
    bool init();

    void Free();

    void render();

    void update();

private:
    position posLand;
};

#endif
