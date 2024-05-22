#include "pipe.h"
#include <stdio.h>

vector<pos> posPipe;

bool pipe::initPipe()
{
    posPipe.clear();
    for (int i = 0; i < 2; i++)
    {
        pos temp;
        //Tạo ra 2 pipes mỗi cái cách nhau 220, và cái đầu tiên ở vị trí 700 khi bắt đầu chơi
        temp.getPos(700 + i * 220, (rand() % 206 - 343));//pipe cao 373 nên y random sẽ đc vị trí pipe từ 30 - 235 để đảm bảo vẫn chơi được
        posPipe.push_back(temp);
    }
    if (Texture::texture == NULL)
    {
        if (LoadImg("image/pipe.png", 1))
        {
            return true;
        }
    }
    return false;
}

void pipe::Free()
{
    free();
}

void pipe::render()
{
    //Render trôi
    for (int i = 0; i < 2; i++)
    {
        if (posPipe[i].x <= SCREEN_WIDTH && posPipe[i].x > -65)
            //Khi pipe chưa ra khỏi màn hình game
        {
            //Render pipe hướng xuống
            Render(posPipe[i].x, posPipe[i].y, 0, NULL, SDL_FLIP_NONE);
            //Render pipe hướng lên
            Render(posPipe[i].x, posPipe[i].y + 373 + PIPE_SPACE, 180, NULL, SDL_FLIP_NONE);
        }
    }
}

void pipe::velocity()
{
    //Xử lý trôi pipe
    if (!Detail::die)
    {
        for (int i = 0; i < 2; i++)
        {
            //khi 1 pipe ra khỏi màn hình
            if (posPipe[i].x < -65)
            {
                //random lại y của ống
                posPipe[i].y = (rand() % 206) - 343;
                //đưa vị trí pipe x đến sau pipe cuối cùng
                posPipe[i].x = posPipe[(i + 1) % 2].x + 220;
            }
            else
            {
                //Tốc độ di chuyển
                posPipe[i].x -= 3;
            }
        }
    }
}
