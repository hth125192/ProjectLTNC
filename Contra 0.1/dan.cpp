#include "dan.h"

Dan::Dan()
{
    di = 0;
    check = false;
}

Dan::~Dan()
{
    Free();
}

bool Dan::LayDan(SDL_Renderer* screen)
{
    switch (loai)
    {
        case TRON:
            return LayAnh("anh/dantron.png", screen);
        case LASER:
            return LayAnh("anh/danlaser.png", screen);
        case LUA:
            return LayAnh("anh/danlua.png", screen);
    }
}

void Dan::XuLi()
{
    switch (huong)
    {
        case PHAI:
        {
            kichthuoc.x += di;
            if (kichthuoc.x > SCR_W) check = false;
            break;
        }
        case TRAI:
        {
            kichthuoc.x -= di;
            if (kichthuoc.x < 0) check = false;
            break;
        }
    }
}
