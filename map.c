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
#define base_soldiers 20

int num_of_country=0;

int x_barracks(int x , int w )
{
    return (x+(w/2)) ;
}
int y_barracks( int y , int h)
{
    return (y+(h/2)) ;
}

void x_y_rand_map(int xy[50][3] )
{
    int t = 0;
    int o = 0;
    int b = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            xy[o][0]=t;
            xy[o][1]=b;
            xy[o][2]=0;
            b+=125;
            o++;
        }
        t+=160;
        b=0;
      
    }
    
}

void num_of_soldiers(SDL_Renderer *renderer ,int i, int x , int y)
{
    char num[50];
    TTF_Font* font = TTF_OpenFont("fonts/new.ttf", 20);
    SDL_Color White = {255, 255, 255};
    sprintf(num, "%d", save.country[i].number_of_soldiers);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, num , White); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    int texW=0 , texH=0 ;
    SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);

    SDL_Rect Message_rect; 
    Message_rect.x = x;  
    Message_rect.y = y; 
    Message_rect.w = texW; 
    Message_rect.h = texH; 

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    TTF_CloseFont(font);
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage);
    


}
void make_ready_map(int num_ready_map)
{
    int num_o = 0 ;
    int num_c = 0;
    if(num_ready_map == 1)
    {
        srand(5);
        num_o = 2;
        num_c = 5;
    }
    else if(num_ready_map == 2)
    {
        srand(20);
        num_o = 3;
        num_c = 7;
    }
    else if(num_ready_map == 3)
    {
        srand(10);
        num_o = 3;
        num_c = 8;
    }
    else if(num_ready_map == 4)
    {
        srand(55);
        num_o = 4;
        num_c = 8;
    }
    else if(num_ready_map == 5)
    {
        srand(77); 
        num_o = 5;
        num_c = 10;
    }
    else if(num_ready_map == 6)
    {
        import_no_map();
        srand(save_map.ra_time);
        num_o = save_map.op ;
        num_c = save_map.co;
    }
    else if(num_ready_map == 7)
    {
        num_of_attack = 0;
        num_of_country = 11;
        import_memory();
        return;
    }
   
    
    int xy_rand_map[50][3];
    
    x_y_rand_map(xy_rand_map);
    int rand =0  , i_rand = 0 , y_rand = 0 ;
    char name_of_shape[25][25] = {{"1"} , {"2"} , {"3"} , {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}};
    char temp[25] ;
    char zero[25] = "0.png";
    char color_of_shape[25][25] = {{"1.png"} , {"2.png"} , {"3.png"} , {"4.png"} , {"5.png"} };
    for (int i = 0; i < num_o; i++)
    {
        
        i_rand = printRandoms(0,27);
        while (xy_rand_map[i_rand][2]!=0)
        {
            i_rand = printRandoms(0,27);
        }
        xy_rand_map[i_rand][2]=1;
        strcpy(temp , name_of_shape[i]);
        strcpy(save.country[num_of_country].shape , temp);
        strcat( temp , color_of_shape[i] );
        strcpy(save.country[num_of_country].color , color_of_shape[i]);
        strcpy(save.country[num_of_country].path , temp);
        save.country[num_of_country].x = xy_rand_map[i_rand][0] + printRandoms(-20,20) ;
        save.country[num_of_country].y = xy_rand_map[i_rand][1] + printRandoms(-20,20);
        if(i==0)
        {
            save.country[num_of_country].user = true;
        }
        else
        {
            save.country[num_of_country].user = false;
        }
        save.country[num_of_country].sides = true;
        save.country[num_of_country].number_of_soldiers = base_soldiers ;
        save.country[num_of_country].number_of_soldiers_copy = base_soldiers ;
        save.country[num_of_country].personality = i ;
        num_of_country++;
    }
    
    for (int i = 0; i < num_c-num_o; i++)
    {
        rand = printRandoms(0 , 8);
        i_rand = printRandoms(0,27);
        while (xy_rand_map[i_rand][2]!=0)
        {
            i_rand = printRandoms(0,27);
        }
        xy_rand_map[i_rand][2]=1;
        strcpy(temp , name_of_shape[rand]);
        strcpy(save.country[num_of_country].shape , temp);
        strcat( temp , zero );
        strcpy(save.country[num_of_country].color , zero);
        strcpy(save.country[num_of_country].path , temp );
        save.country[num_of_country].x = xy_rand_map[i_rand][0] + printRandoms(-20,20) ;
        save.country[num_of_country].y = xy_rand_map[i_rand][1] + printRandoms(-20,20) ;
        save.country[num_of_country].user = false;
        save.country[num_of_country].sides = false;
        save.country[num_of_country].number_of_soldiers = base_soldiers ;
        save.country[num_of_country].number_of_soldiers_copy = base_soldiers ;
        save.country[num_of_country].personality = 5 ;
        num_of_country++;

    }
}
void make_random_map(int num_c , int num_o)
{
    
    save_map.ra_time = time(0) ; 
    srand(save_map.ra_time);
    
    int xy_rand_map[50][3];
    
    x_y_rand_map(xy_rand_map);
    int rand =0  , i_rand = 0 , y_rand = 0 ;
    char name_of_shape[25][25] = {{"1"} , {"2"} , {"3"} , {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}};
    char temp[25] ;
    char zero[25] = "0.png";
    char color_of_shape[25][25] = {{"1.png"} , {"2.png"} , {"3.png"} , {"4.png"} , {"5.png"} };
    for (int i = 0; i < num_o; i++)
    {
        
        i_rand = printRandoms(0,27);
        while (xy_rand_map[i_rand][2]!=0)
        {
            i_rand = printRandoms(0,27);
        }
        xy_rand_map[i_rand][2]=1;
        strcpy(temp , name_of_shape[i]);
        strcpy(save.country[num_of_country].shape , temp);
        strcat( temp , color_of_shape[i] );
        strcpy(save.country[num_of_country].color , color_of_shape[i]);
        strcpy(save.country[num_of_country].path , temp);
        save.country[num_of_country].x = xy_rand_map[i_rand][0] + printRandoms(-20,20) ;
        save.country[num_of_country].y = xy_rand_map[i_rand][1] + printRandoms(-20,20);
        if(i==0)
        {
            save.country[num_of_country].user = true;
        }
        else
        {
            save.country[num_of_country].user = false;
        }
        save.country[num_of_country].sides = true;
        save.country[num_of_country].number_of_soldiers = base_soldiers ;
        save.country[num_of_country].number_of_soldiers_copy = base_soldiers ;
        save.country[num_of_country].personality = i ;
        num_of_country++;
    }
    
    for (int i = 0; i < num_c-num_o; i++)
    {
        rand = printRandoms(0 , 8);
        i_rand = printRandoms(0,27);
        while (xy_rand_map[i_rand][2]!=0)
        {
            i_rand = printRandoms(0,27);
        }
        xy_rand_map[i_rand][2]=1;
        strcpy(temp , name_of_shape[rand]);
        strcpy(save.country[num_of_country].shape , temp);
        strcat( temp , zero );
        strcpy(save.country[num_of_country].color , zero);
        strcpy(save.country[num_of_country].path , temp );
        save.country[num_of_country].x = xy_rand_map[i_rand][0] + printRandoms(-20,20) ;
        save.country[num_of_country].y = xy_rand_map[i_rand][1] + printRandoms(-20,20) ;
        save.country[num_of_country].user = false;
        save.country[num_of_country].sides = false;
        save.country[num_of_country].number_of_soldiers = base_soldiers ;
        save.country[num_of_country].number_of_soldiers_copy = base_soldiers ;
        save.country[num_of_country].personality = 5 ;
        num_of_country++;

    }
      
}

void map(SDL_Renderer *renderer)
{
    for(int i = 0 ; i < num_of_country ; i++)
    {
        
        char path[50] = "maps\\" ;
        strcat(path, save.country[i].path);
        SDL_Texture * image_texture = initialize_texture_from_file( path , renderer);
        int image_width, image_height;

        SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);

        SDL_Rect texture_destination;

        texture_destination.x = save.country[i].x ;
        texture_destination.y = save.country[i].y ;
        texture_destination.w = image_width;
        texture_destination.h = image_height;
        save.country[i].x_of_barracks = x_barracks(save.country[i].x , image_width) ;
        save.country[i].y_of_barracks = y_barracks(save.country[i].y ,image_height);
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        ellipse(renderer , save.country[i].x_of_barracks , save.country[i].y_of_barracks , 25 , 25 , 100 , 50 , 40 , 1);
        num_of_soldiers(renderer ,i,(save.country[i].x_of_barracks)-10 , (save.country[i].y_of_barracks-10));
        SDL_DestroyTexture(image_texture);
        IMG_Quit();
    
    }
}
void change_number_of_soldiers(int num_attack , int num_soldier , int val)
{
    int amade = save.attack[num_attack].soldiers[num_soldier].source ;
    int mire = save.attack[num_attack].soldiers[num_soldier].dest ;
    char color_of_shape[25][25] = {{"1.png"} , {"2.png"} , {"3.png"} , {"4.png"} , {"5.png"} };
    
    if(val == 1)
    {
        if((save.attack[num_attack].soldiers[num_soldier].personality == save.country[mire].personality))
        {
            
            save.country[mire].number_of_soldiers++;
            save.country[mire].number_of_soldiers_copy++; 


        }
        else
        {
            if(save.country[mire].number_of_soldiers > 0)
            {
                save.country[mire].number_of_soldiers--;
                save.country[mire].number_of_soldiers_copy--;


            }
            else
            {
                char temp[50] ;
                strcpy(temp , save.country[mire].shape);
                strcat(temp , color_of_shape[save.attack[num_attack].soldiers[amade].personality] );
                strcpy(save.country[mire].path , temp);
                save.country[mire].sides = true ;
                save.country[mire].personality = save.attack[num_attack].soldiers[amade].personality ;
                if(save.country[mire].personality == 0)
                {
                    save.country[mire].user = true ;
                    
                }
                else
                {
                    save.country[mire].user = false ;
                }
                save.country[mire].number_of_soldiers++;
                save.country[mire].number_of_soldiers_copy++;
            }
        }
    }
    else
    {
        if (save.country[amade].number_of_soldiers > 0)
        {
            save.country[amade].number_of_soldiers-- ;
        }

    }
    
    
}