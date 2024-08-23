#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL.h>
#include<SDL_image.h>
#include"bullet.h"
class asteroid
{
public:
    int xRand;
    int Cangle;
    SDL_Point Spawn;
    asteroid(SDL_Texture*texture ,SDL_Texture*shadow,int x,int y,int w,int h,int angle)
    {
        Spawn={x,y};
        dst={x,y,w,h};
        ShadowRect=dst;
        ShadowRect.y+=20;
        this->shadow=shadow;
        this->texure=texture;
        is_move=true;
        xRand=rand()%5;
        this->Cangle=angle;
        if(xRand>=4)
        {
            xRand=rand()%4;
        }
        if(xRand<4)
        {
            xRand=-rand()%4;
        }
    }
    int GetX()
    {
        return dst.x;
    }
    int GetY()
    {
        return dst.y;
    }
    int GetW()
    {
        return dst.w;
    }
    int GetH()
    {
        return dst.h;
    }
    void ChangeAngle()
    {
        angle+=Cangle;
    }
    void ChangeX(int x)
    {
        dst.x+=x;
        ShadowRect.x+=x;
    }
    void ChangeY(int x)
    {
        dst.y+=x;
        ShadowRect.y+=x;
    }
    SDL_Texture *GetTex()
    {
        return texure;
    }
    SDL_Texture*GetShadow()
    {
        return shadow;
    }
    SDL_Rect* GetDst()
    {
        return &dst;
    }
    SDL_Rect* GetShadowDst()
    {
        return &ShadowRect;
    }
    void set_is_move(bool move)
    {
        this->is_move=move;
    }
    void SetY(int y)
    {
        dst.y=y;
    }
    int GetAngle()
    {
        return angle;
    }
    void SetX(int x)
    {
        dst.x=x;
    }
    bool get_is_move()
    {
        return is_move;
    }
private:
    SDL_Texture*texure;
    SDL_Texture*shadow;
    SDL_Rect dst;
    SDL_Rect ShadowRect;
    int angle;
    bool is_move;
};