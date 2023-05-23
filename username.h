#ifndef __HEADER_USERNAME_H__
#define __HEADER_USERNAME_H__
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
#include "menu.h"
#include "leaderboard.h"
#define new_max(x,y) (((x) >= (y)) ? (x) : (y))
#define new_min(x,y) (((x) <= (y)) ? (x) : (y))
#define FPS 60

extern int num_of_user;
extern int active_user_id;


void check_user(char username[]);
void image(SDL_Renderer *renderer , char name[], int x ,int y);
void neveshte(SDL_Renderer *renderer , char username[] , int x , int y ,int size, int r , int g , int b , int a);
void input_username(SDL_Renderer *renderer , int* running , int* flag1 , int* flag2);


#endif	