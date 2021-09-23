#include "mang.h"

Mang::Mang()
{
    num = 3;
}

Mang::~Mang()
{
    Free();
}

void Mang::ThemViTri(const int& x)
{
    dsvitri.push_back(x);
}

void Mang::Lay(SDL_Renderer* screen)
{
    LayAnh("anh/mang.png", screen);
    if (dsvitri.size() > 0) dsvitri.clear();
    for (int i=0; i<3; i++) ThemViTri(20+40*i);
}

void Mang::Xuat(SDL_Renderer* screen)
{
    for (int i=0; i < dsvitri.size(); i++)
    {
        kichthuoc.x = dsvitri.at(i);
        kichthuoc.y = 0;
        XuatAnh(screen);
    }
}

void Mang::Tang()
{
    num++;
    dsvitri.push_back(dsvitri.back() + 40);
}

void Mang::Mat()
{
    num--;
    dsvitri.pop_back();
}
