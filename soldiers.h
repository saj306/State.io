#ifndef __HEADER_SOLDIERS_H__
#define __HEADER_SOLDIERS_H__
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
#include "extra.h"
#include "potion.h"
#include "username.h"
#include "menu.h"
#include "leaderboard.h"
#define new_max(x,y) (((x) >= (y)) ? (x) : (y))
#define new_min(x,y) (((x) <= (y)) ? (x) : (y))
#define FPS 60


extern double delay;
extern int num_of_attack;
extern int fin_sourse ;
extern int fin_dest ;
extern int dal;


void choose_color(int kind , int* r , int* g , int* b);
void move_soldiers(SDL_Renderer *renderer );
void Sending_soldiers(SDL_Renderer *renderer ,int source, int dest );
void growth_of_soldiers();
void artificial_intelligence(SDL_Renderer *renderer , int* flag);
void event_handler (int* running ,SDL_Renderer *renderer );


#endif 