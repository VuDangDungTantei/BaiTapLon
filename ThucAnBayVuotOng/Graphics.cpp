#include "game.h"
#include <iostream>

bool Texture::quit = false;
bool Texture::die = true;
int Texture::score = 0;
SDL_Window* Texture::window = NULL;
SDL_Renderer* Texture::renderer = NULL;
SDL_Event Texture::event;

Texture::Texture()
{
    texture = NULL;
}

int Texture::getWidth()
{
    return Width;
}

int Texture::getHeight()
{
    return Height;
}

void Texture::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        Width = 0;
        Height = 0;
    }
}

void Texture::Render(int x, int y, int angle, SDL_Rect* clip, SDL_RendererFlip flip)
{
    SDL_Rect render = { x, y, Width, Height };

    if( clip != NULL )
    {
        render.w = clip->w ;
        render.h = clip->h ;
    }

    SDL_RenderCopyEx( renderer, texture, clip, &render, angle, NULL, SDL_FLIP_NONE);
}

bool Texture::Load(string path, double scale)
{
    free();

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 255, 255 ) );

        texture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( texture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            Width = (loadedSurface->w) * scale;
            Height = (loadedSurface->h) * scale;
        }

        SDL_FreeSurface( loadedSurface );
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    return texture != NULL;

}

bool Texture::isNULL()
{
    if (texture == NULL) return true;
    return false;
}

void position::getPos(const int x, const int y)
{
    this->x = x;
    this->y = y;
}
