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
#include "questions.h"


// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    //question questions[NUM_QUESTIONS];
    int r;
    int *category_num=new int[3];
    bool *taken_category=new bool[5];

    //initialize categories;
    for (int i=0;i<3;i++){
      r=(rand() % 4)+1;
      if(taken_category[r]){
        i--;
      }else{
        category_num[i]=r;
        taken_category[r]=true;
      }
    }
    int index=0;
    int *questions_num=new int[NUM_QUESTIONS];

    for (int i=0;i<sizeof(category_num);i++){

      bool *taken_question=new bool[7];
      for (int j=0;j<4;j++){
        r=(rand() % 6)+1;
        if(taken_question[r]){
          j--;
        }else{
          questions_num[index]=r;
          string filename=("categories/category%d.txt",category_num[i]);
          FILE *file=fopen(filename, "r");
          if(file){
            while(fscanf(file,"%s",line)!=EOF){
              questions[index].category=line;
              categories[i]=line;
              if(strcmp(line,r)==0){
                r=fscanf(file,"%s",line);
                questions[index].question=line;
                r=fscanf(file,"%s",line);
                questions[index].answer=line;
                questions[index].answered=false;
                questions[index].value=(j+1)*200;
              }
            }
            fclose(file);
          }
          index++;
          taken_question[r]=true;
        }
      }
    }

}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    for (int i=0;i<sizeof(categories);i++){
      printf("%s\t", categories[i]);
    }
    printf("\n");
    int index=0;
    for(int i=0;i<4;i++){
      for(int j=0;j<3;j++){
        if(!questions[index].answered){
          printf("$%d\t", questions[index].value);
        }else{
          printf("\t");
        }
      }
      printf("\n");
    }

}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
  for(int i=0;i<sizeof(questions);i++){
    if(strcmp(category,questions[i].category)==0 && value==questions[i].value){
      printf("%s\n", questions[i].question);
    }
  }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    for(int i=0;i<sizeof(questions);i++){
      if(strcmp(category,questions[i].category)==0 && value==questions[i].value){
        if(strcmp(answer,questions[i].answer)==0){
          questions[i].answered=true;
          return true;
        }
      }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    for(int i=0;i<sizeof(questions);i++){
      if(strcmp(category,questions[i].category)==0 && value==questions[i].value){
        if(questions[i].answered){
          return true;
        }
      }
    }
    return false;
}
