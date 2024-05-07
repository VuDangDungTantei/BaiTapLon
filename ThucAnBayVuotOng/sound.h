#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>
#include <string>
#include "Graphics.h"

using namespace std;

class sound:Texture
{
public:
    bool initSound();

    void Free();

    void playFlyup();

    void playHit();

    void playgetPoint();

    void renderSound();

    bool checkSound();

private:
    const int POS_X = 107;
    const int POS_Y = 267;
    bool isPlay = 0;
    Mix_Chunk* getpoint = NULL;
    Mix_Chunk* flyup = NULL;
    Mix_Chunk* hit = NULL;
    Mix_Chunk* drop = NULL;
    SDL_Rect Mute ;
    SDL_Rect Active ;
};

#endif
