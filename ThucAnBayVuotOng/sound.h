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

    bool changeSound();

    void renderSoundimage();

    void playFlyup();

    void playHit();

    void playgetPoint();


private:
    bool isPlay = false;
    Mix_Chunk* hit = NULL;
    Mix_Chunk* drop = NULL;
    Mix_Chunk* getpoint = NULL;
    Mix_Chunk* flyup = NULL;
    SDL_Rect Mute, Play;
};

#endif
