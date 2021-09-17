/*
 *  UCF COP3502 Spring 2021 Assignment Solution
 *  Copyright 2021 Jose Yamin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function to return 1 if is pretty and 0 if is not pretty
int isPretty(char **arr,int size){
    for(int i=0;i<size-1;i++){
        if(!((char)arr[i][strlen(arr[i])-1]==(char)arr[i+1][0])){
            return 0;
        }
    }
    return 1;
}

//print arr free all allocations and exit
void printarr(char **arr,int size,char*tmp){
    for(int i=0;i<size;i++){
        printf("%s ",arr[i]);
        free(arr[i]);
    }
    free(arr);
    exit(0);
}

void permute(char **arr,int place,int size,char*tmp){
    if(place==size-1){ //if the fixed point reaches the last letter the last permuation is done
        if(isPretty(arr,size)){ //if is pretty returns 1 it is pretty so calls printarr and exits
            printarr(arr,size,tmp);
        }
    }else{
        for(int i=place;i<size;i++){//a loop for every letter starting at the fixed/place
            tmp=arr[place];
            arr[place]=arr[i];   //swap values with fixed positon and every other position after
            arr[i]=tmp;
            permute(arr,place+1,size,tmp); //go into recursive call but the fixed is the next letter
            tmp=arr[place];
            arr[place]=arr[i];   // back track swap back
            arr[i]=tmp;
        }
    }
}

int main(){
    char **arr;
    int size;

    scanf("%d",&size);  //store size input

    char*tmp=malloc(sizeof(char)*20);  //malloc **arr and *tmp
    arr=malloc(sizeof(char*)*size);
    for (int i=0;i<size;i++){
        arr[i]=malloc(sizeof(char)*20);
        scanf("%s",arr[i]);
    }

    permute(arr,0,size,tmp);

    return 0;
}