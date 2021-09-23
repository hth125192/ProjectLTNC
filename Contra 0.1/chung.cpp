#include "chung.h"

bool CheckVaCham(const SDL_Rect& kichthuoc1, const SDL_Rect& kichthuoc2)
{
    int trai1 = kichthuoc1.x;
    int phai1 = kichthuoc1.x + kichthuoc1.w;
    int tren1 = kichthuoc1.y;
    int duoi1 = kichthuoc1.y + kichthuoc1.h;

    int trai2 = kichthuoc2.x;
    int phai2 = kichthuoc2.x + kichthuoc2.w;
    int tren2 = kichthuoc2.y;
    int duoi2 = kichthuoc2.y + kichthuoc2.h;

    if (trai1 > trai2 && trai1 < phai2)
        if (tren1 > tren2 && tren1 < duoi2) return true;
    if (trai1 > trai2 && trai1 < phai2)
        if (duoi1 > tren2 && duoi1 < duoi2) return true;
    if (phai1 > trai2 && phai1 < phai2)
        if (tren1 > tren2 && tren1 < duoi2) return true;
    if (phai1 > trai2 && phai1 < phai2)
        if (duoi1 > tren2 && duoi1 < duoi2) return true;

    if (trai2 > trai1 && trai2 < phai1)
        if (tren2 > tren1 && tren2 < duoi1) return true;
    if (trai2 > trai1 && trai2 < phai1)
        if (duoi2 > tren1 && duoi2 < duoi1) return true;
    if (phai2 > trai1 && phai2 < phai1)
        if (tren2 > tren1 && tren2 < duoi1) return true;
    if (phai2 > trai1 && phai2 < phai1)
        if (duoi2 > tren1 && duoi2 < duoi1) return true;

    if (tren1 == tren2 && phai1 == phai2 && duoi1 == duoi2) return true;

    return false;
}
