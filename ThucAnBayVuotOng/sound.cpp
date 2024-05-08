#include "sound.h"
#include <stdio.h>
#include <iostream>
#include <string>

bool sound::initSound()
{
    string flyup_path = "sound/sfx_flyup.wav";
    string hit_path = "sound/sfx_hit.wav";
    string getPoint_path = "sound/sfx_point.wav";
    string Changesound_path = "image/sound.png";

    bool success = true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        getpoint = Mix_LoadWAV(getPoint_path.c_str());
        flyup = Mix_LoadWAV(flyup_path.c_str());
        hit = Mix_LoadWAV(hit_path.c_str());
        if (getpoint == NULL || flyup == NULL || hit == NULL)
        {
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
        if (!LoadImg(Changesound_path, 1))
        {
            return false;
        }

        Play = {0, 0, 32, 24};
        Mute = {0, 24, 32, 24};
        isPlay = true;
    }
    return success;
}

void sound::Free()
{
    free();

    Mix_FreeChunk(flyup);
    flyup = NULL;
    Mix_FreeChunk(hit);
    hit = NULL;

    Mix_Quit();
}

void sound::playgetPoint()
{
    if(isPlay) Mix_PlayChannel(-1, getpoint, 0);
}

void sound::playFlyup()
{
    if (isPlay) Mix_PlayChannel( -1, flyup, 0 );
}

void sound::playHit()
{
    if (isPlay) Mix_PlayChannel(-1, hit, 0);
}

void sound::renderSound()
{
    if (isPlay) Render(107, 267, 0, &Play);
    else Render(107, 267, 0, &Mute);
}

bool sound::checkSound()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > 107 && x < 139 && y > 267 && y < 313)
    {
        isPlay = !isPlay;
        return true;
    }
    return false;
}
