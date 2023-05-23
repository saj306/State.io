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

int score[50][2];

void export_user_data()
{

	FILE *outfile;
	outfile = fopen ("person.dat", "w");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opened file\n");
		exit (1);
	}

    
    fwrite (&led, sizeof(leaderboard), 1, outfile);
    
    
	if(fwrite != 0)
		printf("contents to file written successfully !\n");
	else
		printf("error writing file !\n");

	fclose (outfile);

}



void import_user_data()
{
	FILE *infile;
	int i = 0;
	
	infile = fopen ("person.dat", "r");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}
	
	fread(&led, sizeof(leaderboard), 1, infile);
    
	fclose (infile);
}
void export_num_user()
{

	FILE *outfile;
	outfile = fopen ("num_user.dat", "w");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opened file\n");
		exit (1);
	}

    
    fwrite (&num_of_user, sizeof(int), 1, outfile);
    
    
	if(fwrite != 0)
		printf("contents to file written successfully !\n");
	else
		printf("error writing file !\n");

	fclose (outfile);

}
void import_num_user()
{
	FILE *infile;
	int i = 0;
	
	infile = fopen ("num_user.dat", "r");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	fread(&num_of_user, sizeof(int), 1, infile);
   
	fclose (infile);
}
void sort_score()
{
    for (int i = 0; i < num_of_user; i++)
    {
        score[i][0] = i ;
        score[i][1] = led.user[i].score ;
    }
    
    for (int s = 0; s < num_of_user; s++)
    {
        for (int u = s+1; u < num_of_user; u++)
        {
            if(score[u][1] >= score[s][1])
            {
                int temp =0;
                int temp2 =0;
                temp = score[u][1];
                temp2= score[u][0];
                score[u][1] = score[s][1] ;
                score[u][0] = score[s][0] ;
                score[s][1] = temp ;
                score[s][0] = temp2 ;
            }
        }
        
    }
    
}

void show_leaderboard(SDL_Renderer *renderer , int* running)
{
    int x=0 , y=0 ;
    SDL_Event Event ;
    int r1=239 , g1=214 ,b1=10 ;
    int r2=195 , g2=234 ,b2=129 ;
    int r3=202 , g3=14 ,b3=199 ;
    int num[50];
    for (int d = 0; d < num_of_user; d++)
    {
        num[d] = d+1;
    }
    
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
                        if((x > 35) && (x < 185) && (y > 650) && (y <703))
                        {
                              return;
                        }
                       
                    }
                break;
                
            }

        
        }
        
        SDL_SetRenderDrawColor(renderer, 238, 237, 237, 255);
        SDL_RenderClear(renderer);
        image(renderer , "ff2.png" , 0 , 0);
        image(renderer , "leaderboard.png" , 350 , 100);
        int dim = 235 ;
        int bim = 262 ;
        char temp[50];
        char temp2[20];
        neveshte(renderer , "Row         username        score" , 600 , 200 , 30 , 255 ,255 ,255 ,255);
        image(renderer , "home.png" , 35 , 650);
        for (int j = 0; j < num_of_user; j++)
        {   
            sprintf(temp,"%d" , led.user[score[j][0]].score);
            sprintf(temp2, "%d" , num[j]);

            
            if(j == 0)
            {
                image(renderer , "border6.png" , 350 , dim);
                ellipse(renderer , 420 , bim+15 , 20 , 20 , 9 , 82 , 133 ,1);
                neveshte(renderer , temp2 , 420 , bim , 30 , r1 ,g1 ,b1 ,255);
                neveshte(renderer , led.user[score[j][0]].name , 600 , bim , 30 , r2 ,g2 ,b2 ,255);
                neveshte(renderer , temp , 768 , bim , 30 , r3 ,g3 ,b3 ,255);
                dim += 70;
                bim += 57 ;
            }
            else
            {
                image(renderer , "border7.png" , 363 , dim);
                ellipse(renderer , 420 , bim+15 , 20 , 20 , 9 , 82 , 133 ,1);
                neveshte(renderer , temp2 , 420 , bim , 30 , r1 ,g1 ,b1 ,255);
                neveshte(renderer , led.user[score[j][0]].name , 600 , bim , 30 , r2 ,g2 ,b2 ,255);
                neveshte(renderer , temp , 768 , bim , 30 , r3 ,g3 ,b3 ,255);
                dim += 63;
                bim += 64 ;
                

            }
        }
        
        
    
        SDL_RenderPresent(renderer);
        SDL_Delay(FPS / 1000);
    }
    

}