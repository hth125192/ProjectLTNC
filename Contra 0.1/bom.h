#ifndef BOM_H_INCLUDED
#define BOM_H_INCLUDED

#include "chung.h"
#include "anh.h"

class Bom : public Anh
{
public:
    Bom();
    ~Bom();

    bool LayBom(SDL_Renderer* screen);
    void XuLi();

    void CaiDi(const int& d) {di = d;}
    void CaiCheck(const bool& c) {check = c;}
    bool LayCheck() const {return check;}

private:
    int di;
    bool check;
};

#endif // BOM_H_INCLUDED
