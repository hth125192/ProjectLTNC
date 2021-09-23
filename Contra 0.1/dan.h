#ifndef DAN_H_INCLUDED
#define DAN_H_INCLUDED

#include "chung.h"
#include "anh.h"

class Dan : public Anh
{
public:
    Dan();
    ~Dan();

    enum Huong
    {
        PHAI = 11,
        TRAI = 12,
    };

    enum Loai
    {
        TRON = 21,
        LASER = 22,
        LUA = 23,
    };

    bool LayDan(SDL_Renderer* screen);
    void XuLi();

    void CaiDi(const int& d) {di = d;}
    void CaiCheck(const bool& c) {check = c;}
    bool LayCheck() const {return check;}
    void CaiHuong(const int& h) {huong = h;}
    void CaiLoai(const int& l) {loai = l;}

private:
    int di;
    bool check;
    int huong;
    int loai;
};

#endif // DAN_H_INCLUDED
