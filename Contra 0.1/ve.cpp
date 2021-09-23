#include "ve.h"

void Ve::VeHCN(const FORMAT& kt, const COLOR& mau, SDL_Renderer* screen)
{
    SDL_Rect kthcn = {kt.x_, kt.y_, kt.w_, kt.h_};
    SDL_SetRenderDrawColor(screen, mau.r_, mau.g_, mau.b_, 255);
    SDL_RenderFillRect(screen, &kthcn);
}

void Ve::VeVien(const FORMAT& kt, const COLOR& mau, SDL_Renderer* screen)
{
    SDL_Rect ktvien = {kt.x_, kt.y_, kt.w_, kt.h_};
    SDL_SetRenderDrawColor(screen, mau.r_, mau.g_, mau.b_, 255);
    SDL_RenderDrawRect(screen, &ktvien);
}
