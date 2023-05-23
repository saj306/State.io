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


#define speed 1.2
#define FPS 60
#define max_side_true 50
double delay = 30 ;
int num_of_attack=0;
int fin_sourse =-1 ;
int fin_dest =-1 ;
int dal = 1;
void choose_color(int kind , int* r , int* g , int* b)
{
    switch (kind)
    {
    case 0:
        *r = 19 ; *g = 157; *b = 204;
        break;
    case 1:
        *r = 156 ; *g = 95; *b = 156;
        break;
    case 2:
        *r = 107 ; *g = 139; *b = 90;
        break;
    case 3:
        *r = 188 ; *g = 178; *b = 113;
        break;
    case 4:
        *r = 157 ; *g = 25; *b = 66;
        break;
    
    default:
        break;
    }
}
void move_soldiers(SDL_Renderer *renderer )
{
    for (int i = 0; i < num_of_attack; i++)
    {
            
        if(save.attack[i].active == true)
        {
            float speed_potion = 1.0 ;
            double x_source = save.attack[i].x_source ;
            double y_source = save.attack[i].y_source ;
            double x_dest = save.attack[i].x_dest ;
            double y_dest = save.attack[i].y_dest ;
            double spase = sqrt(((x_dest - x_source)*(x_dest - x_source))+ ((y_dest - y_source)*(y_dest - y_source)));
            double dx = ((x_dest - x_source)/spase) * speed ;
            double dy = ((y_dest - y_source)/spase) * speed ;
            int j = 0 ;
            while (j < save.attack[i].number_of_soldiers)
            {
                if(save.attack[i].soldiers[j].delay <= 0 && save.attack[i].soldiers[j].deleted == false)
                {
                    int colo[3] = {0} ;
                    choose_color(save.attack[i].soldiers[j].personality , colo , colo+1 , colo+2);
                    ellipse(renderer , save.attack[i].soldiers[j].x_source  , save.attack[i].soldiers[j].y_source , 5 , 5 , colo[0] , colo[1] , colo[2] ,1);
                    
                    if(abs(save.attack[i].soldiers[j].x_source - save.attack[i].soldiers[j].x_dest)<=10 && abs(save.attack[i].soldiers[j].y_source - save.attack[i].soldiers[j].y_dest)<=10)
                    {
                        save.attack[i].soldiers[j].deleted = true ;
                        change_number_of_soldiers(i , j , 1);
                        if(j==save.attack[i].number_of_soldiers-1)
                        {
                            save.attack[i].active = false ;
                        }
                    }
                    else
                    {
                        if((abs(save.attack[i].soldiers[j].x_source - save.attack[i].x_source) == 0) && (abs(save.attack[i].soldiers[j].y_source - save.attack[i].y_source) == 0))
                         {
                            change_number_of_soldiers(i , j , 0);
                         }
                         for (int d = 0; d < num_of_attack; d++)
                         {
                             if(save.attack[d].active == true)
                             {
                                for (int r = 0; r < save.attack[d].number_of_soldiers ; r++)
                                {
                                    if((abs(save.attack[i].soldiers[j].x_source - save.attack[d].soldiers[r].x_source) <= 4) && (abs(save.attack[i].soldiers[j].y_source - save.attack[d].soldiers[r].y_source) <= 4) && (save.attack[i].soldiers[j].personality != save.attack[d].soldiers[r].personality) && save.attack[i].soldiers[j].deleted == false &&  save.attack[d].soldiers[r].deleted == false)
                                        {
                                            save.attack[i].soldiers[j].deleted = true ;
                                            save.attack[d].soldiers[r].deleted = true ;
                                        }
                                }
                             }
                             
                         }
                         for (int a = 0; a < num_of_potion; a++)
                         {
                             int con = 1;
                             if((abs((save.potion[a].x + 7 ) - save.attack[i].soldiers[j].x_source) <= 25) && (abs((save.potion[a].y + 20 ) - save.attack[i].soldiers[j].y_source) <= 25))
                             {
                                 
                                for (int g = 0; g < num_of_potion; g++)
                                    {
                                        if(save.potion[g].personality == save.attack[i].soldiers[j].personality)
                                        {
                                            con = 0;
                                        }
                                        
                                    }
                                if(save.potion[a].show == true && save.potion[a].active == false && con)
                                 {
                                    
                                    save.potion[a].personality = save.attack[i].soldiers[j].personality ;
                                    save.potion[a].active = true;
                                    

                                 }
                             }
                         }
                         for (int c = 0; c < num_of_potion; c++)
                         {
                            if((save.attack[i].soldiers[j].personality == save.potion[c].personality) && (save.potion[c].active) && (!strcmp(save.potion[c].kind , "1") ))
                            {
                                speed_potion = 4;
                                save.attack[i].soldiers[j].x_source+=(dx * speed_potion);
                                save.attack[i].soldiers[j].y_source+=(dy * speed_potion);

                            }
                            if((save.attack[i].soldiers[j].personality == save.potion[c].personality) && (save.potion[c].active) &&  (!strcmp(save.potion[c].kind , "3")) )
                            {
                                speed_potion = 0.0001;
                                save.attack[i].soldiers[j].x_source+=(dx * speed_potion);
                                save.attack[i].soldiers[j].y_source+=(dy * speed_potion);

                            }
                            else
                            {
                                speed_potion = 1;
                                save.attack[i].soldiers[j].x_source+=(dx * speed_potion);
                                save.attack[i].soldiers[j].y_source+=(dy * speed_potion);
                            }
                         }
                         
                        
                        
                        
                    }

                }
                
                save.attack[i].soldiers[j].delay--;
                j++;
            }

        }
    }
    
    
    
}
void Sending_soldiers(SDL_Renderer *renderer ,int source, int dest )
{
    int x_source = 0 , y_source = 0 ;
    int x_dest = 0 , y_dest = 0 ;
    
    x_source = save.country[source].x_of_barracks ;
    y_source = save.country[source].y_of_barracks ;
    x_dest = save.country[dest].x_of_barracks;
    y_dest = save.country[dest].y_of_barracks;
    
    save.attack[num_of_attack].number_of_soldiers = save.country[source].number_of_soldiers_copy ;
    save.country[source].number_of_soldiers_copy = 0 ;
    save.attack[num_of_attack].id = num_of_attack ;
    save.attack[num_of_attack].active = true ;
    save.attack[num_of_attack].x_source = x_source ;
    save.attack[num_of_attack].y_source = y_source ;
    save.attack[num_of_attack].x_dest = x_dest ;
    save.attack[num_of_attack].y_dest = y_dest ;
    for (int i = 0; i < save.attack[num_of_attack].number_of_soldiers ; i++)
    {
        save.attack[num_of_attack].soldiers[i].id = i ;
        save.attack[num_of_attack].soldiers[i].deleted = false ;
        save.attack[num_of_attack].soldiers[i].x_source = x_source ;
        save.attack[num_of_attack].soldiers[i].y_source = y_source ;
        save.attack[num_of_attack].soldiers[i].x_dest = x_dest ;
        save.attack[num_of_attack].soldiers[i].y_dest = y_dest ;
        save.attack[num_of_attack].soldiers[i].source = source ;
        save.attack[num_of_attack].soldiers[i].personality = save.country[source].personality ;
        save.attack[num_of_attack].soldiers[i].dest = dest ;
        save.attack[num_of_attack].soldiers[i].delay = i*6 ;
    }
    
    num_of_attack++;
    
    
}
void growth_of_soldiers()
{
    
    if(delay == 0)
    {
        for (int i = 0; i < num_of_country; i++)
        {
            
            if(save.country[i].sides == true && save.country[i].number_of_soldiers < max_side_true)
            {
                save.country[i].number_of_soldiers++;
                save.country[i].number_of_soldiers_copy++;
            }
        }
        delay = 30 ;
        
    }
    else
    {
        delay-- ;
    }
    
    
}
void artificial_intelligence(SDL_Renderer *renderer , int* flag)
{
    if(*flag)
    {
        for (int i = 0; i < num_of_country; i++)
        {
            if(save.country[i].personality != 0 && save.country[i].personality != 5)
            {
                int rand = 0;
                
                rand = printRandoms(0 , 9999999);
                rand %= 600;
                if ((rand >= 0) && (rand <= (num_of_country-1)))
                {
                    if(rand != i && (save.country[i].number_of_soldiers_copy - save.country[rand].number_of_soldiers_copy >= 14) && save.country[i].personality != save.country[rand].personality && save.country[rand].personality != 5)
                    {
                        Sending_soldiers(renderer , i , rand);
                    }
                    else if (rand != i && (save.country[i].number_of_soldiers_copy - save.country[rand].number_of_soldiers_copy >= 20) && save.country[i].personality != save.country[rand].personality && save.country[rand].personality == 5)
                    {
                        Sending_soldiers(renderer , i , rand);
                    }
                    
                }
                

            }
        }
        for (int g = 0; g < num_of_attack; g++)
        {
            int qn= 0 ;
            if(save.attack[g].active == true && save.attack[g].soldiers[0].dest != 0 )
            {
                while (qn < num_of_country)
                {
                    if((save.attack[g].soldiers[0].personality != save.country[qn].personality) && (save.country[save.attack[g].soldiers[0].dest].personality == save.country[qn].personality) &&(save.country[qn].number_of_soldiers_copy >= 15) && (save.country[qn].number_of_soldiers_copy - save.attack[g].number_of_soldiers <= 20) && (save.attack[g].number_of_soldiers - save.country[save.attack[g].soldiers[0].dest].number_of_soldiers_copy >= 7) && save.country[qn].personality != 0 && save.country[qn].personality != 5 ) 
                    {
                        for (int l = 0; l < num_of_attack; l++)
                        {
                            if(save.attack[l].soldiers[0].source == qn && save.attack[l].soldiers[0].dest == save.attack[g].soldiers[0].dest)
                            {
                                return;
                            }
                        }
                        
                        if( qn > 0 && save.attack[g].soldiers[0].dest > 0 && (qn != save.attack[g].soldiers[0].dest))
                        {
                            Sending_soldiers(renderer , qn , save.attack[g].soldiers[0].dest );
                            qn++ ;
                        return;
                        }
                        else
                        {
                            qn++ ;
                        }
                    }
                    else
                    {
                        qn++ ;
                    }
                }
                
            }
        }
        



















    }
    
}

void event_handler (int* running ,SDL_Renderer *renderer )
{
    int x = 0 , y = 0 ;
    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
        switch (Event.type) {
            case SDL_QUIT:
                export_num_country();
                export_num_attack();
                export_save();
                *running = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (Event.button.button == SDL_BUTTON_LEFT) {
                   
                   SDL_GetMouseState(&x , &y);
                   for (int i = 0; i < num_of_country; i++)
                   {
                       if(save.country[i].x_of_barracks >= x-25 && save.country[i].x_of_barracks <= x+25 && save.country[i].y_of_barracks >= y-25 && save.country[i].y_of_barracks <= y+25)
                        {
                            fin_sourse = i ;
                        }
                   }

                   
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (Event.button.button == SDL_BUTTON_LEFT) {
                    
                    SDL_GetMouseState(&x , &y);
                    for (int i = 0; i < num_of_country; i++)
                   {
                       if(save.country[i].x_of_barracks >= x-25 && save.country[i].x_of_barracks <= x+25 && save.country[i].y_of_barracks >= y-25 && save.country[i].y_of_barracks <= y+25)
                        {
                            fin_dest = i;
                        }
                   }
                    
                }
                break;
        }
        
    }
    if (fin_dest >= 0 && fin_sourse >= 0 && fin_sourse != fin_dest)
    {
        if(save.country[fin_sourse].user == true)
        {
            Sending_soldiers(renderer,fin_sourse , fin_dest );
           
        
        }
        fin_dest = -1;
        fin_sourse = -1;
    }
    else if (fin_sourse == fin_dest)
    {
        fin_dest = -1;
        fin_sourse = -1;
    }
    return;
}