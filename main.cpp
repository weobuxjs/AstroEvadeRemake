#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<vector>
#include<SDL_ttf.h>
#include<string>
#include<math.h>
#include"RenderWindow.h"
#include"player.h"
#include"bullet.h"
#include"asteroid.h"
#include"HealthBar.h"
#include"Medicine.h"
#include"Text.h"
#include"MathFunc.h"
#include"Menu.h"
using namespace std;
int main(int argc,char*argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) !=0){
        cout<<SDL_GetError()<<endl;
        return 0;
    }
    TTF_Init();
    int angle=0;
    RenderWindow window("Astro Evade Remake",1200,800);
    bool Loop=true;
    SDL_Event event;
    Mix_OpenAudio(48000,AUDIO_S16SYS,2,2048);
    SDL_Texture*ship=window.loadTexture("res/spaceship_blue_spritesheet.png");
    SDL_Texture*shadow=window.loadTexture("res/spaceship_shadow_spritesheet.png");
    Mix_Music*doors=Mix_LoadMUS("res/doors.mp3");
    player player (ship,shadow,400,600);
    SDL_Texture * bullet_texture=window.loadTexture("res/spaceship_blue_projectile_spritesheet.png");
    SDL_Texture*HealthBar_Texture=window.loadTexture("res/HealthBar.png");
    SDL_Texture*HealTexture= window.loadTexture("res/Medicine.png");
    Mix_Chunk*background =Mix_LoadWAV("res/music2.wav");
    Mix_Chunk*shoot =Mix_LoadWAV("res/sfx_exp_short_hard16.wav");
    Mix_Chunk*asteroidBoom = Mix_LoadWAV("res/asteroid_explosion.wav");
    Mix_Chunk*GetDamage=Mix_LoadWAV("res/sfx_wpn_laser7.wav");
    vector<Bullet*>bullet_list;
    vector<pair<int,int>>size={make_pair(29,29),make_pair(21,13*1.5),make_pair(13.2,12)};
    vector<SDL_Texture*>Texture={window.loadTexture("res/large.png"),window.loadTexture("res/small3.png"),window.loadTexture("res/small4.png")};
    vector<SDL_Texture*>ShadowTexture={window.loadTexture("res/large1_shadow.png"),window.loadTexture("res/small3_shadow.png"),window.loadTexture("res/small4_shadow.png")};
    HealthBar HealthBar(0,750,HealthBar_Texture);
    vector<Medicine*>MedicineVector;
    Mix_Music * Healing= Mix_LoadMUS("res/Healing.mp3");
    Mix_Music* Click= Mix_LoadMUS("res/Click1.mp3");
    Text ScoreText;
    ScoreText.font= TTF_OpenFont("res/Poppins-SemiBold.ttf",200);
    ScoreText.pos.x=0;
    ScoreText.pos.y=0;
    ScoreText.pos.w=0;
    ScoreText.pos.h=25;
    ScoreText.Color={255,255,255};
    int MAP[24][45]; 
    int ScoreCounter=0;
    vector<asteroid*>AsteroidVector;
    bool isF5=false;
    bool isESC=false;
    Menu menu(window.loadTexture("res/Button.png"),window.loadTexture("res/Doge.jpg"));
    freopen("res/MAP.txt","r",stdin);
    for(int i=0;i<24;i++)
    {
        for(int j=0;j<45;j++)
        {
            cin>>MAP[i][j];
        }
    }
    for(int i=0;i<3;i++)
    {
        if(!ShadowTexture[i])
        {
            cout<<"Cant load texture: "<<SDL_GetError()<<endl;
        }
        if(!Texture[i])
        {
            cout<<"Cant load texture: "<<SDL_GetError()<<endl;
        }
    }
    int frame=0;
    int framebull=0;
    int x=0,y=0;
    SDL_Rect HealthColor;
    srand(time(0));
    int MouseX,MouseY;
    Mix_PlayChannel(-1,background,-1);
    int Start=SDL_GetTicks();
    while(Loop)
    {  
            if(menu.isReplay==true)
            {
                player.set_is_dead(false);
                player.SetHP(100);
                menu.isReplay=false;
                AsteroidVector.clear();
                bullet_list.clear();
                MedicineVector.clear();
                player.SetX(400);
                x=0;
                y=0;
                Start=SDL_GetTicks();
                isESC=false;
                player.xVel=player.yVel=0;
            }

            if(!isESC && menu.isClicked)
            {
                
                if(x==45 && y==24)
                { 
                    x=0,y=0;      
                }
                if(x==45)
                {
                    x=0;
                    y++;
                }
            }
            
            SDL_Rect HealthColor={0,750,player.GetHP()*2.56,32};
            int random=rand()%3;
            if(!player.get_is_dead() && isESC==false && menu.isClicked)
            {

                int currenttime=SDL_GetTicks();
                ScoreCounter=(currenttime-Start)/1000;
            
            }
                ScoreText.Text=to_string(ScoreCounter);
                ScoreText.pos.w=12*GetChuSo(ScoreCounter);
                ScoreText.TextSurface=TTF_RenderText_Solid(ScoreText.font,ScoreText.Text.c_str(),ScoreText.Color);
                ScoreText.TextTexture=window.rendersurface(ScoreText.TextSurface);
                if(MAP[y][x]==2)
                { 
                    asteroid*gAsteroid= new asteroid(Texture[random],ShadowTexture[random],x*26,-500,size[random].first,size[random].second,rand()%10+3);
                    AsteroidVector.push_back(gAsteroid);
                }
                if(MAP[y][x]==3 && rand()%12==3)
                {
                    asteroid*gAsteroid= new asteroid(Texture[0],ShadowTexture[0],x*26,-1000,size[0].first,size[0].second,50);
                    AsteroidVector.push_back(gAsteroid);
                } 
                if(MAP[y][x]==1 && player.GetHP()<=15)
                {
                    Medicine *medicine= new Medicine(rand()%900,0,HealTexture);
                    MedicineVector.push_back(medicine);
                }
            
            
            window.color(158,13,13,0.8);
             window.clear();
            window.color(0xFF,0xFF,0xFF,0xFF);
            
            while(SDL_PollEvent(&event))
            {
                if(event.type==SDL_QUIT)
                {
                    Loop=false;
                }
                if(!isESC) player.HandleInput(event);
                if(event.type==SDL_KEYDOWN && menu.isClicked==true)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_F5:
                            isF5=!isF5;
                            break;
                        case SDLK_ESCAPE:
                            isESC=!isESC;
                            player.xVel =0;
                            break;
                    }
                }
                if(event.type==SDL_MOUSEMOTION)
                {
                    SDL_GetMouseState(&MouseX,&MouseY);
                }
                if(event.type==SDL_MOUSEBUTTONDOWN && menu.isClicked==false)
                {
                     if(window.CheckCoillision(MouseX,MouseY,menu.inGameDst))
                     {
                        menu.isClicked=true;
                        x=0;
                        Start=SDL_GetTicks();
                        Mix_PlayMusic(Click,0);
                     }
                     if(window.CheckCoillision(MouseX,MouseY,menu.quitDst)==true)
                     {
                        Mix_PlayMusic(Click,0);
                        Loop=false;
                     }
                     
                }
                if(event.type==SDL_MOUSEBUTTONDOWN)
                {
                    if(player.get_is_dead()==true)
                    {
                     if(window.CheckCoillision(MouseX,MouseY,menu.quitDst)==true)
                     {
                        Mix_PlayMusic(Click,0);
                        menu.isClicked=false;
                     }
                     if(window.CheckCoillision(MouseX,MouseY,menu.replayDst))
                     {
                        Mix_PlayMusic(Click,0);
                        menu.isReplay=true;
                     }
                    }
                    if(isESC)
                    {
                        if(window.CheckCoillision(MouseX,MouseY,menu.quitDst)==true)
                        {
                            Mix_PlayMusic(Click,0);
                            menu.isClicked=false;
                        }
                        if(window.CheckCoillision(MouseX,MouseY,menu.replayDst))
                        {
                            Mix_PlayMusic(Click,0);
                            menu.isReplay=true;
                        }
                    }
                }
                if(event.type==SDL_MOUSEBUTTONDOWN && menu.isClicked)
                {
                    if(event.button.button==SDL_BUTTON_LEFT)
                    {
                        if(player.get_is_dead()==false && !isESC)
                        {
                            Bullet* bullet = new Bullet (bullet_texture,player);
                            bullet->set_is_move(true);
                            bullet->set_is_bounce(false);
                            bullet->angle=0;
                            bullet_list.push_back(bullet);
                             Mix_PlayChannel(-1,shoot,0);
                        }
                    }
                }
            }
            if(menu.isClicked==true)
            {
                if(player.GetHP()<=0)
                {
                    player.set_is_dead(true);
                }        
                for(int i=0;i<AsteroidVector.size();i++)
                {
                    if(AsteroidVector[i]!=NULL)
                    {
                       if(player.get_is_dead()==false && !isESC)
                       {
                            AsteroidVector[i]->ChangeY(AsteroidVector[i]->Cangle);
                            AsteroidVector[i]->ChangeX(AsteroidVector[i]->xRand);
                            AsteroidVector[i]->ChangeAngle();
                        }
                        window.rotate(AsteroidVector[i],AsteroidVector[i]->GetAngle()); 
                        if(isF5==true) 
                        {
                            window.drawrect(*AsteroidVector[i]->GetDst());
                            window.drawline(AsteroidVector[i]->Spawn.x+AsteroidVector[i]->GetW(),0,AsteroidVector[i]->GetX()+AsteroidVector[i]->GetW()/2,AsteroidVector[i]->GetY());
                        }
                        if(window.CheckCoillision(player,AsteroidVector[i])==true)
                        {

                            for(int j=0;j<3;j++)
                            {
                                if(AsteroidVector[i]->GetTex()==Texture[j])
                                {
                                    if(j==0)
                                    {
                                    player.ChangeHP(-9- AsteroidVector[i]->Cangle);
                                    break;
                                    }
                                    if(j==1)
                                    {
                                        player.ChangeHP(-3.9- AsteroidVector[i]->Cangle/3);
                                        break;
                                    }
                                    if(j==2)
                                    {
                                        player.ChangeHP(-1.2- AsteroidVector[i]->Cangle/2);
                                        break;
                                    }
                                }
                            }
                            AsteroidVector[i]->set_is_move(false);
                            Mix_PlayChannel(-1,GetDamage,0);
                        }

                        if(AsteroidVector[i]->GetY()>1900)
                        {
                            AsteroidVector.erase(AsteroidVector.begin()+i);
                        }
                        if(AsteroidVector[i]->get_is_move()==false)
                        {
                            AsteroidVector.erase(AsteroidVector.begin()+i);
                        }
                    } 
                }
                for(int i=0;i<bullet_list.size();i++)
                {
                    for(int j=0;j<AsteroidVector.size();j++)
                    {
                        asteroid*gAsteroid=AsteroidVector[j];
                        if(gAsteroid!=NULL)
                        {
                            if(window.CheckCoillision(gAsteroid,bullet_list[i])==true)
                            {
                                gAsteroid->set_is_move(false);
                                if(gAsteroid->GetTex()!=Texture[0])
                                {
                                    bullet_list[i]->set_is_move(false);
                                }
                                if(gAsteroid->GetTex()==Texture[0])
                                {
                                    if(gAsteroid->Cangle<5)
                                    {
                                        bullet_list[i]->set_is_move(false);
                                    }
                                    if(gAsteroid->Cangle>=5)
                                    {
                                        bullet_list[i]->length=bullet_list[i]->SpawnY-AsteroidVector[j]->GetY();
                                        bullet_list[i]->set_is_bounce(true);
                                        if(bullet_list[i]->bounce==true) bullet_list[i]->angle= 180-atan(1.5)*180/3.14;
                                        else if(bullet_list[i]->bounce==false) bullet_list[i]->angle= -180+atan(1.5)*180/3.14;
                                        else bullet_list[i]->angle= 180-atan(1.5)*180/3.1;
                                    }
                                }
                                Mix_PlayChannel(-1,asteroidBoom,0);
                            }
                            if(gAsteroid->get_is_move()==false)
                            {
                                AsteroidVector.erase(AsteroidVector.begin()+j);
                                delete gAsteroid;
                            }
                        }
                    }
                    if(framebull/4>=3) framebull=0;
                    window.rotate(bullet_list[i],bullet_list[i]->frame[framebull/4]);
                    if(isF5==true)
                    {
                        window.drawrect(*bullet_list[i]->GetDst());
                    }
                    framebull++;
                    if(window.CheckCoillision(player,AsteroidVector[i])==true && isESC==false)
                    {
                        player.ChangeHP(-50);
                        AsteroidVector[i]->set_is_move(false);
                    }
                    if(bullet_list[i]!=NULL && !isESC)
                    {
                        if(bullet_list[i]->GetY()<-100)
                        {
                            bullet_list[i]->set_is_move(false);
                        }
                        if(bullet_list[i]->GetY()>1900)
                        {
                            bullet_list[i]->set_is_move(false);
                        }
                        if(bullet_list[i]->get_is_move()==true && bullet_list[i]->get_is_bounce()==false)
                        {
                            bullet_list[i]->ChangeY(-10);
                        }
                        if(bullet_list[i]->get_is_move()==true&& bullet_list[i]->get_is_bounce()==true)
                        {
                            bullet_list[i]->ChangeY(10);
                            if(bullet_list[i]->bounce==true ) bullet_list[i]->ChangeX(15);
                            if(bullet_list[i]->bounce==false) bullet_list[i]->ChangeX(-15);
                            else bullet_list[i]->ChangeX(15);
                        }
                        if(bullet_list[i]->get_is_move()==false)
                        {
                            bullet_list.erase(bullet_list.begin()+i);
                        }
                    }
                }
                if(player.get_is_dead()==false)
                {  
                for(int i=0;i<MedicineVector.size();i++)
                {
                    if(MedicineVector[i]!=NULL)
                    {
                        if(isF5==true)
                        {
                            window.drawrect(*MedicineVector[i]->GetDst());
                        }
                        window.render(MedicineVector[i]);
                        if(!isESC)MedicineVector[i]->ChangeY(5);
                        if(window.CheckCoillision(player,MedicineVector[i])==true)
                        {
                            player.ChangeHP(15);
                            MedicineVector.erase(MedicineVector.begin()+i);
                            Mix_PlayMusic(Healing,0);
                        }
                        if(MedicineVector[i]->GetY()>=800)
                        {
                        MedicineVector.erase(MedicineVector.begin()+i); 
                        }
                    }
                }
                }
                if(frame/5>=4) frame=0;
                if(player.get_is_dead()==false && isESC==false) window.render(player,player.idle[frame/5]);
                else if(player.get_is_dead()==true || isESC==true) 
                {
                   window.render(player,player.idle[0]); 
                }
                window.draw_fullrect(HealthColor);
                if(player.GetHP()<=100 && player.GetHP()>75) window.render(HealthBar,HealthBar.Clip[0]);
                if(player.GetHP()<=75 && player.GetHP()>50) window.render(HealthBar,HealthBar.Clip[1]);
                if(player.GetHP()<=50 && player.GetHP()>25) window.render(HealthBar,HealthBar.Clip[2]);
                if(player.GetHP()<=25 && player.GetHP()>0) window.render(HealthBar,HealthBar.Clip[3]);
                if(player.GetHP()<=0) window.render(HealthBar,HealthBar.Clip[4]);
                if(!isESC) player.update();     
                window.render(ScoreText); 
                if(isF5==true)
                {
                    window.drawrect(ScoreText.pos);  
                    window.drawrect(*player.GetDst());
                    window.drawrect(player.Hitbox);
                    window.drawrect(player.HitboxLeft);
                    window.drawrect(player.HitboxRight);
                    window.drawrect(player.HitboxUp);
                }
            }
            
            frame++;
            if(menu.isClicked==false)
            {
                window.render(menu);
                SDL_SetWindowTitle(window.GetWindow(),"Are You Ready To Play This Game?");
            } 
            if((player.get_is_dead()==true|| isESC==true) && menu.isClicked==true )
            {
                window.renderQuit(menu);
            }
            x= (x+1)%46;
            window.display();
            ScoreText.free();
            // SDL_Delay(16);
        }   
    Mix_FreeMusic(doors);
    Mix_FreeChunk(shoot);
    Mix_FreeChunk(background);
    Mix_FreeChunk(asteroidBoom);
    SDL_DestroyTexture(HealthBar_Texture);
    
    window.cleanup();
    SDL_Quit();
    return 0;
}