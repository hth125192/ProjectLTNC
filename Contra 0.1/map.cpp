#include "map.h"

void Map::LayMap(char* name)
{
    FILE* fp = NULL;
    fopen_s(&fp, name, "rb");
    if (!fp) return;

    map_.o_x = 0;
    map_.o_y = 0;
    for (int i=0; i < MAP_H; i++)
        for (int j=0; j < MAP_W; j++)
        {
            fscanf(fp, "%d", &map_.o[i][j]);
            if (map_.o[i][j])
            {
                if (j > map_.o_x) map_.o_x = j;
                if (i > map_.o_y) map_.o_y = i;
            }
        }
    map_.o_x = (map_.o_x + 1)*O_SIZE;
    map_.o_y = (map_.o_y + 1)*O_SIZE;
    map_.toado_x = 0;
    map_.toado_y = 0;
    map_.ten = name;
    fclose(fp);
}

void Map::LayOMap(SDL_Renderer* screen)
{
    char anh[O_NUM];
    FILE* fp = NULL;

    for (int i=0; i < O_NUM; i++)
    {
        sprintf_s(anh, "map/%d.png", i);
        fopen_s(&fp, anh, "rb");
        if (!fp) continue;
        fclose(fp);
        loaimap[i].LayAnh(anh, screen);
    }
}

void Map::XuatMap(SDL_Renderer* screen)
{
    int x1 = -map_.toado_x % O_SIZE;
    int x2 = x1 + SCR_W + (x1 ? O_SIZE : 0);
    int x = map_.toado_x/O_SIZE;
    int y1 = -map_.toado_y % O_SIZE;
    int y2 = y1 + SCR_H + (y1 ? O_SIZE : 0);
    int y = map_.toado_y/O_SIZE;

    for (int i=y1; i<y2; i+=O_SIZE)
    {
        x = map_.toado_x/O_SIZE;
        for (int j=x1; j<x2; j+=O_SIZE)
        {
            if (map_.o[y][x])
            {
                loaimap[map_.o[y][x]].CaiKichThuoc(j,i);
                loaimap[map_.o[y][x]].XuatAnh(screen);
            }
            x++;
        }
        y++;
    }
}
