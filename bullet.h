#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include "player.h"
class Bullet
{
public:
    SDL_Rect frame[4];
    int angle;
    int SpawnY;
    Bullet(SDL_Texture* texture,player& player)
    {
        tex=texture;
        dst.x=player.GetX()+35;
        dst.y=player.GetY()-25;
        dst.w=20;
        dst.h=40;
        SpawnY=player.GetY()-25;
        SetClip();
        length=0;
        length1=0;
        int angle=0;
        is_bounce=false;
        if(rand()%12>6) bounce=false;
        if(rand()%12<=6) bounce=true; 
    }
    void SetClip()
    {
        for(int i=0;i<4;i++)
        {
            frame[i].x=i*5;
            frame[i].y=0;
            frame[i].w=5;
            frame[i].h=10;
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
    void ChangeX(int x)
    {
        dst.x+=x;
    }
    void ChangeY(int x)
    {
        dst.y+=x;
    }
    bool get_is_bounce()
    {
        return is_bounce;
    }
    void set_is_bounce(bool bounce)
    {
        this->is_bounce=bounce;
    }
    SDL_Texture *GetTex()
    {
        return tex;
    }
    SDL_Rect* GetDst()
    {
        return &dst;
    }
    void set_is_move(bool move)
    {
        is_move=move;
    }
    bool get_is_move()
    {
        return is_move;
    }
    int length;
    int length1;
    bool bounce;
private:
    SDL_Rect dst;
    SDL_Texture*tex;
    bool is_move;
    bool is_bounce;
};