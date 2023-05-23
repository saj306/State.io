#ifndef __HEADER_POTION_H__
#define __HEADER_POTION_H__
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
#define FPS 60



extern int delay_for_potion;
extern int num_of_potion;
extern int val;

void initialize_potions();
void barracks_action();
void potion_actions(float* s);
void blink_zan(int a);
void current_potion(SDL_Renderer *renderer);
void stay_potion();
void choose_x_y_potion(double* x_rand , double* y_rand);
void choose_potion();
void potions(SDL_Renderer *renderer);


#endif 