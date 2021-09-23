#ifndef ANH_H_INCLUDED
#define ANH_H_INCLUDED

#include "chung.h"

class Anh
{
public:
    Anh();
    ~Anh();

    virtual bool LayAnh(std::string link, SDL_Renderer* screen);
    void XuatAnh(SDL_Renderer* screen, const SDL_Rect* hieuung = NULL);
    void Free();

    SDL_Texture* LayTexture() const {return texture;}
    void CaiKichThuoc(const int& x, const int& y) {kichthuoc.x = x, kichthuoc.y = y;}
    SDL_Rect LayKichThuoc() const {return kichthuoc;}

protected:
    SDL_Texture* texture;
    SDL_Rect kichthuoc;
};

#endif // ANH_H_INCLUDED
