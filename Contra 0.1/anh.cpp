#include "anh.h"

Anh::Anh()
{
    texture = NULL;
    kichthuoc.x = 0;
    kichthuoc.y = 0;
    kichthuoc.w = 0;
    kichthuoc.h = 0;
}

Anh::~Anh()
{
    Free();
}

bool Anh::LayAnh(std::string link, SDL_Renderer* screen)
{
    Free();
    SDL_Surface* surface = IMG_Load(link.c_str());
    if (surface)
    {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, KEY_R, KEY_G, KEY_B));
        texture = SDL_CreateTextureFromSurface(screen, surface);
        if (texture)
        {
            kichthuoc.w = surface->w;
            kichthuoc.h = surface->h;
        }
        SDL_FreeSurface(surface);
    }
    return texture != NULL;
}

void Anh::XuatAnh(SDL_Renderer* screen, const SDL_Rect* hieuung)
{
    SDL_Rect cacthongso = {kichthuoc.x, kichthuoc.y, kichthuoc.w, kichthuoc.h};
    SDL_RenderCopy(screen, texture, hieuung, &cacthongso);
}

void Anh::Free()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        kichthuoc.w = 0;
        kichthuoc.h = 0;
    }
}
