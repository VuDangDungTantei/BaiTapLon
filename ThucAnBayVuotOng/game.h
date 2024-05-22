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
        enum type {QUIT, PLAY, NONE, PAUSE};
        type Type;
    };
    input userInput;
    paimon paimon;
    pipe pipe;
    sound sound;
    land land;

    game();

    ~game();

    bool initGraphic();

    bool isQuit()
    {
        return Detail::quit;
    }

    bool isDie()
    {
        return Detail::die;
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

    void presentScene();

    void freeGraphic();

    void renderScoreOver();

    void renderScoreGame();

    void BestScore();

    void rendergameMenu();

    void renderBackground();

    void renderLand();

    void resume();

    void pause();

    void renderPauseTab();

    void character();

    void renderGameOver();

    void renderReplay();

    bool checkReplay();

    void Restart();

private:
    int bestScore;
};

#endif
