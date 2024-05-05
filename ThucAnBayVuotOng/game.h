#ifndef GAME_
#define GAME_
#include "paimon.h"
#include "pipe.h"
#include "land.h"
#include "sound.h"
#include <bits/stdc++.h>

using namespace std;

class game:Texture
{
public:
    struct input
    {
        enum type { QUIT, PLAY, NONE, PAUSE};
        type Type;
    };
    input userInput;
    paimon paimon;
    pipe pipe;
    sound sound;
    land land;
public:
    game();

    ~game();

    bool initGraphic();

    bool isQuit()
    {
        return quit;
    }

    bool isDie()
    {
        return die;
    }

    int getPipeWidth()
    {
        return pipe.width();
    }

    int getPipeHeight()
    {
        return pipe.height();
    }

    void takeInput();

    void display();

    void releaseGraphic();

    void renderScoreSmall();

    void renderScoreLarge();

    void renderBestScore();

    void rendergameMenu();

    void renderBackground();

    void renderBackgroundNight();

    void renderLand();

    void resume();

    void pause();

    void renderPauseTab();

    void lightTheme();

    void nextButton();

    void renderGameOver();

    void replay();

    bool checkReplay();

    void Restart();

private:
    const double scaleNumberS = 0.75;
    int bestScore;
};

#endif
