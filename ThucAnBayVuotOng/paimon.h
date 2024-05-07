#ifndef PAIMON_H
#define PAIMON_H

#include "Graphics.h"
#include "pipe.h"
#include "def.h"

using namespace std;

class paimon:Texture
{
public:
    bool init(bool LPaimon);

    void render();

    void Free();

    void resetTime()
    {
        time = 0;
    }

    void fall();

    void update(int pileWidth, int pileHeight);
private:
    int angle, time, x0;
    int ahead = 0;
    string saved_path = "";
    position posPaimon;
};

#endif
