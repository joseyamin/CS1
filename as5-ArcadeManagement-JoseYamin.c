/*
 *  UCF COP3502 Spring 2021 Assignment Solution
 *  Copyright 2021 Jose Yamin
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct player player;

struct player{ //struct of player holds m for money and his name
    int m;
    char *name;
    player *next;
};

player *pushPlayer(player *head){ //add/push player to top of stack and return new head
    player* new=malloc(sizeof(player));
    new->name=malloc(sizeof(char)*21);
    scanf("%d%s",&new->m,new->name);
    if(head!=NULL && new->m < head->m){ //if the player is poorer then the head just copy the head(richest) info   and add it to stack
        new->m=head->m;
        new->name=strdup(head->name);
    }
    new->next=head;
    return new;
}

void peekRichest(player *head){ //print the head name since the head is always the richest
    if(head==NULL){
        printf(""); //empty print nothing?
    }else{
        printf("%s\n",head->name);
    }
}

player* popPlayer(player *head){ //pop/remove from stack and free removed player and return new head
    if(head==NULL){
        return NULL;
    }
    player *newHead=head->next;
    free(head->name);
    free(head);
    return newHead;
}

void destroyStack(player *head){ //free stack
    player *freeAble;
    while(head!=NULL){
        freeAble=head;
        head=head->next;
        free(freeAble->name);
        free(freeAble);
    }
}
int main(){
    int toDo;
    player *head; //new stack
    head=NULL;
    while(1){
        scanf("%d",&toDo);
        if(toDo==1){
            head=pushPlayer(head);
        }else if(toDo==2){
            head=popPlayer(head);
        }else if(toDo==3){
            peekRichest(head);
        }else if(toDo==0){ 
            destroyStack(head);
            return 0;
        }else{
            return 1; //input was not 1 2 3 or 0 
        }
    }
}