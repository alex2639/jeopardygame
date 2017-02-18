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
  printf("Tokenizing...\n");

  int i = 0;
  char inputcopy[MAX_LEN] = { 0 };
  char *token;
  const char s[2] = " ";

  strcpy(inputcopy, s);

  token = strtok(inputcopy, s);
  while (token != NULL){
    tokens[i] = token;
    i++;
    token = strtok(NULL,s);
  }

}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players){
    for (int i = 0; i < NUM_PLAYERS; i++){
        printf("Player name: %s, Player score: %d\n", players[i].name, players[i].score);
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
    printf("initialize_game\n");
    initialize_game();

    // Prompt for players names
    prompt_player_names(players, NUM_PLAYERS);
    printf("Players set. Hit the ENTER key to start the game.\n");

    // initialize each of the players in the array

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files

        display_categories();

        // Execute the game until all questions are answered
        printf("Enter the name of the contestant who is going: ");
        line(Namecompare, stdin);
        printf("Name selected\n");
        isanswer = false;

        if(player_exists(players,NUM_PLAYERS,Namecompare) == true){
          printf("Player selected\n");

          do{

            printf("Select a category along with a value: ");
            scanf("%s %d", category, &values);
            if(!valid_question(category,values)){
              printf("Invalid category/amount\n");
            }else{
              if(already_answered(category,values)){
                printf("Already answered\n");
              }else{
                display_question(category,values);
                break;
              }
            }

          }while (already_answered(category, values) || !valid_question(category,values));

            while (true){
              printf("Answer: ");
              line(givenanswer, stdin);
              printf("%s\n", givenanswer);
              //tokenize(givenanswer, tokens);

              /*if(is_valid_answer(tokens)){
                break;
              }else{
                printf("You have to type in who is or what is");
              }
              if(is_valid_answer(givenanswer)){
                break;
              }else{
                printf("You have to type in who is or what is");
              }
              */
              break;
            }
            while (true){
              if(valid_answer(category, values, givenanswer)){
                  printf("Correct!\n");
                  update_score(players,NUM_PLAYERS,Namecompare, values);
                  break;
              }else if (isanswer != 1){
                  printf("Incorrect answer\n");
                  //if player inputs wrong answer, subtract the value from
                  //player score
                  update_score(players,NUM_PLAYERS,Namecompare, -values);

                  //print_answer(category,values);
                  break;
              }
            }

        }else{
          printf("Try again: ");
        }

        // Display the final results and exit
        if(all_answered()){
          break;
        }
    }
        printf("Game over\n");
        show_results(players, NUM_PLAYERS);

    return EXIT_SUCCESS;
}

bool is_valid_answer(char **tokens){
  //printf("%s\n", tokens[0]);
  printf("%d\n", sizeof(tokens));

  return (strcmp(tokens[0],"what") == 0 || strcmp (tokens[0], "who") == 0) && strcmp(tokens[1],"is") == 0;
}

void prompt_player_names(player* players, int count){
    for (int i = 0; i < count; i++){
        printf("what is your name, Player %d? ", i + 1);
        line(players[i].name, stdin);
        players[i].score = 0;
    }

}

void line(char* destination, FILE* file){
    scanf("%s", destination);

    char buffer[BUFFER_LEN] = { 0 };
    int lengthofasnwer = strlen(destination) + 1;
    if (lengthofasnwer < BUFFER_LEN){

      //fgets(buffer, BUFFER_LEN, lengthofasnwer, file);
      fgets(buffer, BUFFER_LEN, file);

      int bufferlen = strlen(buffer);
      if (bufferlen > 0 ){
        buffer[strlen(buffer) - 1] = 0;

      }
      strcat(destination, buffer);
    }
}
