#ifndef FPS_H_INCLUDED
#define FPS_H_INCLUDED

#include "chung.h"

class Fps
{
public:
    Fps();
    ~Fps(){}

    void BatDau();
    int LayT();

private:
    int t;
};

#endif // FPS_H_INCLUDED
