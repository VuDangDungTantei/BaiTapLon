#include "paimon.h"
#include <stdio.h>
#include <iostream>

void paimon::initPaimon()
{
    string paimon_path = "image/paimon.png";
    if (texture != NULL)
    {
        //Vị trí xuất hiện
        posPaimon.getPos(75, SCREEN_HEIGHT / 2 - 10);
        next = 0;
        angle = 0;
    }
    if (texture == NULL)
    {
        LoadImg(paimon_path.c_str(), 1);
    }
}

void paimon::Free()
{
    free();
}

void paimon::renderP()
{
    Render(posPaimon.x, posPaimon.y, angle);
}

void paimon::fall()
{
    //Xử lý khi chết
    if (Detail::die && posPaimon.y < SCREEN_HEIGHT - LAND_HEIGHT - PAIMON_HEIGHT)
    {
        //Lấy vị trí hiện tại
        if (time == 0)
        {
            now = posPaimon.y;
        }
        //Góc xoay nhân vật khi rơi
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }
        //Tốc độ rơi
        if (time >= 0)
        {
            posPaimon.y = now + time*time*0.15 - 7.3 * time;
            time++;
        }
    }
    else return;
}

void paimon::PlayAndDie(int W, int H)
{
    //Xử lý khi chơi
    if (!Detail::die)
    {
        if (time == 0)
        {
            now = posPaimon.y;
            angle = 30;
        }
        //Quay xuống khi rơi
        else if (angle < 70 && time > 30)
        {
            angle += 6;
        }
        //Quay lên khi chơi
        else if (angle > 0 && time < 30)
        {
            angle -= 3;
        }
        if (time >= 0)
        {
            //Xử lý nhảy: 40 đầu thì bay lên trong thời gian còn lại thì rơi xuống
            posPaimon.y = now + time * time * 0.18 - 7.3 * time;
            time++;
        }
        //Xử lý va chạm W là chiều rộng, H là chiều cao của ống
        if ((posPaimon.x + 50 > posPipe[next].x) && (posPaimon.x < posPipe[next].x + W) &&
                (posPaimon.y < posPipe[next].y + H || posPaimon.y + 50 > posPipe[next].y + H + 170))
        {
            Detail::die = true;
        }
        //Xử lý điểm
        else if (posPaimon.x > posPipe[next].x + W)
        {
            next = (next + 1) % 2;
            Detail::score++;
        }

        if (posPaimon.y > SCREEN_HEIGHT - LAND_HEIGHT - PAIMON_HEIGHT || posPaimon.y < 0)
        {
            Detail::die = true;
        }
    }
}
