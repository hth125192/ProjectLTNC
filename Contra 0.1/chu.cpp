#include "chu.h"

Chu::Chu()
{
    mau = {255,255,255};
    texture = NULL;
}

Chu::~Chu()
{
    Free();
}

bool Chu::LayChu(TTF_Font* font, SDL_Renderer* screen)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, noidung.c_str(), mau);
    if (surface)
    {
        texture = SDL_CreateTextureFromSurface(screen, surface);
        w = surface->w;
        h = surface->h;

        SDL_FreeSurface(surface);
    }
    return texture != NULL;
}

void Chu::CaiMau(Uint8 r, Uint8 g, Uint8 b)
{
    mau = {r,g,b};
}

void Chu::CaiMau(int mau_)
{
    switch (mau_)
    {
        case TRANG:
        {
            mau = {255,255,255};
            break;
        }
        case DO:
        {
            mau = {255,0,0};
            break;
        }
        case XANHLA:
        {
            mau = {0,255,0};
            break;
        }
        case XANHDUONG:
        {
            mau = {0,0,255};
            break;
        }
        case DEN:
        {
            mau = {0,0,0};
            break;
        }
    }
}

void Chu::XuatChu(SDL_Renderer* screen,int x, int y, SDL_Rect* hieuung, double goc, SDL_Point* point, SDL_RendererFlip flip)
{
    SDL_Rect cacthongso = {x,y,w,h};
    if (hieuung)
    {
        cacthongso.w = hieuung->w;
        cacthongso.h = hieuung->h;
    }
    SDL_RenderCopyEx(screen, texture, hieuung, &cacthongso, goc, point, flip);
}

void Chu::Free()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}
