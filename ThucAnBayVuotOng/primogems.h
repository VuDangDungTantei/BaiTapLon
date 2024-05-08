#ifndef PRI_H
#define PRI_H

#include "Graphics.h"
#include <iostream>
#include <vector>

extern vector <position> posPrim;

struct primogems:Texture
{
    bool initPrimogems();

    void Free();

    void render();

    void update();
};

#endif // PRI_H
