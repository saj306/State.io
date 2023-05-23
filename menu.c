#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "map.h"
#include "soldiers.h"
#include "extra.h"
#include "potion.h"
#include "username.h"
#include "menu.h"
#include "leaderboard.h"
#define new_max(x,y) (((x) >= (y)) ? (x) : (y))
#define new_min(x,y) (((x) <= (y)) ? (x) : (y))
#define FPS 60

void ready_map(SDL_Renderer *renderer , int** running , int* flag2 , int* flag3)
{
    int x=0 , y=0 ;
    int temp = 1;
    SDL_Event Event ;
    char numbere[50] = {'\0'};
    int num_ready_map=0;
    while(**running)
    {
        while (SDL_PollEvent(&Event)) 
        {
            switch (Event.type) 
            {
                case SDL_QUIT:
                    **running = 0;
                    break;
                case SDL_TEXTINPUT:
                    if(strlen(numbere) +1 < 50)
                    {
                        strcat(numbere,Event.text.text);
                    }
                    break;
                case SDL_KEYDOWN:
                    if(Event.key.keysym.sym == SDLK_BACKSPACE)
                    {
                        if(strlen(numbere) > 0)
                        {
                            numbere[strlen(numbere) -1 ] = '\0' ;
                        }
                    }
                    else if(Event.key.keysym.sym == SDLK_KP_ENTER  || Event.key.keysym.sym == SDLK_RETURN)
                    {
                       
                        num_ready_map = atoi(numbere);
                        *flag2 = 0;
                        *flag3 = 1;
                        make_ready_map(num_ready_map);
                        return;
                        
                        
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (Event.button.button == SDL_BUTTON_LEFT) 
                    {
                        SDL_GetMouseState(&x , &y);
                        if((x > 35) && (x < 185) && (y > 650) && (y <703))
                        {
                            return;
                        }
                       
                    }
                break;
                
            }
        
        }
        char temmp[20];
        sprintf(temmp,"%d" ,led.user[active_user_id].score );
        SDL_SetRenderDrawColor(renderer, 238, 237, 237, 255);
        SDL_RenderClear(renderer);
        image(renderer , "ff.png" , 0 , 0);
        image(renderer , "menu.png" , 425 , 100);
        image(renderer , "border.png" , 350 , 230);
        image(renderer , "border5.png" , 457 , 337);
        image(renderer , "picture2.png" , 35 , 35);
        neveshte(renderer , "Username :" , 215 , 60 , 19 , 239 ,214 ,10 ,255);
        neveshte(renderer , led.user[active_user_id].name , 315 , 60 , 23 , 255 ,255 ,255 ,255);
        neveshte(renderer , "Score :" , 196 , 111 , 19 , 239 ,214 ,10 ,255);
        neveshte(renderer , temmp , 244 , 111 , 20 , 255 ,255 ,255 ,255);
        neveshte(renderer , "Choose a ready map number:" , 600 , 280 , 30 , 195 ,234 ,129 ,255);
        neveshte(renderer , numbere , 600 , 350 , 30 , 255 ,255,255 ,255);
        image(renderer , "home.png" , 35 , 650);
        neveshte(renderer , "Your number must be between 1 and 5.", 600 , 410 ,18, 245 , 135 , 232 , 150);
        neveshte(renderer , "If you want your saved map enter number 6.", 600 , 440 ,18, 247 , 197 , 115 , 150);
        image(renderer , "warning.png" , 370 , 430);
        neveshte(renderer , "Press the Enter key to continue", 600 , 470 ,18, 104 , 124 , 142 , 150);

      
        SDL_RenderPresent(renderer);
        SDL_Delay(FPS / 1000);
    }
}
void random_map(SDL_Renderer *renderer , int** running , int* flag2 , int* flag3)
{
    int x=0 , y=0 ;
    int temp = 1;
    SDL_Event Event ;
    char numbere[50] = {'\0'};
    
    while(**running)
    {
        while (SDL_PollEvent(&Event)) 
        {
            switch (Event.type) 
            {
                case SDL_QUIT:
                    **running = 0;
                    break;
                case SDL_TEXTINPUT:
                    if(strlen(numbere) +1 < 50)
                    {
                        strcat(numbere,Event.text.text);
                    }
                    break;
                case SDL_KEYDOWN:
                    if(Event.key.keysym.sym == SDLK_BACKSPACE)
                    {
                        if(strlen(numbere) > 0)
                        {
                            numbere[strlen(numbere) -1 ] = '\0' ;
                        }
                    }
                    else if(Event.key.keysym.sym == SDLK_KP_ENTER  || Event.key.keysym.sym == SDLK_RETURN)
                    {
                        if(temp)
                        {
                            temp =0;
                            save_map.co = atoi(numbere);
                            numbere[0] = '\0';

                        }
                        else
                        {
                            save_map.op = atoi(numbere) + 1;
                            *flag2 = 0;
                            *flag3 = 1;
                            make_random_map(save_map.co , save_map.op);
                            return;
                        }
                        
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (Event.button.button == SDL_BUTTON_LEFT) 
                    {
                        SDL_GetMouseState(&x , &y);
                        if((x > 35) && (x < 185) && (y > 650) && (y <703))
                        {
                            return;
                        }
                       
                    }
                break;
                
            }
        
        }
        char temmp[20];
        sprintf(temmp,"%d" ,led.user[active_user_id].score );
        SDL_SetRenderDrawColor(renderer, 238, 237, 237, 255);
        SDL_RenderClear(renderer);
        image(renderer , "ff.png" , 0 , 0);
        image(renderer , "menu.png" , 425 , 100);
        image(renderer , "border.png" , 350 , 230);
        image(renderer , "border5.png" , 457 , 337);
        image(renderer , "picture2.png" , 35 , 35);
        neveshte(renderer , "Username :" , 215 , 60 , 19 , 239 ,214 ,10 ,255);
        neveshte(renderer , led.user[active_user_id].name , 315 , 60 , 23 , 255 ,255,255 ,255);
        neveshte(renderer , "Score :" , 196 , 111 , 19 , 239 ,214 ,10 ,255);
        neveshte(renderer , temmp , 244 , 111 , 20 , 255 ,255 ,255 ,255);
        image(renderer , "home.png" , 35 , 650);
        if(temp)
        {
            neveshte(renderer , "Enter number of Countries:" , 600 , 280 , 30 , 195 ,234 ,129 ,255);
            neveshte(renderer , numbere , 600 , 350 , 30 , 255 ,255,255 ,255);
            neveshte(renderer , "Your number must be between 6 and 15.", 600 , 410 ,18, 245 , 135 , 232 , 150);
        }
        else
        {
            neveshte(renderer , "Enter number of Opponents:" , 600 , 280 , 30 , 195 ,234 ,129 ,255);
            neveshte(renderer , numbere , 600 , 350 , 30 , 255 ,255,255 ,255);
            neveshte(renderer , "Your number must be between 1 and 4.", 600 , 410 ,18, 245 , 135 , 232 , 150);
        }
        
        neveshte(renderer , "Press the Enter key to continue", 600 , 445 ,18, 104 , 124 , 142 , 150);

      
        SDL_RenderPresent(renderer);
        SDL_Delay(FPS / 1000);
    }
}
void choise_rand_or_ready (SDL_Renderer *renderer , int* running , int* flag2 , int* flag3)
{
    int x=0 , y=0 ;
    SDL_Event Event ;
    int r1=255 , g1=255 ,b1=255 ;
    int r2=255 , g2=255 ,b2=255 ;
    while(*running)
    {
        while (SDL_PollEvent(&Event)) 
        {
            switch (Event.type) 
            {
                case SDL_QUIT:
                    *running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (Event.button.button == SDL_BUTTON_LEFT) 
                    {
                        SDL_GetMouseState(&x , &y);
                        if((x > 450) && (x < 730) && (y > 270) && (y <330))
                        {
                                r1 = 217 ;
                                g1 = 196;
                                b1 = 15;
                        }
                        else if((x > 450) && (x < 730) && (y > 335) && (y <398))
                        {
                                r2 = 217 ;
                                g2 = 196;
                                b2 = 15;
                        }
                        else if((x > 35) && (x < 185) && (y > 650) && (y <703))
                        {
                              return;
                        }
                       
                    }
                break;
                case SDL_MOUSEBUTTONUP:
                    if (Event.button.button == SDL_BUTTON_LEFT) 
                    {
                        SDL_GetMouseState(&x , &y);
                        if((x > 450) && (x < 730) && (y > 270) && (y <330))
                        { 
                            ready_map(renderer , &running , flag2 , flag3);
                            return;
                        }
                        else if((x > 450) && (x < 730) && (y > 335) && (y <398))
                        {
                            random_map(renderer , &running , flag2 , flag3);
                            return;
                        }
                        
                       
                    }
                break;
                default:
                        SDL_GetMouseState(&x , &y);
                        if((x > 450) && (x < 730) && (y > 270) && (y <330))
                        { 
                                r1 = 217 ;
                                g1 = 196;
                                b1 = 15;
                                r2=255 ; g2=255 ;b2=255 ;

                        }
                        else if((x > 450) && (x < 730) && (y > 335) && (y <398))
                        {
                                r2 = 217 ;
                                g2 = 196;
                                b2 = 15;
                                r1=255 ; g1=255 ;b1=255 ;

                        }
                        
                        else
                        {
                            r1=255 ; g1=255 ;b1=255 ;
                            r2=255 ; g2=255 ;b2=255 ;
                        }
                break;
              
            }
        
        }
        char temmp[20];
        sprintf(temmp,"%d" ,led.user[active_user_id].score );
        SDL_SetRenderDrawColor(renderer, 238, 237, 237, 255);
        SDL_RenderClear(renderer);
        image(renderer , "ff.png" , 0 , 0);
        image(renderer , "menu.png" , 425 , 100);
        image(renderer , "border3.png" , 450 , 270);
        image(renderer , "border5.png" , 457 , 337);
        image(renderer , "picture2.png" , 35 , 35);
        neveshte(renderer , "Username :" , 215 , 60 , 19 , 239 ,214 ,10 ,255);
        neveshte(renderer , led.user[active_user_id].name , 315 , 60 , 23 , 255 ,255 ,255 ,255);
        neveshte(renderer , "Score :" , 196 , 111 , 19 , 239 ,214 ,10 ,255);
        neveshte(renderer , temmp , 244 , 111 , 20 , 255 ,255 ,255 ,255);
        image(renderer , "home.png" , 35 , 650);
        neveshte(renderer , "Ready maps" , 600 , 280 , 30 , r1 ,g1 ,b1 ,255);
        neveshte(renderer , "Random map" , 600 , 350 , 30 , r2 ,g2,b2 ,255);
      
        SDL_RenderPresent(renderer);
        SDL_Delay(FPS / 1000);
    }
    
}
void main_menu(SDL_Renderer *renderer , int* running , int* flag2 , int* flag3 ,int* valid)
{
    int x=0 , y=0 ;
    SDL_Event Event ;
    int r1=255 , g1=255 ,b1=255 ;
    int r2=255 , g2=255 ,b2=255 ;
    int r3=255 , g3=255 ,b3=255 ;
    int r4=255 , g4=255 ,b4=255 ;
    while(*running)
    {
        while (SDL_PollEvent(&Event)) 
        {
            switch (Event.type) 
            {
                case SDL_QUIT:
                    *running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (Event.button.button == SDL_BUTTON_LEFT) 
                    {
                        SDL_GetMouseState(&x , &y);
                        if((x > 450) && (x < 730) && (y > 270) && (y <330))
                        {
                                r1 = 217 ;
                                g1 = 196;
                                b1 = 15;
                        }
                        else if((x > 450) && (x < 730) && (y > 335) && (y <398))
                        {
                                r2 = 217 ;
                                g2 = 196;
                                b2 = 15;
                        }
                        else if((x > 450) && (x < 730) && (y > 400) && (y <465))
                        {
                                r3 = 217 ;
                                g3 = 196;
                                b3 = 15;
                        }
                        else if((x > 450) && (x < 730) && (y > 465) && (y <528))
                        {
                                r4 = 217 ;
                                g4 = 196;
                                b4 = 15;
                        }
                        else if((x > 35) && (x < 185) && (y > 650) && (y <703))
                        {
                            *running = 0;
                            return;
                        }
                    }
                break;
                case SDL_MOUSEBUTTONUP:
                    if (Event.button.button == SDL_BUTTON_LEFT) 
                    {
                        SDL_GetMouseState(&x , &y);
                        if((x > 450) && (x < 730) && (y > 270) && (y <330))
                        { 
                            choise_rand_or_ready(renderer , running , flag2, flag3);
                            return;
                        }
                        else if((x > 450) && (x < 730) && (y > 335) && (y <398))
                        {
                            import_num_country();
                            import_num_attack();
                            import_save();
                            *flag2 = 0 ;
                            *flag3 = 1 ;
                            return;
                        }
                        else if((x > 450) && (x < 730) && (y > 400) && (y <465))
                        {
                            sort_score();
                            show_leaderboard(renderer , running);
                            export_num_user();
                            export_user_data();
                            return;
                        }
                        else if((x > 450) && (x < 730) && (y > 465) && (y <528))
                        {
                            *valid = 1;
                        }
                       
                    }
                break;
                case SDL_KEYDOWN:
                    if(Event.key.keysym.sym == SDLK_KP_ENTER  || Event.key.keysym.sym == SDLK_RETURN)
                        {
                            *valid = 0 ;
                        }
                break;
                default:
                        SDL_GetMouseState(&x , &y);
                        if((x > 450) && (x < 730) && (y > 270) && (y <330))
                        { 
                                r1 = 217 ;
                                g1 = 196;
                                b1 = 15;
                                r2=255 ; g2=255 ;b2=255 ;
                                r3=255 ; g3=255 ;b3=255 ;
                                r4=255 , g4=255 ,b4=255 ;
                        }
                        else if((x > 450) && (x < 730) && (y > 335) && (y <398))
                        {
                                r2 = 217 ;
                                g2 = 196;
                                b2 = 15;
                                r1=255 ; g1=255 ;b1=255 ;
                                r3=255 ; g3=255 ;b3=255 ;
                                r4=255 , g4=255 ,b4=255 ;
                        }
                        else if((x > 450) && (x < 730) && (y > 400) && (y <465))
                        {
                                r3 = 217 ;
                                g3 = 196;
                                b3 = 15;
                                r1=255 ; g1=255 ;b1=255 ;
                                r2=255 ; g2=255 ;b2=255 ;
                                r4=255 , g4=255 ,b4=255 ;
                        }
                        else if((x > 450) && (x < 730) && (y > 465) && (y <528))
                        {
                            r4 = 217 ;
                            g4 = 196;
                            b4 = 15;
                            r1=255 ; g1=255 ;b1=255 ;
                            r2=255 ; g2=255 ;b2=255 ;
                            r3=255 ; g3=255 ;b3=255 ;
                        }
                        else
                        {
                            r1=255 ; g1=255 ;b1=255 ;
                            r2=255 ; g2=255 ;b2=255 ;
                            r3=255 ; g3=255 ;b3=255 ;
                            r4=255 , g4=255 ,b4=255 ;
                        }
                break;

            }
        
        }
        char temmp[20];
        sprintf(temmp,"%d" ,led.user[active_user_id].score );
        SDL_SetRenderDrawColor(renderer, 238, 237, 237, 255);
        SDL_RenderClear(renderer);
        image(renderer , "ff.png" , 0 , 0);
        image(renderer , "picture2.png" , 35 , 35);
        image(renderer , "menu.png" , 425 , 100);
        image(renderer , "border3.png" , 450 , 270);
        image(renderer , "border5.png" , 457 , 337);
        image(renderer , "border5.png" , 457 , 404);
        image(renderer , "border5.png" , 457 , 471);
        image(renderer , "exit.png" , 35 , 643);
        neveshte(renderer , "Username :" , 215 , 60 , 19 , 239 ,214 ,10 ,255);
        neveshte(renderer , led.user[active_user_id].name , 315 , 60 , 23 , 255 ,255 ,255 ,255);
        neveshte(renderer , "Score :" , 196 , 111 , 19 , 239 ,214 ,10 ,255);
        neveshte(renderer , temmp , 244 , 111 , 20 , 255 ,255 ,255 ,255);
        neveshte(renderer , "New game" , 600 , 280 , 30 , r1 ,g1 ,b1 ,255);
        neveshte(renderer , "Continues" , 600 , 350 , 30 , r2 ,g2,b2 ,255);
        neveshte(renderer , "Leaderboard" , 600 , 417 , 30 , r3 ,g3 ,b3 ,255);
        neveshte(renderer , "About Potions" , 600 , 485 , 30 , r4 ,g4 ,b4 ,255);
        if(*valid)
        {
            image(renderer , "ff.png" , 0 , 0);
            image(renderer , "war.png" , 0 , 0);
        }
      
        SDL_RenderPresent(renderer);
        SDL_Delay(FPS / 1000);
    }
    

}
