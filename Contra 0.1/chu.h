#ifndef CHU_H_INCLUDED
#define CHU_H_INCLUDED

#include "chung.h"

class Chu
{
public:
    Chu();
    ~Chu();

    enum Mau
    {
        TRANG = 50,
        DO = 51,
        XANHLA = 52,
        XANHDUONG = 53,
        DEN = 54,
    };

    bool LayChu(TTF_Font* font, SDL_Renderer* screen);
    void CaiMau(Uint8 r, Uint8 g, Uint8 b);
    void CaiMau(int mau_);
    void XuatChu(SDL_Renderer* screen, int x, int y, SDL_Rect* hieuung = NULL, double goc = 0.0, SDL_Point* point = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Free();

    int LayW() const {return w;}
    int LayH() const {return h;}
    void CaiNoiDung(const std::string& nd) {noidung = nd;}
    std::string LayNoiDung() const {return noidung;}

private:
    int w;
    int h;
    SDL_Texture* texture;
    SDL_Color mau;
    std::string noidung;
};

#endif // CHU_H_INCLUDED
