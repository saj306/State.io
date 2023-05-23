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
#include "username.h"
#include "menu.h"
#include "leaderboard.h"
#define new_max(x,y) (((x) >= (y)) ? (x) : (y))
#define new_min(x,y) (((x) <= (y)) ? (x) : (y))

#define max_side_true 50

#define FPS 60
#define time_potion 300
#define time_potion_stay 600

int num_of_potion =3;
int delay_for_potion = 10 ;


void initialize_potions()
{
	int rand_delay = 0 ;
	for (int i = 0; i < num_of_potion; i++)
	{
		rand_delay = printRandoms(100 , 300);
		
		save.potion[i].show = false;
		save.potion[i].active = false;
		save.potion[i].personality = 5 ;
		save.potion[i].time = time_potion;
		save.potion[i].delay = rand_delay ;
		save.potion[i].stay = time_potion_stay;
		save.potion[i].blink = true;
	}
	
}

void barracks_action()
{
	if(delay_for_potion == 0)
	{
		for (int s = 0; s < num_of_potion; s++)
		{
			if((!strcmp(save.potion[s].kind , "2")) && save.potion[s].active)
			{
				for (int f = 0; f < num_of_country; f++)
				{
					if((save.potion[s].personality == save.country[f].personality) && save.country[f].number_of_soldiers < max_side_true)
					{
						save.country[f].number_of_soldiers++ ;
						save.country[f].number_of_soldiers_copy++ ;
					}
				}
				
			}
			else if((!strcmp(save.potion[s].kind , "4")) && save.potion[s].active)
			{
				for (int h = 0; h < num_of_country; h++)
				{
					if((save.potion[s].personality == save.country[h].personality) )
					{
						save.country[h].number_of_soldiers++ ;
						save.country[h].number_of_soldiers_copy++ ;
					}
				}
				
			}
				
		}
		delay_for_potion = 10;
	}
	else
	{
		delay_for_potion--;
	}
		
	
}
void potion_actions(float* s)
{
	for (int i = 0; i < num_of_potion; i++)
	{
	
		if(save.potion[i].active == true && save.potion[i].time != 0)
		{
			
			if(!strcmp(save.potion[i].kind , "1"))
			{
				
				*s=4;
				
				return;
			}
			else if(!strcmp(save.potion[i].kind , "3"))
			{
				*s=0.001;
				return;
			}
			
		}
			
	}
	
}

int val = 20;
void blink_zan(int a)
{
	if(val == 0)
	{
		val = 20 ;
	}
	if(val <= 10)
	{
		save.potion[a].blink = false;
	}
	else
	{
		save.potion[a].blink = true;
	}
	val--;
}
void current_potion(SDL_Renderer *renderer)
{
	for (int i = 0; i < num_of_potion; i++)
	{
		if(save.potion[i].active == true)
		{
			if(save.potion[i].time == 0)
			{
				save.potion[i].active = false;
				save.potion[i].show = false;
				save.potion[i].personality = 5;
			}
			else
			{
				SDL_Texture * image_texture ;
				if(save.potion[i].personality == 0)
				{
					image_texture = initialize_texture_from_file( "images/pic1.png" , renderer);
				}
				else if(save.potion[i].personality == 1)
				{
					image_texture = initialize_texture_from_file( "images/pic2.png" , renderer);
				}
				else if(save.potion[i].personality == 2)
				{
					image_texture = initialize_texture_from_file( "images/pic3.png" , renderer);
				}
				else if(save.potion[i].personality == 3)
				{
					image_texture = initialize_texture_from_file( "images/pic4.png" , renderer);
				}
				else if(save.potion[i].personality == 4)
				{
					image_texture = initialize_texture_from_file( "images/pic5.png" , renderer);
				}
				int image_width, image_height;

				SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);

				SDL_Rect texture_destination;
				if(!strcmp(save.potion[i].kind , "2"))
				{
					texture_destination.x =   save.potion[i].x - 73 ;
					texture_destination.y =   save.potion[i].y - 52;
				}
				else
				{
					texture_destination.x =   save.potion[i].x - 60 ;
					texture_destination.y =   save.potion[i].y - 52;
				}
				
				texture_destination.w = image_width;
				texture_destination.h = image_height;
				SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
				SDL_DestroyTexture(image_texture);
				IMG_Quit();

				save.potion[i].time--;
			}
		}

	}
	
}
void stay_potion()
{
	for (int i = 0; i < num_of_potion ; i++)
	{
		if(save.potion[i].stay == 0 && save.potion[i].active == false && save.potion[i].personality == 5)
		{
			save.potion[i].show = false ;
		}
		else
		{
			save.potion[i].stay--;
		}
	}
	
}
void choose_x_y_potion(double* x_rand , double* y_rand)
{
    int rand1 , rand2 ; 
	double ch1_x , ch2_x , ch1_y , ch2_y ;
    rand1 = printRandoms(0 , num_of_country-1);
    rand2 = printRandoms(0 , num_of_country-1);
    while(rand1 == rand2)
    {
        rand2 = printRandoms(0 , num_of_country-1);
    }
	ch1_x = save.country[rand1].x_of_barracks;
	ch2_x = save.country[rand2].x_of_barracks;
	ch1_y = save.country[rand1].y_of_barracks;
	ch2_y = save.country[rand2].y_of_barracks;
	*x_rand = printRandoms((new_min(ch1_x , ch2_x) +5) , (new_max(ch1_x , ch2_x)-5) );
	if((ch2_x - ch1_x) == 0)
	{
		ch2_x++;
	}
	*y_rand = ((((ch2_y - ch1_y)/(ch2_x - ch1_x)) * (*x_rand - ch1_x)) + ch1_y) ;
	*x_rand = *x_rand-5;
	*y_rand = *y_rand-10;


}
void choose_potion()
{
	int rand=0 ;
	int rand2=0;
	double x=0 , y=0 ;
	char name_of_potion[25][25] = {{"1"} , {"2"} , {"3"} , {"4"}};
	char sufix[15] = ".png";
	for (int i = 0; i < num_of_potion; i++)
	{
		
		if(save.potion[i].show == false && save.potion[i].delay == 0)
		{
			char temp[20];
			rand = printRandoms(0,3);
			rand2 = printRandoms(100,300);
			strcpy(temp , name_of_potion[rand]);
			strcpy(save.potion[i].kind , temp);
			strcat(temp , sufix);
			strcpy(save.potion[i].path , temp);
			choose_x_y_potion(&x , &y);
			save.potion[i].x = x ;
			save.potion[i].y = y ;
			save.potion[i].show = true;
			save.potion[i].active = false;
			save.potion[i].personality = 5 ;
			save.potion[i].time = time_potion ;
			save.potion[i].stay = time_potion_stay;
			save.potion[i].delay= rand2;
		}
		else if(save.potion[i].show == false && save.potion[i].delay != 0)
		{
			save.potion[i].delay--;
		}
		
	}
	
}
void potions(SDL_Renderer *renderer)
{
	for(int i=0  ; i < num_of_potion ; i++)
	{
		if(save.potion[i].show)
		{	
			char path[50] = "potions\\" ;
			strcat(path, save.potion[i].path);
			SDL_Texture * image_texture = initialize_texture_from_file( path , renderer);
			int image_width, image_height;

			SDL_QueryTexture(image_texture, NULL, NULL, &image_width, &image_height);

			SDL_Rect texture_destination;

			texture_destination.x =   save.potion[i].x  ;
			texture_destination.y =   save.potion[i].y ;
			texture_destination.w = image_width;
			texture_destination.h = image_height;
			SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
			SDL_DestroyTexture(image_texture);
			IMG_Quit();
		}
	}
}
