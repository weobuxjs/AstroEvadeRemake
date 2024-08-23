#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include"player.h"
#include"bullet.h"
#include"asteroid.h"
#include"HealthBar.h"
#include"Medicine.h"
#include"Text.h"
#include"Menu.h"
#define PI 3.14
using namespace std;
class RenderWindow
{
public:
    RenderWindow(const char*title,int x,int y)
    {
        window=SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,x,y,SDL_WINDOW_SHOWN);
        renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED||SDL_RENDERER_PRESENTVSYNC);
        if(window==NULL)
        {
            cout<<"ERROR: "<<SDL_GetError();
        }
        if(renderer==NULL)
        {
            cout<<"ERROR: "<<SDL_GetError();
        }
    }
    SDL_Texture*loadTexture(const char*filePath)
    {
        return IMG_LoadTexture(renderer,filePath);;
    }
    void cleanup()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }
    void clear()
    {
        SDL_RenderClear(renderer);
    }
    void render(player & player,SDL_Rect currentframe)
    {
        SDL_RenderCopy(renderer,player.GetShadowTexture(),&currentframe,player.GetShadow());
        SDL_RenderCopy(renderer,player.GetTex(),&currentframe,player.GetDst());
    }
    void render(Bullet* bullet,SDL_Rect currentframe)
    {
        SDL_RenderCopy(renderer,bullet->GetTex(),&currentframe,bullet->GetDst());
    }
    void render(HealthBar gHealthBar, SDL_Rect currentframe)
    {
        SDL_RenderCopy(renderer,gHealthBar.GetTex(),&currentframe,gHealthBar.GetDst());
    }
    void render(Text ScoreText)
    {
        SDL_RenderCopy(renderer,ScoreText.TextTexture,NULL,&ScoreText.pos);
    }
    void render(Medicine*Medicine)
    {
        SDL_RenderCopy(renderer,Medicine->GetTex(),Medicine->GetSrc(),Medicine->GetDst());
    }
    void renderQuit(Menu menu)
    {
        SDL_RenderCopy(renderer,menu.BUTTON,&menu.replay[2], &menu.replayDst);
        SDL_RenderCopy(renderer,menu.BUTTON,&menu.quit[2],&menu.quitDst);
    }
    void render(Menu menu)
    {
        SDL_RenderCopy(renderer,menu.BACKGROUND,NULL,NULL);
        SDL_RenderCopy(renderer,menu.BUTTON,&menu.ingame[2],&menu.inGameDst);
        SDL_RenderCopy(renderer,menu.BUTTON,&menu.quit[2],&menu.quitDst);
    }
    void rotate(player&player,int angle)
    {
        SDL_RenderCopyEx(renderer,player.GetTex(),&player.idle[0],player.GetDst(),angle,NULL,SDL_FLIP_NONE);
    }
    void rotate(Bullet*bullet,SDL_Rect currentframe)
    {
        SDL_RenderCopyEx(renderer,bullet->GetTex(),&currentframe,bullet->GetDst(),bullet->angle,NULL,SDL_FLIP_NONE);
    }
    void rotate(asteroid*asteroid,int angle)
    {
        SDL_RenderCopyEx(renderer,asteroid->GetShadow(),NULL,asteroid->GetShadowDst(),angle,NULL,SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer,asteroid->GetTex(),NULL,asteroid->GetDst(),angle,NULL,SDL_FLIP_NONE);
    }


    void rotate(player&player,int angle,SDL_Point center,SDL_RendererFlip flip)
    {
        SDL_RenderCopyEx(renderer,player.GetTex(),player.GetSrc(),player.GetDst(),angle,&center,flip);
    }
    void display()
    {
        SDL_RenderPresent(renderer);
    }
    void color(int r,int g,int b,int a)
    {
        SDL_SetRenderDrawColor(renderer,r,g,b,a);
    }
    void drawrect(SDL_Rect rect)
    {
        SDL_RenderDrawRect(renderer,&rect);
    }
    void draw_fullrect(SDL_Rect rect)
    {
        SDL_RenderFillRect(renderer,&rect);
    }
    void drawline(int x1,int y1,int x2, int y2)
    {
        SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
    }
    SDL_Texture* rendersurface(SDL_Surface*surface)
    {
        SDL_Texture*tex=SDL_CreateTextureFromSurface(renderer,surface);
        return tex;
    }
    bool CheckCoillision(player&player,Medicine*medicine)
    {
        if(CheckCoillision(player.Hitbox,*medicine->GetDst())==true || CheckCoillision(player.HitboxLeft,*medicine->GetDst())==true|| CheckCoillision(player.HitboxRight,*medicine->GetDst())==true || CheckCoillision(player.HitboxUp,*medicine->GetDst())==true)
        {
            return true;
        }
        return false;
    }
    bool CheckCoillision(player&player, Bullet*bullet)
    {
        if(CheckCoillision(*bullet->GetDst(),player.Hitbox)) return true;
        if(CheckCoillision(*bullet->GetDst(),player.HitboxUp)) return true;
        if(CheckCoillision(*bullet->GetDst(),player.HitboxLeft)) return true;
        if(CheckCoillision(*bullet->GetDst(),player.HitboxRight)) return true;
        return false;
    }
    bool CheckCoillision(asteroid* asteroid, Bullet* Bullet)
    {
        if(CheckCoillision(*asteroid->GetDst(),*Bullet->GetDst())==true)
        {
            return true;
        }
        return false;
    }
    bool CheckCoillision(int x,int y,SDL_Rect Button)
    {
        if(x<Button.x ) return false;
        if(x>Button.x+Button.w) return false;
        if(y>Button.y+ Button.h) return false;
        if(y<Button.y) return false;
        return true;
    }
    bool CheckCoillision(SDL_Rect a,SDL_Rect b)
    {
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;
        leftA = a.x;
        rightA = a.x + a.w;
        topA = a.y;
        bottomA = a.y + a.h;
        leftB = b.x;
        rightB = b.x + b.w;
        topB = b.y;
        bottomB = b.y + b.h;
        if( bottomA <= topB )
        {
            return false;
        }
        if( topA >= bottomB )
        {
            return false;
        }
        if( rightA <= leftB )
        {
            return false;
        }
        if( leftA >= rightB )
        {
            return false;
        }
        return true;
     }
     bool CheckCoillision(player&player, asteroid*asteroid)
     {
        if(CheckCoillision(player.Hitbox,*asteroid->GetDst())==true)
        {
            return true;
        }
        if(CheckCoillision(player.HitboxUp,*asteroid->GetDst())==true)
        {
            return true;
        }
        if(CheckCoillision(player.HitboxLeft,*asteroid->GetDst())==true)
        {
            return true;
        }
        if(CheckCoillision(player.HitboxRight,*asteroid->GetDst())==true)
        {
            return true;
        }
        return false;
     }
    SDL_Window*GetWindow()
    {
        return window;
    }
private:
    SDL_Window*window;
    SDL_Renderer*renderer;
};