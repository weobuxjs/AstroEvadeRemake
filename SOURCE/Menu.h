#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
class Menu
{
public:
    bool isQuit=false,isReplay=false;

    Menu(SDL_Texture*BUTTON,SDL_Texture*BACKGROUND)
    {
        this->BUTTON=BUTTON;
        this->BACKGROUND=BACKGROUND;
        isClicked=false;
        isQuit=false;
        SetClip();
        inGameDst={450,400,576/2,288/2};
        quitDst={450,600,576/2,288/2};
        replayDst={450,400,576/2,288/2};
    }
    void SetClip()
    {
        for(int i=0;i<3;i++)
        {
            ingame[i].x=i*192;
            ingame[i].y=0;
            ingame[i].w=192;
            ingame[i].h=96;
            
            replay[i].x=i*192;
            replay[i].y=192;
            replay[i].w=192;
            replay[i].h=96;

            quit[i]={i*192,96,192,96};
        }
    }
    SDL_Rect inGameDst,replayDst,quitDst;
    SDL_Texture*BUTTON;
    SDL_Texture*BACKGROUND;
    SDL_Rect ingame[3],replay[3],quit[3];
    bool isClicked;
};