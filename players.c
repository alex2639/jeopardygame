/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Alex, Gayanath
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "players.h"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int num_players, char *name)

{
    for (int i=0; i<4; i++){
        if (strcmp(players[i].name,name)== 0){
          return true;
        }
    }
    return false;

}

// Go through the list of players and update the score for the
// player given their name
void update_score(player *players, int num_players, char *name, int score)
{
    //int score1 = 0;
    for (int i=0; i<4; i++){
        if (strcmp(players[i].name,name)==0){
            players[i].score = players[i].score + score;
            printf("Player name: %s, Player score: %d\n", players[i].name, players[i].score);
        }

    }
    printf("Hit the ENTER key to continue\n");

}
