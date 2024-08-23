#include<iostream>
#include<math.h>
#include"MathFunc.h"
#include<SDL.h>
#include<SDL_image.h>
#include"RenderWindow.h"
#include"player.h"
using namespace std;
int main(int argc,char*argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        cout<<SDL_GetError()<<endl;
    }
    RenderWindow window("Test",1200,800);
    bool Run=true;
    SDL_Event event;
    SDL_Texture*playertex=window.loadTexture("res/spaceship_blue_spritesheet.png");
    player Ship(playertex,NULL,400,600);

    while(Run)
    {
        int x,y;
        window.color(255,0,0,0);
        window.clear();
        while(SDL_PollEvent(&event))
        {
            
            if(event.type==SDL_QUIT)
            {
                Run=false;
            }
        }
        SDL_GetMouseState(&x,&y);
        double a=Ship.GetY()-y;
        double b=x-Ship.GetX();
        int angle;
        angle=90*b/abs(b)-atan(a/b) *180/3.14;
        cout<<angle<<" "<<a<<" "<<b<<endl;
        window.rotate(Ship,angle);
        window.display();
    }
    return 0;
}