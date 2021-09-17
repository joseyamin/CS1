/*
 *  UCF COP3502 Spring 2021 Assignment Solution
 *  Copyright 2021 Jose Yamin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//function that will print first and last letter of words

int main(void){
    int n;
    scanf("%d\n",&n); //scan in n

    char *f,*b; //holds front and back char
    f=malloc(sizeof(char));
    b=malloc(sizeof(char));
    *b=' ';
    int stringSize=0; 
    for(int i=0;i<n;i++){ //runs n amount of times
        while(1){ //reads in char and runs until a new line is found
            stringSize++; //add to the length of the word
            scanf("%c",f); 
            if(*f=='\n'){ //if newline reached break
                if(*b!=' ' && stringSize>1){ //check to print last letter
                    printf("%c",*b);
                }
                break;
            }else if(*b==' ' && *f!=' '){ //if new word is found length is 0 and print first letter
                printf("%c",*f);
                stringSize=0;
            }else if(*f==' ' && *b!=' '){//if end of word is reached check if the front letter hasn't been printed and print it
                if(stringSize>1){
                    printf("%c",*b);
                }
            }
            *b=*f; //store the last letter into b
        }
        stringSize=0; //reset the size and b and print newline
        *b=' ';
        printf("\n");
    }
}