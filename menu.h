#ifndef __HEADER_MENU_H__
#define __HEADER_MENU_H__
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
#include "leaderboard.h"




void ready_map(SDL_Renderer *renderer , int** running , int* flag2 , int* flag3);
void random_map(SDL_Renderer *renderer , int** running , int* flag2 , int* flag3);
void choise_rand_or_ready (SDL_Renderer *renderer , int* running , int* flag2 , int* flag3);
void main_menu(SDL_Renderer *renderer , int* running , int* flag2 , int* flag3 ,int* valid);



#endif