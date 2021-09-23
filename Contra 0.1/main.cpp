#include "chung.h"
#include "anh.h"
#include "map.h"
#include "nhanvat.h"
#include "quai.h"
#include "boss.h"
#include "no.h"
#include "chu.h"
#include "ve.h"
#include "fps.h"

Anh background;
Anh menu;
Anh hd;
TTF_Font* font = NULL;
TTF_Font* mfont = NULL;
Fps fps;
bool ibatdau = false;
bool inhacnen = true;
bool iketthuc = false;

bool KhoiTao()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Contra 0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_W, SCR_H, SDL_WINDOW_SHOWN);
    if (!g_window) return false;

    g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (!g_screen) return false;

    SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);

    if (!(IMG_Init(IMG_INIT_PNG) && IMG_INIT_PNG)) return false;

    if (TTF_Init() == -1) return false;

    font = TTF_OpenFont("font/font.ttf", 15);
    if (!font) return false;

    mfont = TTF_OpenFont("font/font.ttf", 32);
    if (!mfont) return false;

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;

    if (!background.LayAnh("anh/background.png", g_screen)) return false;

    if (!menu.LayAnh("anh/menu.png", g_screen)) return false;

    if (!hd.LayAnh("anh/huongdan.png", g_screen)) return false;

    return true;
}

void BatDau()
{
    Chu chon[4];
    int x[4] = {338,642,338,642};
    int y[4] = {242,296,350,404};
    bool ihuongdan = false;
    bool icaidat = false;
    while (!ibatdau)
    {
        fps.BatDau();

        while (SDL_PollEvent(&g_event))
        {
            bool check[4];
            for (int i=0; i<4; i++) check[i] = g_event.motion.x >= x[i] && g_event.motion.x <= x[i] + chon[i].LayW() && g_event.motion.y >= y[i] && g_event.motion.y <= y[i] + chon[i].LayH();

            switch (g_event.type)
            {
                case SDL_QUIT:
                {
                    ibatdau = true;
                    iketthuc = true;
                    break;
                }
                case SDL_MOUSEMOTION:
                {
                    for (int i=0; i<4; i++)
                        if (check[i]) chon[i].CaiMau(Chu::DO); else chon[i].CaiMau(Chu::TRANG);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    if (check[0]) ibatdau = true;
                    else if (check[1]) ihuongdan = true;
                    else if (check[2]) icaidat = true;
                    else if (check[3])
                    {
                        ibatdau = true;
                        iketthuc = true;
                    }
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderClear(g_screen);
        menu.XuatAnh(g_screen);

        chon[0].CaiNoiDung("Bat dau");
        chon[1].CaiNoiDung("Huong dan");
        chon[2].CaiNoiDung("Cai dat");
        chon[3].CaiNoiDung("Thoat");

        for (int i=0; i<4; i++)
        {
            chon[i].LayChu(mfont, g_screen);
            chon[i].XuatChu(g_screen,x[i],y[i]);
        }

        if (ihuongdan)
        {
            Fps mfps;
            Chu mchon[4];
            int mx[4] = {338,338,338,642};
            int my[4] = {242,328,414,518};

            while (ihuongdan)
            {
                mfps.BatDau();
                for (int i=0; i<3; i++) mchon[i].CaiMau(Chu::TRANG);

                while (SDL_PollEvent(&g_event))
                {
                    bool mcheck = g_event.motion.x >= mx[3] && g_event.motion.x <= mx[3] + mchon[3].LayW() && g_event.motion.y >= my[3] && g_event.motion.y <= my[3] + mchon[3].LayH();

                    switch (g_event.type)
                    {
                        case SDL_QUIT:
                        {
                            ibatdau = true;
                            iketthuc = true;
                            ihuongdan = false;
                            break;
                        }
                        case SDL_MOUSEMOTION:
                        {
                            if (mcheck) mchon[3].CaiMau(Chu::DO); else mchon[3].CaiMau(Chu::TRANG);
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN:
                        {
                            if (mcheck) ihuongdan = false;
                            break;
                        }
                    }
                }

                SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
                SDL_RenderClear(g_screen);
                hd.XuatAnh(g_screen);

                mchon[0].CaiNoiDung("Di chuyen: A-W-D");
                mchon[1].CaiNoiDung("10   = 2   = 1");
                mchon[2].CaiNoiDung("1   = 1   = -1");
                mchon[3].CaiNoiDung("Quay lai");

                for (int i=0; i<4; i++)
                {
                    mchon[i].LayChu(mfont, g_screen);
                    mchon[i].XuatChu(g_screen,mx[i],my[i]);
                }

                SDL_RenderPresent(g_screen);

                if (1000/MFPS > mfps.LayT()) SDL_Delay(1000/MFPS - mfps.LayT());
            }
        }

        if (icaidat)
        {
            Fps mfps;
            Chu mchon[4];
            int mx[4] = {338,550,778,612};
            int my[4] = {242,302,302,400};

            while (icaidat)
            {
                mfps.BatDau();
                mchon[0].CaiMau(Chu::TRANG);

                while (SDL_PollEvent(&g_event))
                {
                    bool mcheck[4];
                    for (int i=1; i<4; i++) mcheck[i] = g_event.motion.x >= mx[i] && g_event.motion.x <= mx[i] + mchon[i].LayW() && g_event.motion.y >= my[i] && g_event.motion.y <= my[i] + mchon[i].LayH();

                    switch (g_event.type)
                    {
                        case SDL_QUIT:
                        {
                            ibatdau = true;
                            iketthuc = true;
                            icaidat = false;
                            break;
                        }
                        case SDL_MOUSEMOTION:
                        {
                            if (mcheck[1]) mchon[1].CaiMau(Chu::XANHLA); else mchon[1].CaiMau(Chu::TRANG);
                            if (mcheck[2]) mchon[2].CaiMau(Chu::XANHLA); else mchon[2].CaiMau(Chu::TRANG);
                            if (mcheck[3]) mchon[3].CaiMau(Chu::DO); else mchon[3].CaiMau(Chu::TRANG);
                            break;
                        }
                        case SDL_MOUSEBUTTONDOWN:
                        {
                            if (mcheck[1])
                            {
                                inhacnen = false;
                                icaidat = false;
                            }
                            else if (mcheck[2])
                            {
                                inhacnen = true;
                                icaidat = false;
                            }
                            else if (mcheck[3]) icaidat = false;
                            break;
                        }
                    }
                }

                SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
                SDL_RenderClear(g_screen);
                menu.XuatAnh(g_screen);

                mchon[0].CaiNoiDung("Nhac nen?");
                mchon[1].CaiNoiDung("<Tat>");
                mchon[2].CaiNoiDung("<Bat>");
                mchon[3].CaiNoiDung("Quay lai");

                for (int i=0; i<4; i++)
                {
                    mchon[i].LayChu(mfont, g_screen);
                    mchon[i].XuatChu(g_screen,mx[i],my[i]);
                }

                SDL_RenderPresent(g_screen);

                if (1000/MFPS > mfps.LayT()) SDL_Delay(1000/MFPS - mfps.LayT());
            }
        }

        SDL_RenderPresent(g_screen);

        if (1000/MFPS > fps.LayT()) SDL_Delay(1000/MFPS - fps.LayT());
    }
}

void KetThuc(NhanVat nhanvat, const bool& kq)
{
    Chu chon[6];
    int x[6] = {398,494,704,494,672,322};
    int y[6] = {242,326,326,388,388,564};
    int nhay = 0;

    while (iketthuc)
    {
        fps.BatDau();
        nhay = (nhay+1)%4;
        for (int i=0; i<5; i++) chon[i].CaiMau(Chu::TRANG);
        if (nhay<2)
            if (kq) chon[0].CaiMau(Chu::XANHLA); else chon[0].CaiMau(Chu::DO);

        while (SDL_PollEvent(&g_event))
        {
            bool check = g_event.motion.x >= x[5] && g_event.motion.x <= x[5] + chon[5].LayW() && g_event.motion.y >= y[5] && g_event.motion.y <= y[5] + chon[5].LayH();

            switch (g_event.type)
            {
                case SDL_QUIT:
                {
                    iketthuc = false;
                    break;
                }
                case SDL_MOUSEMOTION:
                {
                    if (check) chon[5].CaiMau(Chu::DO); else chon[5].CaiMau(Chu::TRANG);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    if (check) iketthuc = false;
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderClear(g_screen);
        menu.XuatAnh(g_screen);

        if (kq) chon[0].CaiNoiDung("CONGRATULATIOS!"); else chon[0].CaiNoiDung(">> GAME OVER <<");
        chon[1].CaiNoiDung("Money:");
        chon[2].CaiNoiDung(std::to_string(nhanvat.LayTien()));
        chon[3].CaiNoiDung("Kill:");
        chon[4].CaiNoiDung(std::to_string(nhanvat.LayKill()));
        chon[5].CaiNoiDung("Thoat");

        for (int i=0; i<6; i++)
        {
            chon[i].LayChu(mfont, g_screen);
            chon[i].XuatChu(g_screen,x[i],y[i]);
        }

        SDL_RenderPresent(g_screen);

        if (1000/MFPS > fps.LayT()) SDL_Delay(1000/MFPS - fps.LayT());
    }
}

void GiaiPhong()
{
    background.Free();
    hd.Free();
    menu.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<Quai*> TaoDSQuai()
{
    std::vector<Quai*> dsquai;

    int x_dungim[15] = {11,22,34,45,56,66,105,146,178,215,231,299,354,368,392};
    int y_dungim[15] = {8,7,5,4,9,4,5,8,3,6,5,3,5,5,7};
    int x_dichuyen[25] = {5,15,24,46,60,80,88,89,123,155,159,164,174,198,238,245,255,270,281,293,301,334,351,383,384};
    int y_dichuyen[25] = {8,5,5,9,9,5,3,8,9,6,9,4,6,5,4,7,7,7,7,9,3,5,5,7,7};
    int phamvi[25] = {2,3,2,3,2,3,3,2,1,2,4,3,1,1,1,2,3,3,2,3,1,1,1,4,5};

    Quai* quaidungim = new Quai[15];
    for (int i=0; i<15; i++)
    {
        Quai* quai = (quaidungim + i);
        if (quai)
        {
            quai->LayQuai("anh/quaidung.png", g_screen);
            quai->LayHieuUng();
            quai->CaiLoai(Quai::DUNGIM);
            quai->CaiViTriX(x_dungim[i]*O_SIZE);
            quai->CaiViTriY(y_dungim[i]*O_SIZE);
            Dan* dan = new Dan();
            quai->NapDan(dan, g_screen);
            dsquai.push_back(quai);
        }
    }

    Quai* quaidichuyen = new Quai[25];
    for (int i=0; i<25; i++)
    {
        Quai* quai = (quaidichuyen + i);
        if (quai)
        {
            quai->LayQuai("anh/quaitrai.png", g_screen);
            quai->LayHieuUng();
            quai->CaiLoai(Quai::DICHUYEN);
            quai->CaiViTriX(x_dichuyen[i]*O_SIZE);
            quai->CaiViTriY(y_dichuyen[i]*O_SIZE);
            quai->CaiTraiPhai(x_dichuyen[i]*O_SIZE + 1, (x_dichuyen[i] + phamvi[i])*O_SIZE - 1);
            quai->CaiACTION();
            dsquai.push_back(quai);
        }
    }

    return dsquai;
}

int main(int argc, char* argv[])
{
    if (!KhoiTao()) return -1;

    BatDau();

    Map g_map;
    g_map.LayMap("map/map.txt");
    g_map.LayOMap(g_screen);

    NhanVat nhanvat;
    nhanvat.LayNhanVat("anh/nvphai.png", g_screen);
    nhanvat.LayHieuUng();
    nhanvat.somang.Lay(g_screen);
    nhanvat.no.LayVuNo("anh/nonhanvat.png", g_screen);
    nhanvat.no.LayHieuUng();

    No noquai;
    noquai.LayVuNo("anh/noquai.png", g_screen);
    noquai.LayHieuUng();

    std::vector<Quai*> dsquai = TaoDSQuai();

    Boss boss;
    boss.LayBoss("anh/quaiboss.png", g_screen);
    boss.LayHieuUng();
    boss.CaiViTriX(396*O_SIZE);
    boss.CaiViTriY(O_SIZE);

    Chu g_money;
    g_money.CaiMau(Chu::TRANG);

    Chu g_kill;
    g_kill.CaiMau(Chu::TRANG);

    Chu g_time;
    g_time.CaiMau(Chu::TRANG);

    if (inhacnen) Mix_PlayChannel(-1, Mix_LoadWAV("nhac/nhacnen.wav"), 0);

    while (ibatdau && !iketthuc)
    {
        fps.BatDau();

        while (SDL_PollEvent(&g_event))
        {
            if (g_event.type == SDL_QUIT || g_event.key.keysym.sym == SDLK_ESCAPE) iketthuc = true;
            nhanvat.XuLi(g_event, g_screen);
        }
        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderClear(g_screen);

        background.XuatAnh(g_screen);

        MAP map_ = g_map.LayMAP();
        g_map.XuatMap(g_screen);

        nhanvat.XuLiDan(g_screen);
        nhanvat.XuLiBom(g_screen);
        nhanvat.CaiViTriMap(map_.toado_x, map_.toado_y);
        nhanvat.DiChuyenNhanVat(map_, g_screen);
        if (!nhanvat.LayMang())
        {
            Mix_PlayChannel(-1, Mix_LoadWAV("nhac/gameover.wav"), 0);
            iketthuc = true;
            KetThuc(nhanvat,false);
            GiaiPhong();
            return 0;
        }
        nhanvat.XuatNhanVat(g_screen);

        g_map.CaiMAP(map_);

        FORMAT kthcn(0,0,SCR_W,32);
        COLOR mauhcn(95,95,95);
        Ve::VeHCN(kthcn, mauhcn, g_screen);

        FORMAT ktvien(0,0,SCR_W,31);
        COLOR mauvien(255,255,255);
        Ve::VeVien(ktvien, mauvien, g_screen);

        nhanvat.somang.Xuat(g_screen);

        std::string nd = "Money: " + std::to_string(nhanvat.LayTien());
        g_money.CaiNoiDung(nd);
        g_money.LayChu(font, g_screen);
        g_money.XuatChu(g_screen,430,8);

        nd = "Kill: " + std::to_string(nhanvat.LayKill());
        g_kill.CaiNoiDung(nd);
        g_kill.LayChu(font, g_screen);
        g_kill.XuatChu(g_screen,700,8);

        if (TIME < SDL_GetTicks()/1000)
        {
            Mix_PlayChannel(-1, Mix_LoadWAV("nhac/timeout.wav"), 0);
            iketthuc = true;
            KetThuc(nhanvat,false);
            GiaiPhong();
            return 0;
        }
        else
        {
            nd = "Time: " + std::to_string(TIME - SDL_GetTicks()/1000);
            g_time.CaiNoiDung(nd);
            g_time.LayChu(font, g_screen);
            g_time.XuatChu(g_screen,1110,8);
        }

        for (int i=0; i < dsquai.size(); i++)
        {
            Quai* quai = dsquai.at(i);
            if (quai)
            {
                quai->CaiViTriMap(map_.toado_x, map_.toado_y);
                quai->QuaiDiChuyen(g_screen);
                quai->DiChuyenQuai(map_);
                quai->BanDan(g_screen);
                quai->XuatQuai(g_screen);

                bool check1 = false;
                for (int j=0; j < quai->LayBangDan().size(); j++)
                {
                    Dan* dan = quai->LayBangDan().at(j);
                    if (dan)
                        if (CheckVaCham(nhanvat.LayKichThuocFrame(), dan->LayKichThuoc()))
                        {
                            check1 = true;
                            break;
                        }
                }
                bool check2 = CheckVaCham(nhanvat.LayKichThuocFrame(), quai->LayKichThuocFrame());
                if (check1 || check2)
                {
                    nhanvat.MatMang(g_screen);
                    if (!nhanvat.LayMang())
                    {
                        Mix_PlayChannel(-1, Mix_LoadWAV("nhac/gameover.wav"), 0);
                        iketthuc = true;
                        KetThuc(nhanvat,false);
                        quai->Free();
                        GiaiPhong();
                        return 0;
                    }
                }
            }
        }

        for (int i=0; i < nhanvat.LayBangDan().size(); i++)
        {
            Dan* dan = nhanvat.LayBangDan().at(i);
            if (dan)
            {
                for (int j=0; j < dsquai.size(); j++)
                {
                    Quai* quai = dsquai.at(j);
                    if (quai)
                        if (CheckVaCham(dan->LayKichThuoc(), quai->LayKichThuocFrame()))
                        {
                            nhanvat.ThuThapKill(1);
                            for (int k=0; k < FRAME; k++)
                            {
                                noquai.CaiFrame(k);
                                noquai.CaiKichThuoc(dan->LayKichThuoc().x - noquai.LayFrameW()*0.5, dan->LayKichThuoc().y - noquai.LayFrameH()*0.5);
                                noquai.XuatVuNo(g_screen);
                            }
                            nhanvat.XoaDan(i);
                            Mix_PlayChannel(-1, Mix_LoadWAV("nhac/noquai.wav"), 0);
                            quai->Free();
                            dsquai.erase(dsquai.begin() + j);
                        }
                }
                if (CheckVaCham(dan->LayKichThuoc(), boss.LayKichThuocFrame()))
                {
                    nhanvat.XoaDan(i);
                    boss.MatMang(g_screen);
                    if (!boss.LayMang())
                    {
                        nhanvat.ThuThapKill(10);
                        Mix_PlayChannel(-1, Mix_LoadWAV("nhac/congratulatios.wav"), 0);
                        iketthuc = true;
                        KetThuc(nhanvat,true);
                        boss.Free();
                        GiaiPhong();
                        return 0;
                    }
                }
            }
        }

        boss.CaiViTriMap(map_.toado_x, map_.toado_y);
        boss.DiChuyenBoss(map_);
        boss.BanDan(g_screen);
        boss.XuatBoss(g_screen);

        for (int i=0; i < nhanvat.LayChuoiBom().size(); i++)
        {
            Bom* bom = nhanvat.LayChuoiBom().at(i);
            if (bom)
            {
                for (int j=0; j < dsquai.size(); j++)
                {
                    Quai* quai = dsquai.at(j);
                    if (quai)
                        if (CheckVaCham(bom->LayKichThuoc(), quai->LayKichThuocFrame()))
                        {
                            nhanvat.ThuThapKill(1);
                            for (int k=0; k < FRAME; k++)
                            {
                                noquai.CaiFrame(k);
                                noquai.CaiKichThuoc(bom->LayKichThuoc().x - noquai.LayFrameW()*0.5, bom->LayKichThuoc().y - noquai.LayFrameH()*0.5);
                                noquai.XuatVuNo(g_screen);
                            }
                            nhanvat.XoaBom(i);
                            Mix_PlayChannel(-1, Mix_LoadWAV("nhac/nobom.wav"), 0);
                            quai->Free();
                            dsquai.erase(dsquai.begin() + j);
                        }
                }
                if (CheckVaCham(bom->LayKichThuoc(), boss.LayKichThuocFrame()))
                {
                    nhanvat.XoaBom(i);
                    boss.MatMang(g_screen);
                    if (!boss.LayMang())
                    {
                        nhanvat.ThuThapKill(10);
                        Mix_PlayChannel(-1, Mix_LoadWAV("nhac/congratulatios.wav"), 0);
                        iketthuc = true;
                        KetThuc(nhanvat,true);
                        boss.Free();
                        GiaiPhong();
                        return 0;
                    }
                }
            }
        }

        bool check1 = false;
        for (int i=0; i < boss.LayBangDan().size(); i++)
        {
            Dan* dan = boss.LayBangDan().at(i);
            if (dan)
                if (CheckVaCham(nhanvat.LayKichThuocFrame(), dan->LayKichThuoc()))
                {
                    check1 = true;
                    break;
                }
        }
        bool check2 = CheckVaCham(nhanvat.LayKichThuocFrame(), boss.LayKichThuocFrame());
        if (check1 || check2)
        {
            nhanvat.MatMang(g_screen);
            if (!nhanvat.LayMang())
            {
                Mix_PlayChannel(-1, Mix_LoadWAV("nhac/gameover.wav"), 0);
                iketthuc = true;
                KetThuc(nhanvat,false);
                boss.Free();
                GiaiPhong();
                return 0;
            }
        }

        SDL_RenderPresent(g_screen);

        if (1000/FPS > fps.LayT()) SDL_Delay(1000/FPS - fps.LayT());
    }

    for (int i=0; i < dsquai.size(); i++)
    {
        Quai* quai = dsquai.at(i);
        if (quai)
        {
            quai->Free();
            quai = NULL;
        }
    }
    dsquai.clear();

    GiaiPhong();
    return 0;
}
