/*
 *  UCF COP3502 Spring 2021 Assignment Solution
 *  Copyright 2021 Jose Yamin
 */

#include <stdio.h>
#include <string.h>


int main(void) {
  //declare values such as input, min and max for range, lg to save last guess
  char input[128];
  int max;
  int min=1;
  int lg=0;
  //ask for max value
  scanf("%d",&max);

  //while loop that will never stop unless user inputs yes then when guess is correct and it returns 0 and ends entire program.
  while(1){
    //guess for min value
    printf("%d\n",min);
    scanf(" %[^\n]s", input);

    //will ignore all inputs but for yes and No change. if yes then return and end program. if nochange then value is confirmed to be middle of last guess and current guess, min.
    if(strcmp(input,"Yes!!!")==0){
      return 0;
    }else if(strcmp(input,"No. No change.")==0){
      max=(lg+min)/2;
    }
    lg=min;

    //guess max value and check for yes, warmer, colder, or no change
    printf("%d\n",max);
    scanf(" %[^\n]s", input);

    //if yes then it is correct and will end program. if it is warmer then we know we it is closer to min so we can shave the max range in half and add one to min since it also wasnt min from last guess. For colder it is the other way around. No change wil make get the middle of last guess and current guess and make it the next guess.
    if(strcmp(input,"Yes!!!")==0){
      return 0;
    }else if(strcmp(input,"No. Warmer.")==0){
      lg=max;
      min=((max+min)/2)+1;
      max--;
    }else if(strcmp(input,"No. Colder.")==0){
      lg=max;
      max=(max+min)/2;
      min++;
    }else if(strcmp(input,"No. No change.")==0){
      min=(lg+max)/2;
    }
  }
  return 0;
}