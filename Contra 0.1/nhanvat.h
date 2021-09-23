#ifndef NHANVAT_H_INCLUDED
#define NHANVAT_H_INCLUDED

#include "chung.h"
#include "anh.h"
#include "dan.h"
#include "bom.h"
#include "mang.h"
#include "no.h"

class NhanVat : public Anh
{
public:
    NhanVat();
    ~NhanVat();

    enum Huong
    {
        DUNG = 0,
        PHAI = 1,
        TRAI = 2,
    };

    void LayNhanVat(std::string link, SDL_Renderer* screen);
    void ChonAnhNhanVat(SDL_Renderer* screen);
    void XuatNhanVat(SDL_Renderer* screen);
    void XuLi(SDL_Event event, SDL_Renderer* screen);
    void LayHieuUng();
    void DiChuyenNhanVat(MAP& map_, SDL_Renderer* screen);
    void CheckMap(MAP& map_, SDL_Renderer* screen);
    int Check(MAP& map_, const int y, const int x);
    void CuonMap(MAP& map_);
    void XuLiDan(SDL_Renderer* screen);
    void XoaDan(const int& i);
    void XuLiBom(SDL_Renderer* screen);
    void XoaBom(const int& i);
    void ThuThapTien(const int& i);
    void ThuThapKill(const int& i);
    void ThuThapMang();
    void MatMang(SDL_Renderer* screen);

    SDL_Rect LayKichThuocFrame();
    void CaiViTriMap(const int& x, const int& y){map_x = x; map_y = y;}
    void CaiTime(const int& t) {time = t;}
    int LayTien() const {return tien;}
    int LayKill() const {return kill;}
    int LayMang() const {return mang;}
    void CaiBangDan(std::vector<Dan*> bd) {bangdan = bd;}
    std::vector<Dan*> LayBangDan() const {return bangdan;}
    void CaiChuoiBom(std::vector<Bom*> cb) {chuoibom = cb;}
    std::vector<Bom*> LayChuoiBom() const {return chuoibom;}
    Mang somang;
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
    bool matdat;
    int huong;
    int time;
    int tien;
    int kill;
    int mang;
    SDL_Rect hieuung[FRAME];
    ACTION hd;
    std::vector<Dan*> bangdan;
    std::vector<Bom*> chuoibom;

};

#endif // NHANVAT_H_INCLUDED
