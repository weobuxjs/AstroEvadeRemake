#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
class player
{
public:

    SDL_Rect idle[4];
    
    player(SDL_Texture*texture,SDL_Texture*shadow, int x,int y)
    {
        HP=100;
        tex=texture;
        this->shadow=shadow; 
        dst={x,y,15*6,25*6};
        src={0,0,15,25};
        HitboxUp={x+35,y,20,20};
        Hitbox={x+20,y+20,15*6-40,25*4-7-13};
        HitboxLeft={x+20+15*6-40,y+50,20,50};
        HitboxRight={x,y+50,20,50};
        ShadowRect.x=dst.x;
        ShadowRect.y=dst.y+40;
        ShadowRect.h=dst.h;
        ShadowRect.w=dst.w;
        is_dead=false;
        SetClip();
    }
    void SetClip()
    {
        for(int i=0;i<4;i++)
        {
            idle[i].x=i*15;
            idle[i].y=0;
            idle[i].w=15;
            idle[i].h=25;
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
    double GetHP(){ return HP; }
    void SetHP(int x)
    {
        HP=x;
    }
    void ChangeX(double x)
    {
        if(dst.x>=0)
        {
            dst.x=dst.x+x;
            HitboxUp.x=dst.x+35;
            HitboxLeft.x=dst.x+20+15*6-40;
            HitboxRight.x=dst.x;
            Hitbox.x=dst.x+20;
            ShadowRect.x=dst.x;
        }
        if(dst.x>=0 && dst.x>=1200)
        {
            dst.x=-dst.w;
            HitboxUp.x=dst.x+35;
            HitboxLeft.x=dst.x+20+15*6-40;
            HitboxRight.x=dst.x;
            Hitbox.x=dst.x+20;
            ShadowRect.x=dst.x;
        }
        if(dst.x<0 && dst.w>=0)
        {
            dst.x=dst.x+x;
            HitboxUp.x=dst.x+35;
            HitboxLeft.x=dst.x+20+15*6-40;
            HitboxRight.x=dst.x;
            Hitbox.x=dst.x+20;
            ShadowRect.x=dst.x; 
        }
        if(dst.x+dst.w<0)
        {
            dst.x=1200;
            HitboxUp.x=dst.x+35;
            HitboxLeft.x=dst.x+20+15*6-40;
            HitboxRight.x=dst.x;
            Hitbox.x=dst.x+20;
            ShadowRect.x=dst.x; 
        }
  
    }
    void SetX(int x)
    {
        dst.x+=(x-dst.x);
        ShadowRect.x+= (x-ShadowRect.x);
    }
    bool get_is_dead()
    {
        return is_dead;
    }
    void set_is_dead(bool a)
    {
        is_dead=a;
    }
    void SetY(int y)
    {
        dst.y+=(y-dst.y);
        ShadowRect.y+=(y-ShadowRect.y)+40;
    }
    void ChangeY(int x)
    {
        Hitbox.y+=x;
        dst.y+=x;
        ShadowRect.y+=x;
    }
    void ChangeHP(int x)
    {
         HP=(HP+x);
         if(HP>100)
         {
            HP=100;
         }
    }
    SDL_Texture *GetTex()
    {
        return tex;
    }
    SDL_Rect* GetShadow()
    {
        return &ShadowRect;
    }
    SDL_Rect* GetDst()
    {
        return &dst;
    }
    SDL_Rect* GetSrc()
    {
        return &src;
    }
    SDL_Texture*GetShadowTexture()
    {
        return shadow;
    }
    void HandleInput(SDL_Event event)
    {
        if(event.type==SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_d:
                    if(is_dead==false) ChangeX(20);
                    break;
                case SDLK_a:
                    if(is_dead==false) ChangeX(-20);
                    break;
                case SDLK_LEFT:
                    if(is_dead==false) ChangeX(-20);
                    break;
                case SDLK_RIGHT:
                    if(is_dead==false) ChangeX(20);
                    break;               
            }
        }
    }
    SDL_Rect HitboxUp;
    SDL_Rect Hitbox;
    SDL_Rect HitboxLeft;
    SDL_Rect HitboxRight;
private:
    bool is_dead;
    SDL_Texture*tex;
    SDL_Texture*shadow;
    SDL_Rect src,dst;
    SDL_Rect ShadowRect;
    int xVal;
    int yVal;
    int HP;
};