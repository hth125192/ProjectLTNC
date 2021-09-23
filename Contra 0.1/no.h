#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

#include "chung.h"
#include "anh.h"

class No : public Anh
{
public:
    No();
    ~No();

    void LayVuNo(std::string link, SDL_Renderer* screen);
    void XuatVuNo(SDL_Renderer* screen);
    void LayHieuUng();

    void CaiFrame(const int& f) {frame = f;}
    int LayFrameW() const {return frame_w;}
    int LayFrameH() const {return frame_h;}


private:
    int frame;
    int frame_w;
    int frame_h;
    SDL_Rect hieuung[FRAME];

};


#endif // NO_H_INCLUDED
