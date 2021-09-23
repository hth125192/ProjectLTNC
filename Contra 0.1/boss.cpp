#include "boss.h"

Boss::Boss()
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
    mang = 10;
}

Boss::~Boss()
{
    Free();
}

void Boss::LayBoss(std::string link, SDL_Renderer* screen)
{
    if (Anh::LayAnh(link, screen))
    {
        frame_w = kichthuoc.w/FRAMEM;
        frame_h = kichthuoc.h;
    }
}

void Boss::LayHieuUng()
{
    if (frame_w>0 && frame_h>0)
        for (int i=0; i < FRAMEM; i++)
        {
            hieuung[i].x = i*frame_w;
            hieuung[i].y = 0;
            hieuung[i].w = frame_w;
            hieuung[i].h = frame_h;
        }
}

void Boss::XuatBoss(SDL_Renderer* screen)
{
    frame++;
    if (frame >= FRAMEM) frame = 0;

    kichthuoc.x = vitri_x - map_x;
    kichthuoc.y = vitri_y - map_y;

    SDL_Rect* hieuunghientai = &hieuung[frame];
    SDL_Rect cacthongso = {kichthuoc.x, kichthuoc.y, frame_w, frame_h};
    SDL_RenderCopy(screen, texture, hieuunghientai, &cacthongso);
}

void Boss::DiChuyenBoss(MAP& map_)
{
    di_x = 0;
    di_y += ROI;
    if (di_y > ROIM) di_y = ROIM;

    CheckMap(map_);
}

void Boss::CheckMap(MAP& map_)
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

void Boss::NapDan(SDL_Renderer* screen)
{
    Dan* dan = new Dan();
    dan->CaiLoai(Dan::LUA);
    if (dan->LayDan(screen))
    {
        dan->CaiCheck(true);
        dan->CaiHuong(Dan::TRAI);
        dan->CaiKichThuoc(kichthuoc.x - 50, kichthuoc.y + frame_h - 30);
        dan->CaiDi(15);
        bangdan.push_back(dan);
    }
}

void Boss::BanDan(SDL_Renderer* screen)
{
    if (frame == 18) NapDan(screen);
    for (int i=0; i < bangdan.size(); i++)
    {
        Dan* dan = bangdan.at(i);
        if (dan)
        {
            if (dan->LayCheck())
            {
                if (kichthuoc.x + frame_w - dan->LayKichThuoc().x < 700)
                {
                    dan->XuLi();
                    dan->XuatAnh(screen);
                }
                else
                {
                    dan->CaiCheck(false);
                    dan->Free();
                    bangdan.erase(bangdan.begin() + i);
                }
            }
            else
            {
                dan->CaiCheck(true);
                dan->CaiKichThuoc(kichthuoc.x - 50, kichthuoc.y + frame_h - 30);
            }
        }
    }
}

void Boss::MatMang(SDL_Renderer* screen)
{
    Mix_PlayChannel(-1, Mix_LoadWAV("nhac/noquai.wav"), 0);
    no.LayVuNo("anh/noquai.png", screen);
    no.LayHieuUng();
    mang--;
    for (int i=0; i < FRAME; i++)
    {
        no.CaiFrame(i);
        if (mang)
        {
            no.CaiKichThuoc(kichthuoc.x - no.LayFrameW()*0.4, kichthuoc.y + frame_h*0.6);
            no.XuatVuNo(screen);
            SDL_RenderPresent(screen);
        }
        else
        {
            no.CaiKichThuoc(kichthuoc.x, kichthuoc.y + frame_h*0.35);
            no.XuatVuNo(screen);
            no.CaiKichThuoc(kichthuoc.x + frame_w*0.05, kichthuoc.y + frame_h*0.75);
            no.XuatVuNo(screen);
            no.CaiKichThuoc(kichthuoc.x + frame_w*0.2, kichthuoc.y + frame_h*0.2);
            no.XuatVuNo(screen);
            no.CaiKichThuoc(kichthuoc.x + frame_w*0.3, kichthuoc.y + frame_h*0.55);
            no.XuatVuNo(screen);
            no.CaiKichThuoc(kichthuoc.x + frame_w*0.4, kichthuoc.y + frame_h*0.85);
            no.XuatVuNo(screen);
            no.CaiKichThuoc(kichthuoc.x + frame_w*0.55, kichthuoc.y + frame_h*0.25);
            no.XuatVuNo(screen);
            no.CaiKichThuoc(kichthuoc.x + frame_w*0.65, kichthuoc.y + frame_h*0.7);
            no.XuatVuNo(screen);
            SDL_Delay(1000/MFPS);
            SDL_RenderPresent(screen);
        }
    }
}

SDL_Rect Boss::LayKichThuocFrame()
{
    SDL_Rect kt;
    kt.x = kichthuoc.x;
    kt.y = kichthuoc.y;
    kt.w = frame_w;
    kt.h = frame_h;
    return kt;
}
