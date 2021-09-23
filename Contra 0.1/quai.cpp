#include "quai.h"

Quai::Quai()
{
    di_x = 0;
    di_y = 0;
    vitri_x = 0;
    vitri_y = 0;
    map_x = 0;
    map_y = 0;
    frame = 0;
    frame_w = 0;
    frame_h = 0;
    loai = DUNGIM;
    trai = 0;
    phai = 0;
    hd.trai = 0;
    hd.phai = 0;
    hd.nhay = 0;
}

Quai::~Quai()
{
    Free();
}

void Quai::LayQuai(std::string link, SDL_Renderer* screen)
{
    if (Anh::LayAnh(link, screen))
    {
        frame_w = kichthuoc.w/FRAME;
        frame_h = kichthuoc.h;
    }
}

void Quai::LayHieuUng()
{
    if (frame_w>0 && frame_h>0)
        for (int i=0; i < FRAME; i++)
        {
            hieuung[i].x = i*frame_w;
            hieuung[i].y = 0;
            hieuung[i].w = frame_w;
            hieuung[i].h = frame_h;
        }
}

void Quai::XuatQuai(SDL_Renderer* screen)
{
    frame++;
    if (frame >= FRAME) frame = 0;

    kichthuoc.x = vitri_x - map_x;
    kichthuoc.y = vitri_y - map_y;

    SDL_Rect* hieuunghientai = &hieuung[frame];
    SDL_Rect cacthongso = {kichthuoc.x, kichthuoc.y, frame_w, frame_h};
    SDL_RenderCopy(screen, texture, hieuunghientai, &cacthongso);
}

void Quai::DiChuyenQuai(MAP& map_)
{
    di_x = 0;
    di_y += ROI;
    if (di_y > ROIM) di_y = ROIM;

    if (hd.phai) di_x += QUAI_DI;
    else if (hd.trai) di_x -= QUAI_DI;

    CheckMap(map_);
}

void Quai::CheckMap(MAP& map_)
{
    int x1 = vitri_x/O_SIZE;
    int x2 = (vitri_x + frame_w - 1)/O_SIZE;
    int y = (vitri_y + di_y + frame_h - 1)/O_SIZE;

    if (map_.o[y][x1] >= 1 && map_.o[y][x1] <= 18 || map_.o[y][x2] >= 1 && map_.o[y][x2] <= 18)
    {
        vitri_y = y*O_SIZE - frame_h - 1;
        di_y = 0;
    }
    vitri_x += di_x;
    vitri_y += di_y;
}

void Quai::QuaiDiChuyen(SDL_Renderer* screen)
{
    if (loai == DICHUYEN)
    {
        if (vitri_x > phai)
        {
            hd.trai = 1;
            hd.phai = 0;
            LayQuai("anh/quaitrai.png", screen);
        }
        else if (vitri_x < trai)
        {
            hd.trai = 0;
            hd.phai = 1;
            LayQuai("anh/quaiphai.png", screen);
        }
    }
}

void Quai::NapDan(Dan* dan, SDL_Renderer* screen)
{
    if (dan)
    {
        dan->CaiLoai(Dan::LASER);
        if (dan->LayDan(screen))
        {
            dan->CaiCheck(true);
            dan->CaiHuong(Dan::TRAI);
            dan->CaiKichThuoc(kichthuoc.x + 10, kichthuoc.y + 10);
            dan->CaiDi(12);
            bangdan.push_back(dan);
        }
    }
}

void Quai::BanDan(SDL_Renderer* screen)
{
    for (int i=0; i < bangdan.size(); i++)
    {
        Dan* dan = bangdan.at(i);
        if (dan)
        {
            if (dan->LayCheck())
            {
                if (kichthuoc.x + frame_w - dan->LayKichThuoc().x < 300)
                {
                    dan->XuLi();
                    dan->XuatAnh(screen);
                }
                else dan->CaiCheck(false);
            }
            else
            {
                dan->CaiCheck(true);
                dan->CaiKichThuoc(kichthuoc.x + 10, kichthuoc.y + 10);
            }
        }
    }
}

void Quai::XoaDan(const int& i)
{
    if (bangdan.size() > 0 && i < bangdan.size())
    {
        Dan* dan = bangdan.at(i);
        bangdan.erase(bangdan.begin() + i);
        if (dan)
        {
            delete dan;
            dan = NULL;
        }
    }
}

SDL_Rect Quai::LayKichThuocFrame()
{
    SDL_Rect kt;
    kt.x = kichthuoc.x;
    kt.y = kichthuoc.y;
    kt.w = frame_w;
    kt.h = frame_h;
    return kt;
}
