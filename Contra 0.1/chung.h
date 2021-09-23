#ifndef CHUNG_H_INCLUDED
#define CHUNG_H_INCLUDED

#include <windows.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int SCR_W = 1280;
const int SCR_H = 640;

const int KEY_R = 167;
const int KEY_G = 175;
const int KEY_B = 180;

const int FPS = 30;
const int MFPS = 10;

const int TIME = 360;

#define O_NUM 30
#define O_SIZE 64
#define MAP_W 400
#define MAP_H 10

#define FRAME 8
#define FRAMEM 32
#define ROI 0.8
#define ROIM 10
#define NV_NHAY 15
#define NV_DI 8
#define QUAI_DI 3

typedef struct MAP
{
    int toado_x;
    int toado_y;
    int o_x;
    int o_y;
    int o[MAP_H][MAP_W];
    char* ten;
};

typedef struct ACTION
{
    int trai;
    int phai;
    int nhay;
};

typedef struct FORMAT
{
    FORMAT(int x, int y, int w, int h) {x_ = x, y_ = y, w_ = w, h_ = h;}
    int x_;
    int y_;
    int w_;
    int h_;
};

typedef struct COLOR
{
    COLOR(Uint8 r, Uint8 g, Uint8 b) {r_ = r, g_ = g, b_ = b;}
    Uint8 r_;
    Uint8 g_;
    Uint8 b_;
};

bool CheckVaCham(const SDL_Rect& kichthuoc1, const SDL_Rect& kichthuoc2);

#endif // CHUNG_H_INCLUDED
