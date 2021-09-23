#ifndef MANG_H_INCLUDED
#define MANG_H_INCLUDED

#include "chung.h"
#include "anh.h"

class Mang : public Anh
{
public:
    Mang();
    ~Mang();

    void ThemViTri(const int& x);
    void Lay(SDL_Renderer* screen);
    void Xuat(SDL_Renderer* screen);
    void Tang();
    void Mat();

    void CaiNum(const int& n) {num = n;}

private:
    int num;
    std::vector<int> dsvitri;
};

#endif // MANG_H_INCLUDED
