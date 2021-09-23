#ifndef QUAI_H_INCLUDED
#define QUAI_H_INCLUDED

#include "chung.h"
#include "anh.h"
#include "dan.h"

class Quai : public Anh
{
public:
    Quai();
    ~Quai();

    enum Loai
    {
        DUNGIM = 41,
        DICHUYEN = 42,
    };

    void LayQuai(std::string link, SDL_Renderer* screen);
    void XuatQuai(SDL_Renderer* screen);
    void LayHieuUng();
    void DiChuyenQuai(MAP& map_);
    void CheckMap(MAP& map_);
    void QuaiDiChuyen(SDL_Renderer* screen);
    void NapDan(Dan* dan, SDL_Renderer* screen);
    void BanDan(SDL_Renderer* screen);
    void XoaDan(const int& i);

    SDL_Rect LayKichThuocFrame();
    void CaiViTriMap(const int& x, const int& y) {map_x = x; map_y = y;}
    void CaiViTriX(const float& x) {vitri_x = x;}
    void CaiViTriY(const float& y) {vitri_y = y;}
    void CaiLoai(const int& l) {loai = l;}
    void CaiACTION() {hd.trai = 1;}
    void CaiTraiPhai(const int& t, const int& p) {trai = t, phai = p;}
    void CaiBangDan(std::vector<Dan*> bd) {bangdan = bd;}
    std::vector<Dan*> LayBangDan() const {return bangdan;}

private:
    float di_x;
    float di_y;
    float vitri_x;
    float vitri_y;
    int map_x;
    int map_y;
    int frame;
    int frame_w;
    int frame_h;
    int loai;
    int trai;
    int phai;
    SDL_Rect hieuung[FRAME];
    ACTION hd;
    std::vector<Dan*> bangdan;
};

#endif // QUAI_H_INCLUDED
