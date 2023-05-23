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
#define max_username_len 50

int num_of_user =0;
int active_user_id = -1 ;

void check_user(char username[])
{
    
    int val = 1 ;
    for (int g = 0; g <= num_of_user; g++)
    {
       
        if(!strcmp(led.user[g].name , username))
        {
            active_user_id = g;
            val = 0;
            
            return;
        }
    }
    if(val)
    {
        
        strcpy(led.user[num_of_user].name , username);
        led.user[num_of_user].score = 0;
        active_user_id = num_of_user;
        num_of_user++;
        
        return;
    }
    
}
void image(SDL_Renderer *renderer , char name[], int x ,int y)
{
    char temp[20] = "images\\" ; 
    strcat(temp, name);
    SDL_Texture * image_texture = initialize_texture_from_file( temp , renderer);
    int image_width, image_height;

    SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);

    SDL_Rect texture_destination;

    texture_destination.x = x ;
    texture_destination.y = y ;
    texture_destination.w = image_width;
    texture_destination.h = image_height;

    SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
}
void neveshte(SDL_Renderer *renderer , char username[] , int x , int y ,int size, int r , int g , int b , int a)
{
    TTF_Font* font = TTF_OpenFont("fonts/BalsamiqSans-Bold.ttf", size);
    SDL_Color color = {r, g, b , a};
    
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, username , color); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    int texW=0 , texH=0 ;
    SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);

    SDL_Rect Message_rect; 
    Message_rect.x = x - (texW / 2);  
    Message_rect.y = y; 
    Message_rect.w = texW; 
    Message_rect.h = texH; 

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    TTF_CloseFont(font);
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage);
}
void input_username(SDL_Renderer *renderer , int* running , int* flag1 , int* flag2)
{
    
    SDL_Event event ;

    import_num_user();
    import_user_data();
    if (num_of_user >  50)
    {
        num_of_user = 0;
    }
    char username[50] = {'\0'};
    while(*running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                *running = 0;
            }
            if(event.type == SDL_TEXTINPUT)
            {
                if(strlen(username) +1 < max_username_len)
                {
                    strcat(username,event.text.text);
                }
            }
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if(strlen(username) > 0)
                    {
                        username[strlen(username) -1 ] = '\0' ;
                    }
                }
                else if(event.key.keysym.sym == SDLK_KP_ENTER  || event.key.keysym.sym == SDLK_RETURN)
                {
                
                    check_user(username);
                    *flag1 = 0;
                    *flag2 = 1;
                    return;
                }
            }
            
            
        }
        
        SDL_SetRenderDrawColor(renderer, 238, 237, 237, 255);
        SDL_RenderClear(renderer);
        image(renderer , "back.jpg" , 0 , 0);
        image(renderer , "border1.png" , 419 , 260);
        image(renderer , "border.png" , 350 , 170);
        image(renderer , "user.png" , 515 , 20);
        neveshte(renderer , "Enter your name :", 600 , 220 ,30, 195 , 234 , 129 , 255);
        neveshte(renderer , username, 600 , 290 ,40, 255 , 255 , 255 , 255);
        
        neveshte(renderer , "Press the Enter key to continue", 600 , 370 ,18, 104 , 124 , 142 , 150);
        neveshte(renderer , "Created by Seyed Ali Jafari", 600 , 450 ,18, 129 , 234 , 223 , 255);
        SDL_RenderPresent(renderer);
        SDL_Delay(FPS / 1000);
    }
    

}

