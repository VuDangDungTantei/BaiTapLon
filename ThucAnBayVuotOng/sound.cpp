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
        if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        getpoint = Mix_LoadWAV( getPoint_path.c_str() );
        if ( getpoint == NULL )
        {
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        flyup = Mix_LoadWAV( flyup_path.c_str() );
        if ( flyup == NULL )
        {
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        hit = Mix_LoadWAV( hit_path.c_str() );
        if (hit == NULL)
        {
            printf( "Failed to load chord! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        if (!LoadImg(Changesound_path, 1))
        {
            return false;
        }

        Active.x = 0;
        Active.y = 0;
        Active.w = getWidth();
        Active.h = getHeight() / 2;
        Mute.x = 0;
        Mute.y = getHeight() / 2;
        Mute.w = getWidth();
        Mute.h = getHeight() / 2;
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
    if(isPlay)
    {
        Mix_PlayChannel(-1, getpoint, 0);
    }
}

void sound::playFlyup()
{
    if (isPlay)
    {
        Mix_PlayChannel( -1, flyup, 0 );
    }
}

void sound::playHit()
{
    if (isPlay)
    {
        Mix_PlayChannel(-1, hit, 0);
    }
}

void sound::renderSound()
{
    if (isPlay)
    {
        Render(POS_X, POS_Y, 0, &Active);
    }
    else
    {
        Render(POS_X, POS_Y, 0, &Mute);
    }
}

bool sound::checkSound()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > POS_X && x < POS_X + getWidth() &&
            y > POS_Y && y < POS_Y + getHeight())
    {
        isPlay = !isPlay;
        return true;
    }
    return false;
}
