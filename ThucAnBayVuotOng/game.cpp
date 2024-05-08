#include "game.h"
#include "Graphics.h"
#include <iostream>

void game::takeInput()
{
    SDL_Event &e = Detail::event;
    while(SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            userInput.Type = input::QUIT;
            Detail::quit = true;
        }
        else if ((e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP && e.key.repeat == 0))
        {
            userInput.Type = input::PLAY;
        }
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE && e.key.repeat == 0)
        {
            userInput.Type = input::PAUSE;
        }
    }
}

game::game()
{
    initGraphic();
    pipe.initPipe();
    land.initLand();
    sound.initSound();
}

game::~game()
{
    paimon.Free();
    pipe.Free();
    land.Free();
    sound.Free();
    free();
    freeGraphic();
}

void game::freeGraphic()
{
    SDL_DestroyWindow( Detail::window );
    Detail::window = NULL;
    SDL_DestroyRenderer( Detail::renderer );
    Detail::renderer = NULL;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool game::initGraphic() {
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    Detail::window = SDL_CreateWindow("ThucAnBayVuotOng", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(Detail::window == NULL) success = false;

    else {
        Detail::renderer = SDL_CreateRenderer(Detail::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(Detail::renderer == NULL) success = false;
        else {
            SDL_SetRenderDrawColor(Detail::renderer, 255, 255, 255, 255);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags)) {
                success = false;
            }
        }
    }

    return success;
}

void game::presentScene()
{
    SDL_RenderPresent(Detail::renderer);
    SDL_RenderClear(Detail::renderer);
}

void game::renderScoreSmall()
{
    string s = to_string(Detail::score);
    int len = s.length();
    Texture image;

    for (int i = len - 1; i >= 0; i--)
    {
        int number = s[i] - '0';
        switch(number)
        {
        case 1:
            image.LoadImg("image/S1.png", 0.75);
            break;
        case 2:
            image.LoadImg("image/S2.png", 0.75);
            break;
        case 3:
            image.LoadImg("image/S3.png", 0.75);
            break;
        case 4:
            image.LoadImg("image/S4.png", 0.75);
            break;
        case 5:
            image.LoadImg("image/S5.png", 0.75);
            break;
        case 6:
            image.LoadImg("image/S6.png", 0.75);
            break;
        case 7:
            image.LoadImg("image/S7.png", 0.75);
            break;
        case 8:
            image.LoadImg("image/S8.png", 0.75);
            break;
        case 9:
            image.LoadImg("image/S9.png", 0.75);
            break;
        default:
            image.LoadImg("image/S0.png", 0.75);
            break;
        }
        image.Render(260 - image.getWidth() * (len - i - 1) * 0.75 - 5 * (len - i - 1), 268);
    }
    image.free();
}

void game::renderScoreLarge()
{
    string s = to_string(Detail::score);
    int len = s.length();
    Texture image;

    for (int i = 0; i < len; i++)
    {
        int number = s[i] - '0';
        switch(number)
        {
        case 0:
            image.LoadImg("image/0.png", 1);
            break;
        case 1:
            image.LoadImg("image/1.png", 1);
            break;
        case 2:
            image.LoadImg("image/2.png", 1);
            break;
        case 3:
            image.LoadImg("image/3.png", 1);
            break;
        case 4:
            image.LoadImg("image/4.png", 1);
            break;
        case 5:
            image.LoadImg("image/5.png", 1);
            break;
        case 6:
            image.LoadImg("image/6.png", 1);
            break;
        case 7:
            image.LoadImg("image/7.png", 1);
            break;
        case 8:
            image.LoadImg("image/8.png", 1);
            break;
        default:
            image.LoadImg("image/9.png", 1);
            break;
        }
        image.Render((SCREEN_WIDTH - (image.getWidth() * len + (len - 1) * 10)) / 2 + (i + 30) * i, 100);
    }
    image.free();
}

void game::renderBestScore()
{
    freopen("Score/bestScore.txt", "r", stdin);
    cin >> bestScore;
    freopen("Score/bestScore.txt", "w", stdout);

    if (Detail::score > bestScore)
    {
        bestScore = Detail::score;
    }
    string s = to_string(bestScore);
    int len = s.length();
    Texture image;

    for (int i = len-1; i >= 0; i--)
    {
        int number = s[i] - '0';
        switch(number)
        {
        case 1:
            image.LoadImg("image/S1.png", 0.75);
            break;
        case 2:
            image.LoadImg("image/S2.png", 0.75);
            break;
        case 3:
            image.LoadImg("image/S3.png", 0.75);
            break;
        case 4:
            image.LoadImg("image/S4.png", 0.75);
            break;
        case 5:
            image.LoadImg("image/S5.png", 0.75);
            break;
        case 6:
            image.LoadImg("image/S6.png", 0.75);
            break;
        case 7:
            image.LoadImg("image/S7.png", 0.75);
            break;
        case 8:
            image.LoadImg("image/S8.png", 0.75);
            break;
        case 9:
            image.LoadImg("image/S9.png", 0.75);
            break;
        default:
            image.LoadImg("image/S0.png", 0.75);
            break;
        }
        image.Render(260 - image.getWidth()*(len-i-1)*0.75 - 5*(len - i - 1), 315);
    }
    image.free();

    cout << bestScore;
}

void game::rendergameMenu()
{
    Texture image;
    image.LoadImg("image/gameMenu.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180);
    image.free();
}

void game::renderBackground()
{
    Texture image;
    image.LoadImg("image/background.png", 1);
    image.Render(0, 0);
    image.free();
}

void game::renderLand()
{
    Texture image;
    image.LoadImg("image/land.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, SCREEN_HEIGHT- image.getHeight());
    image.free();
}

void game::resume()
{
    Texture image;
    image.LoadImg("image/resume.png", 1);
    image.Render(SCREEN_WIDTH - 50, 20);
    image.free();
}

void game::pause()
{
    Texture image;
    image.LoadImg("image/pause.png", 1);
    image.Render(SCREEN_WIDTH - 50, 20);
    image.free();
}

void game::renderPauseTab()
{
    Texture image;
    image.LoadImg("image/pauseTab.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 230);
    image.free();
}

void game::character()
{
    Texture image;
    image.LoadImg("image/paimon.png", 0.8);
    image.Render(105, 315);
    image.free();
}

void game::renderGameOver()
{
    Texture image;
    image.LoadImg("image/gameOver.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 150);
    image.free();
}

void game::replay()
{
    Texture image;
    image.LoadImg("image/replay.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 380);
    image.free();
}

bool game::checkReplay()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > 125 && x < 225 && y > 380 && y < 440) return true;
    return false;
}

void game::Restart()
{
    Detail::die = false;
    Detail::score = 0;
    paimon.resetTime();
}
