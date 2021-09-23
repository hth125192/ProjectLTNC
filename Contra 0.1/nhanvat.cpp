#include "nhanvat.h"

NhanVat::NhanVat()
{
    di_x = 0;
    di_y = 0;
    vitri_x = O_SIZE;
    vitri_y = O_SIZE;
    map_x = 0;
    map_y = 0;
    frame = 0;
    frame_w = 0;
    frame_h = 0;
    matdat = false;
    huong = DUNG;
    time = 0;
    tien = 0;
    kill = 0;
    mang = 3;
    hd.trai = 0;
    hd.phai = 0;
    hd.nhay = 0;
}

NhanVat::~NhanVat()
{
    Free();
}

void NhanVat::LayNhanVat(std::string link, SDL_Renderer* screen)
{
    Free();
    if (Anh::LayAnh(link, screen))
    {
        frame_w = kichthuoc.w/FRAME;
        frame_h = kichthuoc.h;
    }
}

void NhanVat::LayHieuUng()
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

void NhanVat::ChonAnhNhanVat(SDL_Renderer* screen)
{
    if (matdat)
    {
        if (huong == TRAI) LayAnh("anh/nvtrai.png", screen);
        else LayAnh("anh/nvphai.png", screen);
    }
    else
    {
        if (huong == TRAI) LayAnh("anh/nhaytrai.png", screen);
        else LayAnh("anh/nhayphai.png", screen);
    }
}

void NhanVat::XuatNhanVat(SDL_Renderer* screen)
{
    ChonAnhNhanVat(screen);

    if (hd.trai || hd.phai) frame++;
    else frame = 0;
    if (frame >= FRAME) frame = 0;

    if (!time)
    {
        kichthuoc.x = vitri_x - map_x;
        kichthuoc.y = vitri_y - map_y;

        SDL_Rect* hieuunghientai = &hieuung[frame];
        SDL_Rect cacthongso = {kichthuoc.x, kichthuoc.y, frame_w, frame_h};
        SDL_RenderCopy(screen, texture, hieuunghientai, &cacthongso);
    }
}

void NhanVat::XuLi(SDL_Event event, SDL_Renderer* screen)
{
    if (event.type == SDL_KEYDOWN)
        switch (event.key.keysym.sym)
        {
            case SDLK_d:
            {
                huong = PHAI;
                hd.phai = 1;
                hd.trai = 0;
                ChonAnhNhanVat(screen);
                break;
            }
            case SDLK_a:
            {
                huong = TRAI;
                hd.trai = 1;
                hd.phai = 0;
                ChonAnhNhanVat(screen);
                break;
            }
            case SDLK_w:
            {
                hd.nhay = 1;
                break;
            }
            case SDLK_u:
            {
                if (!time)
                {
                    Dan* dan = new Dan();
                    dan->CaiLoai(Dan::TRON);
                    dan->LayDan(screen);
                    Mix_PlayChannel(-1, Mix_LoadWAV("nhac/dantron.wav"), 0);
                    if (huong == TRAI)
                    {
                        dan->CaiHuong(Dan::TRAI);
                        dan->CaiKichThuoc(this->kichthuoc.x + 6, kichthuoc.y + frame_h*0.22);
                    }
                    else
                    {
                        dan->CaiHuong(Dan::PHAI);
                        dan->CaiKichThuoc(this->kichthuoc.x + frame_w - 24, kichthuoc.y + frame_h*0.22);
                    }
                    dan->CaiCheck(true);
                    dan->CaiDi(18);
                    bangdan.push_back(dan);
                }
                break;
            }
            case SDLK_i:
            {
                if (!time)
                {
                    Bom* bom = new Bom();
                    bom->LayBom(screen);
                    Mix_PlayChannel(-1, Mix_LoadWAV("nhac/datbom.wav"), 0);
                    bom->CaiKichThuoc(this->kichthuoc.x + frame_w*0.4, kichthuoc.y + frame_h*0.85);
                    bom->CaiCheck(true);
                    bom->CaiDi(10);
                    chuoibom.push_back(bom);
                }
                break;
            }
        }
    else if (event.type == SDL_KEYUP)
        switch (event.key.keysym.sym)
        {
            case SDLK_d:
            {
                hd.phai = 0;
                break;
            }
            case SDLK_a:
            {
                hd.trai = 0;
                break;
            }
            case SDLK_w:
            {
                hd.nhay = 0;
                break;
            }
        }
}

void NhanVat::DiChuyenNhanVat(MAP& map_, SDL_Renderer* screen)
{
    if (!time)
    {
        di_x = 0;
        di_y += ROI;
        if (di_y > ROIM) di_y = ROIM;

        if (hd.phai) di_x += NV_DI;
        else if (hd.trai) di_x -= NV_DI;
        if (hd.nhay)
        {
            if (matdat) di_y = -NV_NHAY;
            matdat = false;
        }

        CheckMap(map_, screen);
        CuonMap(map_);
    }
    else
    {
        time--;
        if (!time)
        {
            matdat = false;
            if (vitri_x < 25*O_SIZE) vitri_x = O_SIZE;
            else if (vitri_x > 25*O_SIZE && vitri_x < 71*O_SIZE) vitri_x = 25*O_SIZE;
            else if (vitri_x > 71*O_SIZE && vitri_x < 108*O_SIZE) vitri_x = 71*O_SIZE;
            else if (vitri_x > 108*O_SIZE && vitri_x < 148*O_SIZE) vitri_x = 108*O_SIZE;
            else if (vitri_x > 148*O_SIZE && vitri_x < 186*O_SIZE) vitri_x = 148*O_SIZE;
            else if (vitri_x > 186*O_SIZE && vitri_x < 244*O_SIZE) vitri_x = 186*O_SIZE;
            else if (vitri_x > 244*O_SIZE && vitri_x < 288*O_SIZE) vitri_x = 244*O_SIZE;
            else if (vitri_x > 288*O_SIZE && vitri_x < 347*O_SIZE) vitri_x = 288*O_SIZE;
            else if (vitri_x > 347*O_SIZE && vitri_x < 382*O_SIZE) vitri_x = 347*O_SIZE;
            else vitri_x = 382*O_SIZE;
            vitri_y = O_SIZE;
            di_x = 0;
            di_y = 0;
        }
    }
}

int NhanVat::Check(MAP& map_, const int y, const int x)
{
    if (map_.o[y][x] >= 1 && map_.o[y][x] <= 18) return 0;
    if (map_.o[y][x] == 24) return 1;
    if (map_.o[y][x] == 25) return 5;
    if (map_.o[y][x] == 26) return 10;
    if (map_.o[y][x] == 19 || map_.o[y][x] == 20) return -1;
    return 2;
}

void NhanVat::CheckMap(MAP& map_, SDL_Renderer* screen)
{
    int x1 = (vitri_x + di_x)/O_SIZE;
    int x2 = (vitri_x + di_x + frame_w - 1)/O_SIZE;
    int y1 = vitri_y/O_SIZE;
    int y2 = (vitri_y + frame_h - 1)/O_SIZE;

    if (x1>=0 && x2<MAP_W && y1>=0 && y2<MAP_H)
    {
        if (di_x > 0)
        {
            switch (Check(map_,y1,x2))
            {
                case 1:
                {
                    map_.o[y1][x2] = 0;
                    ThuThapTien(1);
                    break;
                }
                case 5:
                {
                    map_.o[y1][x2] = 0;
                    ThuThapTien(5);
                    break;
                }
                case 10:
                {
                    map_.o[y1][x2] = 0;
                    ThuThapMang();
                    break;
                }
                case 0:
                {
                    vitri_x = x2*O_SIZE - frame_w - 1;
                    di_x = 0;
                    break;
                }
                case -1:
                {
                    MatMang(screen);
                    break;
                }
                default:
                    break;
            }
            switch (Check(map_,y2,x2))
            {
                case 1:
                {
                    map_.o[y2][x2] = 0;
                    ThuThapTien(1);
                    break;
                }
                case 5:
                {
                    map_.o[y2][x2] = 0;
                    ThuThapTien(5);
                    break;
                }
                case 10:
                {
                    map_.o[y2][x2] = 0;
                    ThuThapMang();
                    break;
                }
                case 0:
                {
                    vitri_x = x2*O_SIZE - frame_w - 1;
                    di_x = 0;
                    break;
                }
                case -1:
                {
                    MatMang(screen);
                    break;
                }
                default:
                    break;
            }
        }
        else if (di_x < 0)
        {
            switch (Check(map_,y1,x1))
            {
                case 1:
                {
                    map_.o[y1][x1] = 0;
                    ThuThapTien(1);
                    break;
                }
                case 5:
                {
                    map_.o[y1][x1] = 0;
                    ThuThapTien(5);
                    break;
                }
                case 10:
                {
                    map_.o[y1][x1] = 0;
                    ThuThapMang();
                    break;
                }
                case 0:
                {
                    vitri_x = (x1+1)*O_SIZE;
                    di_x = 0;
                    break;
                }
                case -1:
                {
                    MatMang(screen);
                    break;
                }
                default:
                    break;
            }
            switch (Check(map_,y2,x1))
            {
                case 1:
                {
                    map_.o[y2][x1] = 0;
                    ThuThapTien(1);
                    break;
                }
                case 5:
                {
                    map_.o[y2][x1] = 0;
                    ThuThapTien(5);
                    break;
                }
                case 10:
                {
                    map_.o[y2][x1] = 0;
                    ThuThapMang();
                    break;
                }
                case 0:
                {
                    vitri_x = (x1+1)*O_SIZE;
                    di_x = 0;
                    break;
                }
                case -1:
                {
                    MatMang(screen);
                    break;
                }
                default:
                    break;
            }
        }
    }

    x1 = vitri_x/O_SIZE;
    x2 = (vitri_x + frame_w - 1)/O_SIZE;
    y1 = (vitri_y + di_y)/O_SIZE;
    y2 = (vitri_y + di_y + frame_h - 1)/O_SIZE;

    if (x1>=0 && x2<MAP_W && y1>=0 && y2<MAP_H)
    {
        if (di_y > 0)
        {
            switch (Check(map_,y2,x1))
            {
                case 1:
                {
                    map_.o[y2][x1] = 0;
                    ThuThapTien(1);
                    break;
                }
                case 5:
                {
                    map_.o[y2][x1] = 0;
                    ThuThapTien(5);
                    break;
                }
                case 10:
                {
                    map_.o[y2][x1] = 0;
                    ThuThapMang();
                    break;
                }
                case 0:
                {
                    vitri_y = y2*O_SIZE - frame_h - 1;
                    di_y = 0;
                    matdat = true;
                    if (huong == DUNG) huong = PHAI;
                    break;
                }
                case -1:
                {
                    MatMang(screen);
                    break;
                }
                default:
                    break;
            }
            switch (Check(map_,y2,x2))
            {
                case 1:
                {
                    map_.o[y2][x2] = 0;
                    ThuThapTien(1);
                    break;
                }
                case 5:
                {
                    map_.o[y2][x2] = 0;
                    ThuThapTien(5);
                    break;
                }
                case 10:
                {
                    map_.o[y2][x2] = 0;
                    ThuThapMang();
                    break;
                }
                case 0:
                {
                    vitri_y = y2*O_SIZE - frame_h - 1;
                    di_y = 0;
                    matdat = true;
                    if (huong == DUNG) huong = PHAI;
                    break;
                }
                case -1:
                {
                    MatMang(screen);
                    break;
                }
                default:
                    break;
            }
        }
        else if (di_y < 0)
        {
            switch (Check(map_,y1,x1))
            {
                case 1:
                {
                    map_.o[y1][x1] = 0;
                    ThuThapTien(1);
                    break;
                }
                case 5:
                {
                    map_.o[y1][x1] = 0;
                    ThuThapTien(5);
                    break;
                }
                case 10:
                {
                    map_.o[y1][x1] = 0;
                    ThuThapMang();
                    break;
                }
                case 0:
                {
                    vitri_y = (y1+1)*O_SIZE;
                    di_y = 0;
                    break;
                }
                case -1:
                {
                    MatMang(screen);
                    break;
                }
                default:
                    break;
            }
            switch (Check(map_,y1,x2))
            {
                case 1:
                {
                    map_.o[y1][x2] = 0;
                    ThuThapTien(1);
                    break;
                }
                case 5:
                {
                    map_.o[y1][x2] = 0;
                    ThuThapTien(5);
                    break;
                }
                case 10:
                {
                    map_.o[y1][x2] = 0;
                    ThuThapMang();
                    break;
                }
                case 0:
                {
                    vitri_y = (y1+1)*O_SIZE;
                    di_y = 0;
                    break;
                }
                case -1:
                {
                    MatMang(screen);
                    break;
                }
                default:
                    break;
            }
        }
    }

    vitri_x += di_x;
    vitri_y += di_y;

    if (vitri_x < 0) vitri_x = 0;
    else if (vitri_x + frame_w > map_.o_x) vitri_x = map_.o_x - frame_w - 1;

    if (vitri_y > map_.o_y) MatMang(screen);
}

void NhanVat::CuonMap(MAP& map_)
{
    map_.toado_x = vitri_x - SCR_W*2/5;
    if (map_.toado_x < 0) map_.toado_x = 0;
    else if (map_.toado_x + SCR_W >= map_.o_x) map_.toado_x = map_.o_x - SCR_W;

    map_.toado_y = vitri_y - SCR_H*2;
    if (map_.toado_y < 0) map_.toado_y = 0;
    else if (map_.toado_y + SCR_H >= map_.o_y) map_.toado_y = map_.o_y - SCR_H;
}

void NhanVat::XuLiDan(SDL_Renderer* screen)
{
    for (int i=0; i < bangdan.size(); i++)
    {
        Dan* dan = bangdan.at(i);
        if (dan)
        {
            if (dan->LayCheck())
            {
                dan->XuLi();
                dan->XuatAnh(screen);
            }
            else XoaDan(i);
        }
    }
}

void NhanVat::XoaDan(const int& i)
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

void NhanVat::XuLiBom(SDL_Renderer* screen)
{
    for (int i=0; i < chuoibom.size(); i++)
    {
        Bom* bom = chuoibom.at(i);
        if (bom)
        {
            if (bom->LayCheck())
            {
                bom->XuLi();
                bom->XuatAnh(screen);
            }
            else XoaBom(i);
        }
    }
}

void NhanVat::XoaBom(const int& i)
{
    if (chuoibom.size() > 0 && i < chuoibom.size())
    {
        Bom* bom = chuoibom.at(i);
        chuoibom.erase(chuoibom.begin() + i);
        if (bom)
        {
            delete bom;
            bom = NULL;
        }
    }
}

SDL_Rect NhanVat::LayKichThuocFrame()
{
    SDL_Rect kt;
    kt.x = kichthuoc.x;
    kt.y = kichthuoc.y;
    kt.w = frame_w;
    kt.h = frame_h;
    return kt;
}

void NhanVat::ThuThapTien(const int& i)
{
    Mix_PlayChannel(-1, Mix_LoadWAV("nhac/thuthaptien.wav"), 0);
    tien += i;
}

void NhanVat::ThuThapKill(const int& i)
{
    kill += i;
}

void NhanVat::ThuThapMang()
{
    Mix_PlayChannel(-1, Mix_LoadWAV("nhac/thuthapmang.wav"), 0);
    mang++;
    somang.Tang();
}

void NhanVat::MatMang(SDL_Renderer* screen)
{
    Mix_PlayChannel(-1, Mix_LoadWAV("nhac/nonhanvat.wav"), 0);
    no.LayVuNo("anh/nonhanvat.png", screen);
    no.LayHieuUng();
    for (int i=0; i < FRAME; i++)
    {
        no.CaiFrame(i);
        no.CaiKichThuoc(kichthuoc.x + (frame_w - no.LayFrameW())*0.5, kichthuoc.y + (frame_h - no.LayFrameH())*0.5);
        no.XuatVuNo(screen);
        SDL_Delay(1000/FPS);
        SDL_RenderPresent(screen);
    }
    mang--;
    somang.Mat();
    somang.Xuat(screen);
    kichthuoc.x = 0;
    kichthuoc.y = 0;
    CaiTime(60);
    SDL_Delay(1000);
}
