#include "game.h"
#include "Graphics.h"
#include <time.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

const int FPS = 144;
const int frameDelay = 1000 / FPS;
int soundGetPoint = Detail::score;

using namespace std;

int main(int argc, char* argv[])
{
    game g;
    bool isMenu = false;
    bool isPause = false;
    bool isSound = true;

    while(!g.isQuit())
    {
       Uint32 frameStart = SDL_GetTicks();

        if (g.isDie())
        {
            if (isMenu)
            {
                g.sound.playHit();
            }
            while(g.isDie() && !g.isQuit())
            {
                g.takeInput();
                if (isMenu == true && g.userInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        isMenu = false;
                    }
                    g.userInput.Type = game::input::NONE;
                }
                g.renderBackground();
                g.pipe.render();
                g.land.render();
                if (isMenu)
                {
                    g.paimon.renderP();
                    g.paimon.fall();
                    g.renderGameOver();
                    g.renderScoreSmall();
                    g.renderBestScore();
                    g.replay();
                }
                else
                {
                    g.pipe.initPipe();
                    g.paimon.initPaimon();
                    g.paimon.renderP();
                    g.rendergameMenu();
                    if (g.userInput.Type == game::input::PLAY)
                    {
                        g.Restart();
                        isMenu = true;
                    }
                    g.land.update();
                }
                g.presentScene();
            }
            g.pipe.initPipe();
        }
        else
        {
            g.takeInput();

            if (g.userInput.Type == game::input::PAUSE)
            {
                isPause = !isPause;
                g.userInput.Type = game::input::NONE;
            }
            if (isPause == false && g.userInput.Type == game::input::PLAY)
            {
                if (isSound) g.sound.playFlyup();
                g.paimon.resetTime();
                g.userInput.Type = game::input::NONE;
            }

            g.renderBackground();
            g.pipe.render();
            g.land.render();
            g.paimon.renderP();
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
                        isPause = false;
                    }
                    else if (g.sound.checkSound())
                    {
                        isSound = !isSound;
                    }
                    g.userInput.Type = game::input::NONE;
                }
            }
            g.presentScene();
        }

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    return 0;
}
