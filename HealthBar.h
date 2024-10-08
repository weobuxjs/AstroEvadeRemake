#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
class HealthBar
{
public:
    SDL_Rect Clip[5];
    HealthBar(int x,int y,SDL_Texture*tex)
    {
        dst={x,y,256,32};
        HealthBar_Texture=tex;
        SetClip();
    }
    void SetClip()
    {
        for(int i=0;i<5;i++)
        {
            Clip[i].x=i*128;
            Clip[i].y=0;
            Clip[i].w=128;
            Clip[i].h=64;

        }
    }
    SDL_Texture* GetTex()
    {
        return HealthBar_Texture;
    }
    SDL_Rect* GetDst()
    {
        return &dst;
    }
private:
    SDL_Rect dst;
    SDL_Texture*HealthBar_Texture;
};