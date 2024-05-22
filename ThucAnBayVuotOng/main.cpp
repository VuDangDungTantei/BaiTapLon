#include "game.h"
#include "Graphics.h"
#include <time.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//Chỉnh FPS
const int FPS = 60;
const int frameDelay = 1000 / FPS;
int soundGetPoint = Detail::score;

using namespace std;

int main(int argc, char* argv[])
{
    game flp;
    bool isOverMenu = false;
    bool isPause = false;
    bool isSound = true;
    while(!flp.isQuit())
    {
        Uint32 frameStart = SDL_GetTicks();
        //Xử lý khi chết
        if (flp.isDie())
        {
            if (isOverMenu)
            {
                //chạy nhạc khi hiện menu game over
                flp.sound.playHit();
            }
            while(flp.isDie() && !flp.isQuit())
            {
                flp.takeInput();
                if (isOverMenu && flp.userInput.Type == game::input::PLAY)
                {
                    //Replay
                    if (flp.checkReplay())
                    {
                        isOverMenu = false;
                    }
                    flp.userInput.Type = game::input::NONE;
                }
                //Hình ảnh ban đầu
                flp.renderBackground();
                flp.pipe.render();
                flp.land.render();
                //Hình ảnh khi game over
                if (isOverMenu)
                {
                    flp.paimon.renderP();
                    flp.paimon.fall();
                    flp.renderGameOver();
                    flp.renderScoreOver();
                    flp.BestScore();
                    flp.renderReplay();
                }
                else
                    //Hình ảnh khi replay
                {
                    flp.pipe.initPipe();
                    flp.paimon.initPaimon();
                    flp.paimon.renderP();
                    flp.rendergameMenu();
                    if (flp.userInput.Type == game::input::PLAY)
                    {
                        flp.Restart();
                        isOverMenu = true;
                    }
                    flp.land.velocity();
                }
                flp.presentScene();
            }
        }
        else
        {
            //Xử lý khi chơi
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
            //Hình ảnh khi chơi
            flp.renderBackground();
            flp.pipe.render();
            flp.land.render();
            flp.paimon.renderP();
            flp.renderScoreGame();
            //Xử lý điểm, âm thanh, va chạm
            if (!isPause)
            {
                if(soundGetPoint != Detail::score && Detail::score != 0)
                {
                    flp.sound.playgetPoint();
                    soundGetPoint = Detail::score;
                }
                flp.paimon.PlayAndDie(flp.getPipeWidth(), flp.getPipeHeight());
                flp.pipe.velocity();
                flp.land.velocity();
                flp.pause();
            }
            else
            {
                flp.resume();
                flp.renderPauseTab();
                flp.renderScoreOver();
                flp.BestScore();
                flp.renderReplay();
                flp.sound.renderSoundimage();
                if (flp.userInput.Type == game::input::PLAY)
                {
                    if (flp.checkReplay())
                    {
                        isPause = false;
                    }
                    else if (flp.sound.changeSound())
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
