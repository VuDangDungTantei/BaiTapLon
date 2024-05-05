#include "game.h"
#include "Graphics.h"
#include <iostream>

void game::takeInput()
{
    while(SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            userInput.Type = input::QUIT;
            quit = true;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.key.repeat == 0)
        {
            userInput.Type = input::PLAY;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE && event.key.repeat == 0)
        {
            userInput.Type = input::PAUSE;
        }
    }
}

game::game()
{
    initGraphic();
    pipe.init();
    land.init();
    sound.init();
}

game::~game()
{
    paimon.Free();
    pipe.Free();
    land.Free();
    sound.Free();
    free();
    releaseGraphic();
}

void game::releaseGraphic()
{
    SDL_DestroyWindow( window );
    window = NULL;
    SDL_DestroyRenderer( renderer );
    renderer = NULL;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool game::initGraphic()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        window = SDL_CreateWindow( "ThucAnBayVuotOng", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

        if( window == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);

                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

void game::display()
{
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void game::renderScoreSmall()
{
    string s = to_string(score);
    signed char len = s.length();
    Texture image;

    for (int i = len - 1; i >= 0; i--)
    {
        signed char number = s[i] - '0';
        switch(number)
        {
        case 1:
            image.Load("image/S1.png", scaleNumberS);
            break;
        case 2:
            image.Load("image/S2.png", scaleNumberS);
            break;
        case 3:
            image.Load("image/S3.png", scaleNumberS);
            break;
        case 4:
            image.Load("image/S4.png", scaleNumberS);
            break;
        case 5:
            image.Load("image/S5.png", scaleNumberS);
            break;
        case 6:
            image.Load("image/S6.png", scaleNumberS);
            break;
        case 7:
            image.Load("image/S7.png", scaleNumberS);
            break;
        case 8:
            image.Load("image/S8.png", scaleNumberS);
            break;
        case 9:
            image.Load("image/S9.png", scaleNumberS);
            break;
        default:
            image.Load("image/S0.png", scaleNumberS);
            break;
        }
        image.Render(260 - image.getWidth() * (len - i - 1) * 0.75 - 5 * (len - i - 1), 268);
    }
    image.free();
}

void game::renderScoreLarge()
{
    string s = to_string(score);
    signed char len = s.length();
    Texture image;

    for (signed char i = 0; i < len; i++)
    {
        signed char number = s[i] - '0';
        switch(number)
        {
        case 0:
            image.Load("image/0.png", 1);
            break;
        case 1:
            image.Load("image/1.png", 1);
            break;
        case 2:
            image.Load("image/2.png", 1);
            break;
        case 3:
            image.Load("image/3.png", 1);
            break;
        case 4:
            image.Load("image/4.png", 1);
            break;
        case 5:
            image.Load("image/5.png", 1);
            break;
        case 6:
            image.Load("image/6.png", 1);
            break;
        case 7:
            image.Load("image/7.png", 1);
            break;
        case 8:
            image.Load("image/8.png", 1);
            break;
        default:
            image.Load("image/9.png", 1);
            break;
        }
        image.Render((SCREEN_WIDTH - (image.getWidth() * len + (len - 1) * 10)) / 2 + (i + 30) * i, 100);
    }
    image.free();
}

void game::renderBestScore()
{
    ifstream fileIn("Score/bestScore.txt");
    fileIn >> bestScore;
    ofstream fileOut("Score/bestScore.txt", ios::trunc);

    if (score > bestScore)
    {
        bestScore = score;
    }
    string s = to_string(bestScore);
    signed char len = s.length();
    Texture image;

    for (signed char i = len-1; i >= 0; i--)
    {
        signed char number = s[i] - '0';
        switch(number)
        {
        case 1:
            image.Load("image/S1.png", scaleNumberS);
            break;
        case 2:
            image.Load("image/S2.png", scaleNumberS);
            break;
        case 3:
            image.Load("image/S3.png", scaleNumberS);
            break;
        case 4:
            image.Load("image/S4.png", scaleNumberS);
            break;
        case 5:
            image.Load("image/S5.png", scaleNumberS);
            break;
        case 6:
            image.Load("image/S6.png", scaleNumberS);
            break;
        case 7:
            image.Load("image/S7.png", scaleNumberS);
            break;
        case 8:
            image.Load("image/S8.png", scaleNumberS);
            break;
        case 9:
            image.Load("image/S9.png", scaleNumberS);
            break;
        default:
            image.Load("image/S0.png", scaleNumberS);
            break;
        }
        image.Render(260 - image.getWidth()*(len-i-1)*0.75 - 5*(len - i - 1), 315);
    }
    image.free();

    fileOut << bestScore;
    fileIn.close();
    fileOut.close();
}

void game::rendergameMenu()
{
    Texture image;
    image.Load("image/gameMenu.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180);
    image.free();
}

void game::renderBackground()
{
    Texture image;
    image.Load("image/background.png", 1);
    image.Render(0, 0);
    image.free();
}

void game::renderBackgroundNight()
{
    Texture image;
    image.Load("image/background-night.png", 1);
    image.Render(0, 0);
    image.free();
}

void game::renderLand()
{
    Texture image;
    image.Load("image/land.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, SCREEN_HEIGHT- image.getHeight());
    image.free();
}

void game::resume()
{
    Texture image;
    image.Load("image/resume.png", 1);
    image.Render(SCREEN_WIDTH - 50, 20);
    image.free();
}

void game::pause()
{
    Texture image;
    image.Load("image/pause.png", 1);
    image.Render(SCREEN_WIDTH - 50, 20);
    image.free();
}

void game::renderPauseTab()
{
    Texture image;
    image.Load("image/pauseTab.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 230);
    image.free();
}

void game::lightTheme()
{
    Texture image;
    image.Load("image/paimon.png", 0.8);
    image.Render(105, 315);
    image.free();
}

void game::nextButton()
{
    Texture image;
    image.Load("image/nextRight.png", 1);
    image.Render(149, 322);
    image.Load("image/nextLeft.png", 1);
    image.Render(88, 322);
    image.free();
}

void game::renderGameOver()
{
    Texture image;
    image.Load("image/gameOver.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 150);
    image.free();
}

void game::replay()
{
    Texture image;
    image.Load("image/replay.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 380);
    image.free();
}

bool game::checkReplay()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > (SCREEN_WIDTH - 100)/2 && x < (SCREEN_WIDTH + 100) / 2 && y > 380 && y < 380 + 60)
    {
        return true;
    }
    return false;
}

void game::Restart()
{
    die = false;
    score = 0;
    paimon.resetTime();
}
