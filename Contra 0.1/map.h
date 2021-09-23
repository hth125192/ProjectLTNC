#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "chung.h"
#include "anh.h"

class OMap : public Anh
{
public:
    OMap(){}
    ~OMap(){Free();}
};

class Map
{
public:
    Map(){}
    ~Map(){}

    void LayMap(char* name);
    void LayOMap(SDL_Renderer* screen);
    void XuatMap(SDL_Renderer* screen);

    void CaiMAP(MAP& m) {map_ = m;}
    MAP LayMAP() const {return map_;}

private:
    MAP map_;
    OMap loaimap[O_NUM];
};

#endif // MAP_H_INCLUDED
