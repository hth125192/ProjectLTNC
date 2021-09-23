#include "bom.h"

Bom::Bom()
{
    di = 0;
    check = false;
}

Bom::~Bom()
{
    Free();
}

bool Bom::LayBom(SDL_Renderer* screen)
{
    return LayAnh("anh/bom.png", screen);
}

void Bom::XuLi()
{
    kichthuoc.y += di;
    if (kichthuoc.y > SCR_H) check = false;
}
