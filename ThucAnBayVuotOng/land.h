#ifndef LAND_H
#define LAND_H

#include "Graphics.h"
#include <vector>

using namespace std;

class land : Texture
{
public:
    bool initLand();

    void Free();

    void render();

    void velocity();

private:
    pos posLand;
};

#endif
