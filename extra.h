#ifndef __HEADER_EXTRA_H__
#define __HEADER_EXTRA_H__
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
#include "potion.h"
#include "username.h"
#include "menu.h"
#include "leaderboard.h"
#define new_max(x,y) (((x) >= (y)) ? (x) : (y))
#define new_min(x,y) (((x) <= (y)) ? (x) : (y))
#define FPS 60

typedef struct Country
{
    char path[50] ;
    char shape[50];
    char color[50];
    int personality;
    int number_of_soldiers;
    int number_of_soldiers_copy;
    int x ;
    int y ;
    int x_of_barracks;
    int y_of_barracks;
    bool sides;
    bool user;
    
} Country;
typedef struct Potions
{
    char path[50];
    char kind[50];
    double x;
    double y;
    int time;
    int delay ;
    int stay;
    bool active;
    bool show;
    bool blink;
    int personality;
    
}Potions;
typedef struct Soldiers
{
    int id;
    int id_of_country;
    int personality;
    int source;
    int dest;
    double x_source;
    double y_source;
    double x_dest;
    double y_dest;
    int delay ;
    bool deleted;
    
}Soldiers;
typedef struct Attack
{
    int id;
    Soldiers soldiers[1000];
    int number_of_soldiers;
    int x_source;
    int y_source;
    int x_dest;
    int y_dest;
    bool active;


} Attack ;

typedef struct Save
{
    Country country[1000];
    Potions potion[10];
    Attack attack[10000];

}Save;

Save save;




typedef struct Save_map
{
    int ra_time;
    int co;
    int op;
}Save_map;
Save_map save_map;
extern int con ;
SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) ;
int printRandoms(int lower, int upper);
void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian);
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian );
void win_or_lose(SDL_Renderer *renderer,int* running , int* flag2 , int* flag3 , int* int_flag , int* num);
void export_no_map();
void import_no_map();
void export_save();
void import_save();
void export_num_country();
void import_num_country();
void export_num_attack();
void import_num_attack();
void import_memory();



#endif 