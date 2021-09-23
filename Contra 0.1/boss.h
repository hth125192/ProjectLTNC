#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include "chung.h"
#include "anh.h"
#include "dan.h"
#include "no.h"

class Boss : public Anh
{
public:
    Boss();
    ~Boss();

    void LayBoss(std::string link, SDL_Renderer* screen);
    void XuatBoss(SDL_Renderer* screen);
    void LayHieuUng();
    void DiChuyenBoss(MAP& map_);
    void CheckMap(MAP& map_);
    void NapDan(SDL_Renderer* screen);
    void BanDan(SDL_Renderer* screen);
    void MatMang(SDL_Renderer* screen);

    SDL_Rect LayKichThuocFrame();
    void CaiViTriMap(const int& x, const int& y) {map_x = x; map_y = y;}
    void CaiViTriX(const float& x) {vitri_x = x;}
    void CaiViTriY(const float& y) {vitri_y = y;}
    int LayMang() const {return mang;}
    void CaiBangDan(std::vector<Dan*> bd) {bangdan = bd;}
    std::vector<Dan*> LayBangDan() const {return bangdan;}
    No no;

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
    int mang;
    SDL_Rect hieuung[FRAMEM];
    std::vector<Dan*> bangdan;
};

#endif // BOSS_H_INCLUDED
