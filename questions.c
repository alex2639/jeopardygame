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
#include "questions.h"
#include <time.h>

#define MAX_LEN 256
#define NUM_FILES 4
#define NUM_QUESTIONS_PER_FILE  6

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    int r;
    srand(time(NULL));
    int category_num[NUM_CATEGORIES];
    bool taken_category[NUM_FILES+1];//the 3 categories picked will be unique and random
    for(int i=0;i<NUM_FILES+1;i++){
      taken_category[i]=false;
    }

    //initialize categories randomly;
    for (int i=0;i<NUM_CATEGORIES;i++){
      r=(rand() % NUM_FILES)+1;
      if(taken_category[r]){
        i--;
      }else{
        category_num[i]=r;
        taken_category[r]=true;
      }
    }
    int index=0;
    char line[MAX_LEN];

    //initialize questions for each category randomly
    for (int i=0;i<NUM_CATEGORIES;i++){
      bool taken_question[NUM_QUESTIONS_PER_FILE+1];
      for(int j=0;j<NUM_QUESTIONS_PER_FILE+1;j++){
        taken_question[j]=false;
      }
      for (int j=0;j<4;j++){//number of questions per category
        r=(rand() % 6)+1;
        if(taken_question[r]){
          j--;
        }else{
          int q=r;
          char *filename=malloc(strlen("categories/category")+2+strlen(".txt"));
          strcpy(filename,"categories/category");
          char str[MAX_LEN];
          sprintf(str,"%d",category_num[i]);
          strcat(filename,str);
          strcat(filename,".txt");
          FILE *file=fopen(filename, "r");

          int l=0;
          if(file){
            while(fscanf(file,"%s",line)!=EOF){
              if(l==0){//get category name
                strcpy(questions[index].category,line);
                strcpy(categories[i],line);
                l++;
              }else{
                sprintf(str,"%d",r);
                if(strcmp(line,str)==0){
                  r=fscanf(file,"%s",line);
                  char phrase[MAX_LEN];
                  strcpy(phrase,"");
                  while(strcmp(line,"/")!=0){
                    //append line to a string array/vector
                    strcat(line," ");
                    strcat(phrase,line);
                    r=fscanf(file,"%s",line);
                  }
                  strcpy(questions[index].question,phrase);
                  r=fscanf(file,"%s",line);
                  strcpy(questions[index].answer,line);
                  questions[index].answered=false;
                  questions[index].value=(j+1)*200;
                }
              }
            }
            fclose(file);
          }
          index++;
          taken_question[q]=true;
        }
      }
    }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    for (int i=0;i<3;i++){
      printf("%s\t", categories[i]);
    }
    printf("\n");
    int index=0;
    for(int i=0;i<4;i++){
      index=0;
      for(int j=0;j<3;j++){
        if(!questions[index+i].answered){
          printf("$%d\t", questions[index+i].value);
        }else{
          printf("\t");
        }
        index+=4;
      }
      printf("\n");
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
  for(int i=0;i<NUM_QUESTIONS;i++){
    if(strcmp(category,questions[i].category)==0 && value==questions[i].value){
      printf("%s\n", questions[i].question);
    }
  }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    for(int i=0;i<NUM_QUESTIONS;i++){
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
    for(int i=0;i<NUM_QUESTIONS;i++){
      if(strcmp(category,questions[i].category)==0 && value==questions[i].value){
        if(questions[i].answered){
          return true;
        }
      }
    }
    return false;
}

//see if all questions are answered
bool all_answered(void){
  for(int i=0;i<NUM_QUESTIONS;i++){
    if(!questions[i].answered){
      return false;
    }
  }
  return true;
}

//see if question and dollar value exists
bool valid_question(char *category, int value){
  for(int i=0;i<NUM_QUESTIONS;i++){
    if((strcmp(questions[i].category,category)==0) && questions[i].value==value){
      return true;
    }
  }
  return false;
}
