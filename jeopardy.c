/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4
#define TOKENS_COUNT 3


void prompt_player_names(player* players, int count);

void line(char* destination, FILE* file);

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens){

    int j = 0;
    char inputcopy[MAX_LEN] = { 0 };
    char *token;
    const char s[2] = " ";

    strcpy(inputcopy, s);

    token = strtok(inputcopy, s);
    while (token != NULL){
        tokens[j] = token;
        i++;
        token = strtok(NULL,s);
    }

}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players){
    for (int i = o; i < NUM_PLAYERS; i++){
        printf("Player name: %s, Player score: %d\n", players[i].name, players[i].score)
    }
}


int main(int argc, char *argv[])
{
    int values = 0;

    char *tokens[BUFFER_LEN];
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char Namecompare[BUFFER_LEN];
    char category[BUFFER_LEN] = { 0 };
    bool isanswer = false;
    char givenanswer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    
    // Prompt for players names
    prompt_player_names(players, NUM_PLAYERS);
    
    // initialize each of the players in the array

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files
        display_categories();

        // Execute the game until all questions are answered
        printf("Enter the name of the contestant");
            line(Namecompare, stdin);
        isanswer = false;


        if(player_exists(players,Namecompare) == true){
            
            while (already_answered(category, values)){

                printf("Select a category along with a value:")
                scanf("%s %d", category, &values);

                display_question(category,values);
            }

            while (true){
                line(givenanswer, stdin);
                tokenize(givenanswer, tokens);

                if(is_valid_answer(tokens))
                    break;
                printf("You have to type in who is or what is");
            }

            if(valid_answer(category, values, givenanswer)){
                printf("correct");
                update_score(players,Namecompare, values);
            }
            else if (isanswer != 1){
                printf("incorret answer, answer was");
                print_answer(category,val);
            }
        }

        // Display the final results and exit
    }
        printf("Game over");
        show_results(players);

    return EXIT_SUCCESS;
}

bool is_valid_answer(char **tokens){
return (strcmp(tokens[0],"what") == 0 || strcmp (tokens[0], "who") == 0) && strcmp(tokens[i],"is") == 0;
}

void prompt_player_names(player* players, int count){
    for (int i = 0; i < count; i++){
        printf("what is you name", i + 1);
        line(players[i].name, stdin);
        players[i].score = 0;
    }
    
}

void line(char* destination, FILE* File){
    scanf("%s", destination);

    char buffer[BUFFER_LEN] = { 0 };
    int lengthofasnwer = strlen(destination) + 1;
    if (lengthofasnwer < BUFFER_LEN){

    fgets(buffer, BUFFER_LEN, lengthofasnwer, file);
    int bufferlen = strlen(buffer);
    if (bufferlen > 0 ){
            buffer[strlen(buffer) - 1] = 0;

    }
    strcat(destination, buffer);
    }
}