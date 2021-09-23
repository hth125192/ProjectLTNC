#include "no.h"

No::No()
{
    frame = 0;
    frame_w = 0;
    frame_h = 0;
}

No::~No()
{
    Free();
}

void No::LayVuNo(std::string link, SDL_Renderer* screen)
{
    Free();
    if (Anh::LayAnh(link, screen))
    {
        frame_w = kichthuoc.w/FRAME;
        frame_h = kichthuoc.h;
    }
}

void No::LayHieuUng()
{
    if (frame_w>0 && frame_h>0)
        for (int i=0; i < FRAME; i++)
        {
            hieuung[i].x = i*frame_w;
            hieuung[i].y = 0;
            hieuung[i].w = frame_w;
            hieuung[i].h = frame_h;
        }
}

void No::XuatVuNo(SDL_Renderer* screen)
{
    SDL_Rect* hieuunghientai = &hieuung[frame];
    if (hieuunghientai)
    {
        SDL_Rect cacthongso = {kichthuoc.x, kichthuoc.y, hieuunghientai->w, hieuunghientai->h};
        SDL_RenderCopy(screen, texture, hieuunghientai, &cacthongso);
    }
}
