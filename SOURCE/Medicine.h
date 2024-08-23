#pragma once
#include<SDL.h>
#include<iostream>
#include<SDL_image.h>
class Medicine
{
public:
    Medicine(int x,int y,SDL_Texture*tex)
    {
        is_move=true;
        dst={x,y,70,70};
        src={0,0,487,513};
        this->Tex=tex;
    }
    int GetY()
    {
        return dst.y;
    }
    SDL_Rect* GetDst()
    {
        return &dst;
    }
    SDL_Rect*GetSrc()
    {
        return  &src;
    }
    SDL_Texture*GetTex()
    {
        return Tex;
    }
    void ChangeY(int x)
    {
        dst.y+=x;
    }
    

private:
    bool is_move;
    SDL_Texture* Tex;
    SDL_Rect dst,src; 
};