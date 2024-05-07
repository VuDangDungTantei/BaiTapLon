#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "def.h"

using namespace std;

struct position
{
    int x, y, angle, state;
    void getPos(const int x, const int y);
};

class Texture
{
public:
    Texture();

    ~Texture();

    bool LoadImg(string path, double scale);

    int getWidth();
    int getHeight();

    void free();
    void Render(int x, int y, int angle = 0, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
public:
    SDL_Texture* texture;

    int Width;
    int Height;
};
#endif
