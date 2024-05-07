#ifndef DEF_H
#define DEF_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>

#define SCREEN_HEIGHT 625
#define SCREEN_WIDTH 350
const int PIPE_SPACE = 175;
const int TOTAL_PIPE = 4;
const int PIPE_DISTANCE = 234;
const int LAND_HEIGHT = 140;
const int PAIMON_WIDTH = 50;
const int PAIMON_HEIGHT = 64;


struct Detail
{
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool quit;
    static bool die;
    static int score;
};

#endif // DEF_H
