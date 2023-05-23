#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>

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

int con = 1;
SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) 
{
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}

int printRandoms(int lower, int upper)
{

    int num = (rand() %
	(upper - lower + 1)) + lower;
	return num ;

}
void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian)
{

    if(fill_boolian==1)
        filledEllipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);

    if(fill_boolian==0)

        ellipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);


}
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian )
{

    SDL_Rect rectangle ;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
    if (fill_boolian==1)

        SDL_RenderFillRect(Renderer, &rectangle);

    SDL_RenderDrawRect(Renderer, &rectangle);

}

void win_or_lose(SDL_Renderer *renderer,int* running , int* flag2 , int* flag3 , int* int_flag , int* num)
{
    int jadid = 1 ;
    int sum_user = 0 ;
    int sum_unknown = 0 ;
    int sum_another = 0 ;
     for (int i = 0; i < num_of_attack; i++)
    {
        if(save.attack[i].active == true) 
        {
            jadid = 0;
            
        }
        else
        {
            jadid = 1;
        }
              
    }
    if(jadid)
    {
        for (int i = 0; i < num_of_country; i++)
        {
            if((save.country[i].personality == 0))
            {
                sum_user++;
            }
            else if((save.country[i].personality == 5))
            {
                sum_unknown++;
            }
            else
            {
                sum_another++;
            }
        }
        if((sum_user > 0) && (sum_another == 0))
        {
            image( renderer, "dds.png" , 0 , 0);
            image( renderer, "again.png" , 495 , 640);
            SDL_Event event;
            int x= 0 , y= 0;
            while (SDL_PollEvent(&event))
            {
                
                if(event.type == SDL_QUIT)
                {
                    *flag3 = 0;
                    *running = 0;
                }
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (event.button.button == SDL_BUTTON_LEFT) 
                    {
                        SDL_GetMouseState(&x , &y);
                        if((x > 30) && (x < 110) && (y > 650) && (y <730))
                        {
                            export_no_map();
                            *num = 1 ;
                        }
                        else if((x > 495) && (x < 705) && (y > 640) && (y <715))
                        {
                            *flag3 = 0;
                            *flag2 = 1;
                            num_of_country = 0;
                            num_of_attack = 0 ;
                            *int_flag = 1;
                            con = 1;
                            *num = 0 ;
                            return;
                        }
                    }
                }
            }
            if(*num)
            {
                image( renderer, "but2.png" , 70 , 560);
            }
            image( renderer, "but.png" , 30 , 650);
            if(con)
            {
                led.user[active_user_id].score += 10 ;
                export_num_user();
                export_user_data();
                printf("you win!");
                con = 0;
                *int_flag = 0;
                
            }
            return;
        }
        else if((sum_user == 0) && (sum_another > 0))
        {
            image( renderer, "dds2.png" , 0 , 0);
            image( renderer, "again.png" , 495 , 640);
            SDL_Event event;
            int x= 0 , y= 0;
            while (SDL_PollEvent(&event))
            {
                
                if(event.type == SDL_QUIT)
                {
                    *flag3 = 0;
                    *running = 0;
                }
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (event.button.button == SDL_BUTTON_LEFT) 
                    {
                        SDL_GetMouseState(&x , &y);
                        if((x > 30) && (x < 110) && (y > 650) && (y <730))
                        {
                            export_no_map();
                            *num = 1 ;
                        }
                        else if((x > 495) && (x < 705) && (y > 640) && (y <715))
                        {
                            *flag3 = 0;
                            *flag2 = 1;
                            num_of_country = 0;
                            num_of_attack = 0 ;
                            *int_flag = 1;
                            con = 1;
                            *num = 0 ;
                            return;
                        }
                    }
                }
            }
            if(*num)
            {
                image( renderer, "but2.png" , 70 , 560);
            }
            image( renderer, "but.png" , 30 , 650);
            if(con)
            {
                if(led.user[active_user_id].score >= 5)
                {
                    led.user[active_user_id].score -= 5 ;
                }
            
                export_num_user();
                export_user_data();
                printf("you lose!");
                con = 0;
                *int_flag = 0;
                
            }
            return;
            
        }
       
    }
    else
    {
        sum_user = 0 ;
        sum_unknown = 0 ;
        sum_another = 0 ;
        
    }
    return;
}

void export_no_map()
{

	FILE *outfile;
	outfile = fopen ("no_map.dat", "w");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opened file\n");
		exit (1);
	}

    
    fwrite (&save_map, sizeof(Save_map), 1, outfile);
    
    
	if(fwrite != 0)
		printf("contents to file written successfully !\n");
	else
		printf("error writing file !\n");

	fclose (outfile);

}
void import_no_map()
{
	FILE *infile;
	int i = 0;
	
	infile = fopen ("no_map.dat", "r");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	fread(&save_map, sizeof(Save_map), 1, infile);
   
	fclose (infile);
}
void export_save()
{
    FILE *outfile;
	outfile = fopen ("save.dat", "w");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opened file\n");
		exit (1);
	}

    
    fwrite (&save, sizeof(Save), 1, outfile);
    
    
	if(fwrite != 0)
		printf("contents to file written successfully !\n");
	else
		printf("error writing file !\n");

	fclose (outfile);
}

void import_save()
{
    FILE *infile;
	int i = 0;
	
	// Open person.dat for reading
	infile = fopen ("save.dat", "r");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}
	
	// read file contents till end of file
	fread(&save, sizeof(Save), 1, infile);
    
	fclose (infile);
}

void export_num_country()
{

	FILE *outfile;
	outfile = fopen ("num_country.dat", "w");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opened file\n");
		exit (1);
	}

    
    fwrite (&num_of_country, sizeof(int), 1, outfile);
    
    
	if(fwrite != 0)
		printf("contents to file written successfully !\n");
	else
		printf("error writing file !\n");

	fclose (outfile);

}
void import_num_country()
{
	FILE *infile;
	int i = 0;
	
	// Open person.dat for reading
	infile = fopen ("num_country.dat", "r");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	// read file contents till end of file
	fread(&num_of_country, sizeof(int), 1, infile);
   
	fclose (infile);
}
void export_num_attack()
{

	FILE *outfile;
	outfile = fopen ("num_attack.dat", "w");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opened file\n");
		exit (1);
	}

    
    fwrite (&num_of_attack, sizeof(int), 1, outfile);
    
    
	if(fwrite != 0)
		printf("contents to file written successfully !\n");
	else
		printf("error writing file !\n");

	fclose (outfile);

}
void import_num_attack()
{
	FILE *infile;
	int i = 0;
	
	// Open person.dat for reading
	infile = fopen ("num_attack.dat", "r");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	// read file contents till end of file
	fread(&num_of_attack, sizeof(int), 1, infile);
   
	fclose (infile);
}

void import_memory()
{
    FILE *infile;
	int i = 0;
	
	// Open person.dat for reading
	infile = fopen ("memory.dat", "r");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}
	
	// read file contents till end of file
	fread(&save, sizeof(Save), 1, infile);
    
	fclose (infile);
}
