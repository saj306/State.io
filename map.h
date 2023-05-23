#ifndef __HEADER_MAP_H__
#define __HEADER_MAP_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "soldiers.h"
#include "extra.h"
#include "potion.h"
#include "username.h"
#include "menu.h"
#include "leaderboard.h"
#define new_max(x,y) (((x) >= (y)) ? (x) : (y))
#define new_min(x,y) (((x) <= (y)) ? (x) : (y))
#define FPS 60


static const int width = 1200;
static const int height = 750;

extern int num_of_country;


int x_barracks(int x , int w );
int y_barracks( int y , int h);
void x_y_rand_map(int xy[50][3] );
void num_of_soldiers(SDL_Renderer *renderer ,int i, int x , int y);
void make_ready_map(int num_ready_map);
void make_random_map(int num_c , int num_o);
void map(SDL_Renderer *renderer);
void change_number_of_soldiers(int num_attack , int num_soldier , int val);


#endif 