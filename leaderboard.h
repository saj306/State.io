#ifndef __HEADER_LEADERBOARD_H__
#define __HEADER_LEADERBOARD_H__
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

typedef struct UserData
{
    char name[50];
    int score;

}UserData;

typedef struct leaderboard
{           

    UserData user[50];

}leaderboard;

leaderboard led ;

extern int score[50][2];



void export_user_data();
void import_user_data();
void export_num_user();
void import_num_user();
void sort_score();
void show_leaderboard(SDL_Renderer *renderer , int* running);




#endif