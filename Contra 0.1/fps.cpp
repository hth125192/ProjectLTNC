#include "fps.h"

Fps::Fps()
{
    t = 0;
}

void Fps::BatDau()
{
    t = SDL_GetTicks();
}

int Fps::LayT()
{
    return SDL_GetTicks() - t;
}
