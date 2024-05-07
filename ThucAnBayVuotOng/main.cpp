#include "game.h"
#include "Graphics.h"
#include <time.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

const int FPS = 60;
const int frameDelay = 1000 / FPS;
int soundGetPoint = Detail::score;

using namespace std;

int main(int argc, char** argv)
{
    Uint32 frameStart;
    int frameTime;
    game g;
    bool isMenu = 0;
    bool isPause = 0;
    bool isSound = 1;
    bool LPaimon = 0;

    while(!g.isQuit())
    {
        frameStart = SDL_GetTicks();

        if (g.isDie())
        {
            if (isMenu)
            {
                g.sound.playHit();
                g.paimon.render();
            }
            g.userInput.Type = game::input::NONE;
            while(g.isDie() && !g.isQuit())
            {
                g.takeInput();
                if (isMenu == 1 && g.userInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        isMenu = 0;
                    }
                    g.userInput.Type = game::input::NONE;
                }
                g.renderBackground();
                g.pipe.render();
                g.land.render();
                if (isMenu)
                {
                    g.paimon.render();
                    g.paimon.fall();
                    g.renderGameOver();
                    g.renderScoreSmall();
                    g.renderBestScore();
                    g.replay();
                }
                else
                {
                    g.pipe.initPipe();
                    g.paimon.init(LPaimon);
                    g.paimon.render();
                    g.rendergameMenu();
                    if (g.userInput.Type == game::input::PLAY)
                    {
                        g.Restart();
                        isMenu = 1;
                        g.userInput.Type = game::input::NONE;
                    }
                    g.land.update();
                }
                g.display();
            }
            g.pipe.initPipe();
        }
        else
        {
            g.takeInput();

            if (g.userInput.Type == game::input::PAUSE)
            {
                isPause = abs(1 - isPause);
                g.userInput.Type = game::input::NONE;
            }
            if (isPause == 0 && g.userInput.Type == game::input::PLAY)
            {
                if (isSound) g.sound.playFlyup();
                g.paimon.resetTime();
                g.userInput.Type = game::input::NONE;
            }

            g.renderBackground();
            g.pipe.render();
            g.land.render();
            g.paimon.render();
            g.renderScoreLarge();

            if (!isPause)
            {
                if(soundGetPoint != Detail::score && Detail::score != 0)
                {
                    g.sound.playgetPoint();
                    soundGetPoint = Detail::score;
                }
                g.paimon.update(g.getPipeWidth(), g.getPipeHeight());
                g.pipe.update();
                g.land.update();
                g.pause();
            }
            else
            {
                g.resume();
                g.renderPauseTab();
                g.renderScoreSmall();
                g.renderBestScore();
                g.replay();
                g.sound.renderSound();
                if (g.userInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        isPause = 0;
                    }
                    else if (g.sound.checkSound())
                    {
                        isSound = abs(1 - isSound);
                    }
                    g.userInput.Type = game::input::NONE;
                }
            }
            g.display();
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    return 0;
}
