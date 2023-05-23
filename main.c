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


int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("State.io", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();

    int running = 1;
    SDL_Event event ;

    initialize_potions();
    int flag1 = 1 , flag2 = 0 , flag3 = 0 , inte_flag = 1 , valid = 0 , valid1 = 0;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = 0;
            }
            
        }
        
        SDL_SetRenderDrawColor(renderer, 11, 34, 57, 255);
        SDL_RenderClear(renderer);


        if(flag1)
        {
            input_username(renderer , &running , &flag1 , &flag2);

        }
        if(flag2)
        {
            main_menu(renderer , &running , &flag2 , &flag3 , &valid1);

        }
        if(flag3)
        {
            
            map(renderer);
            growth_of_soldiers();
            barracks_action();
            choose_potion();
            current_potion(renderer);
            stay_potion();
            potions(renderer);
            move_soldiers(renderer);
            win_or_lose(renderer ,&running ,&flag2, &flag3 , &inte_flag  ,&valid);
            event_handler(&running , renderer);
            artificial_intelligence(renderer , &inte_flag);
            
            
        }
        
        
        SDL_RenderPresent(renderer);
        SDL_Delay(FPS / 1000);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

