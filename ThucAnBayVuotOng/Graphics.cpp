#include "game.h"
#include <iostream>

SDL_Window* Detail::window = NULL;
SDL_Renderer* Detail::renderer = NULL;
bool Detail::quit = false;
bool Detail::die = true;
int Detail::score = 0;
SDL_Event Detail::event;
SDL_Texture* Detail::PrimTexture = NULL;

Texture::Texture()
{
    texture = NULL;
}

Texture::~Texture()
{

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
    SDL_Rect rect = { x, y, Width, Height };

    if( clip != NULL )
    {
        rect.w = clip->w ;
        rect.h = clip->h ;
    }

    SDL_RenderCopyEx( Detail::renderer, texture, clip, &rect, angle, NULL, SDL_FLIP_NONE);
}

bool Texture::LoadImg(string path, double scale)
{
    free();
    SDL_Renderer* r = Detail::renderer;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface != NULL) {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 0, 255, 255));
        texture = SDL_CreateTextureFromSurface(r, load_surface);
        if(texture != NULL) {
            Width = (load_surface->w)*scale;
            Height = (load_surface->h)*scale;
        }

        SDL_FreeSurface(load_surface);
    }
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

    return texture != NULL;

}

void pos::getPos(const int x1, const int y1)
{
    x = x1;
    y = y1;
}
