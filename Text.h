#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>
using namespace std;
struct Text
{
    SDL_Color Color;
    TTF_Font* font;
    SDL_Texture* TextTexture;
    SDL_Surface* TextSurface;
    string Text;
    SDL_Rect pos;
    void free()
    {
        SDL_DestroyTexture(TextTexture);
        SDL_FreeSurface(TextSurface);
    }
};