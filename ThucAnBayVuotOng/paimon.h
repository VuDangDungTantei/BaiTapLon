#ifndef PAIMON_H
#define PAIMON_H

#include "Graphics.h"
#include "pipe.h"
#include "def.h"

using namespace std;

class paimon:Texture
{
public:

    void initPaimon();

    void renderP();

    void Free();

    void resetTime()
    {
        time = 0;
    }

    void fall();

    void PlayAndDie(int W, int H);
private:
    int angle, time, now;
    int next = 0;
    pos posPaimon;
};

#endif
