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

int main(int argc, char* argv[])
{
    game flp;
    bool isMenu = false;
    bool isPause = false;
    bool isSound = true;
    while(!flp.isQuit())
    {
        Uint32 frameStart = SDL_GetTicks();
        if (flp.isDie())
        {
            if (isMenu)
            {
                flp.sound.playHit();
            }
            while(flp.isDie() && !flp.isQuit())
            {
                flp.takeInput();
                if (isMenu && flp.userInput.Type == game::input::PLAY)
                {
                    if (flp.checkReplay())
                    {
                        isMenu = false;
                    }
                    flp.userInput.Type = game::input::NONE;
                }
                flp.renderBackground();
                flp.pipe.render();
                flp.land.render();
                if (isMenu)
                {
                    flp.paimon.renderP();
                    flp.paimon.fall();
                    flp.renderGameOver();
                    flp.renderScoreSmall();
                    flp.renderBestScore();
                    flp.renderReplay();
                }
                else
                {
                    flp.pipe.initPipe();
                    flp.paimon.initPaimon();
                    flp.paimon.renderP();
                    flp.rendergameMenu();
                    if (flp.userInput.Type == game::input::PLAY)
                    {
                        flp.Restart();
                        isMenu = true;
                    }
                    flp.land.update();
                }
                flp.presentScene();
            }
            flp.pipe.initPipe();
        }
        else
        {
            flp.takeInput();

            if (flp.userInput.Type == game::input::PAUSE)
            {
                isPause = !isPause;
                flp.userInput.Type = game::input::NONE;
            }
            if (isPause == false && flp.userInput.Type == game::input::PLAY)
            {
                if (isSound) flp.sound.playFlyup();
                flp.paimon.resetTime();
                flp.userInput.Type = game::input::NONE;
            }

            flp.renderBackground();
            flp.pipe.render();
            flp.land.render();
            flp.paimon.renderP();
            flp.renderScoreLarge();

            if (!isPause)
            {
                if(soundGetPoint != Detail::score && Detail::score != 0)
                {
                    flp.sound.playgetPoint();
                    soundGetPoint = Detail::score;
                }
                flp.paimon.update(flp.getPipeWidth(), flp.getPipeHeight());
                flp.pipe.update();
                flp.land.update();
                flp.pause();
            }
            else
            {
                flp.resume();
                flp.renderPauseTab();
                flp.renderScoreSmall();
                flp.renderBestScore();
                flp.renderReplay();
                flp.sound.renderSound();
                if (flp.userInput.Type == game::input::PLAY)
                {
                    if (flp.checkReplay())
                    {
                        isPause = false;
                    }
                    else if (flp.sound.checkSound())
                    {
                        isSound = !isSound;
                    }
                    flp.userInput.Type = game::input::NONE;
                }
            }
            flp.presentScene();
        }

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    return 0;
}
