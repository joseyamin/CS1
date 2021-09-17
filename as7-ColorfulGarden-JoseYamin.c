/*
 *  UCF COP3502 Spring 2021 Assignment Solution
 *  Copyright 2021 Jose Yamin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rows,cols;
int **rowInfo;
int **colInfo;
int **garden;


int isValid(int r,int c){
    int groups=0, size=0; // store the amt of groups and its size
    int b=0;  //bool to know when looping through group
    for(int i=0;i<=c;i++){ //loops till current col
        if(garden[r][i]==1){
            if(b==0){//start of group
                groups++;
                b=1;
            }
            size++;//add 1 to group size            
        }else{ //group ends so size and bool reset to 0
            if(b){
                if(size!=rowInfo[r][groups]){ //make sure groups are the right size
                    return 0;
                }
            }
            b=0;
            size=0;
        }
        if(groups>rowInfo[r][0] || (groups>0 && size>rowInfo[r][groups])){ //if amt of groups or the size of group goes over the info then return 0
            return 0;
        }
    }
    groups=0;
    size=0;
    b=0;
    for(int i=0;i<=r;i++){ //same thing with col
        if(garden[i][c]==1){
            if(b==0){
                groups++;
                b=1;
            }
            size++;            
        }else{
            if(b){
                if(size!=colInfo[c][groups]){
                    return 0;
                }
            }
            b=0;
            size=0;
        }
        if(groups>colInfo[c][0] || (groups>0 && size>colInfo[c][groups])){
            return 0;
        }
    }
    return 1;
}

int solve(int r, int c){
    if(c==cols){ //if we reach end of col next row and col 0
        r++;
        c=0;
    }
    if(r==rows){ //solved if we reach end
        return 1;
    }

    garden[r][c]=1; //try black
    if(isValid(r,c)){
        if(solve(r,c+1)){ //if valid try to solve
            return 1;
        }
    }
    garden[r][c]=0; //try red
    if(isValid(r,c)){ 
        if(solve(r,c+1)){//if valid try to solve
            return 1;
        }
    }
    return 0; //return 0 not solvable this way
}


int main(){
    scanf("%d %d", &rows, &cols); //store sizes
    
    rowInfo=calloc(rows,sizeof(int*)); //store row info make row amount of arrays with each pos 0 storing amt of groups and the other positions after storing the sizies
    for(int i=0;i<rows;i++){ 
        int n;
        scanf("%d",&n);
        rowInfo[i]=calloc(n+1,sizeof(int));
        rowInfo[i][0]=n;
        for(int j=1;j<=n;j++){
            scanf("%d",&rowInfo[i][j]);
        }
    }

    colInfo=calloc(cols,sizeof(int*)); //store col info
    for(int i=0;i<cols;i++){
        int n;
        scanf("%d",&n);
        colInfo[i]=calloc(n+1,sizeof(int));
        colInfo[i][0]=n;
        for(int j=1;j<=n;j++){
            scanf("%d",&colInfo[i][j]);
        }
    }

    garden=calloc(rows,sizeof(int*)); //create garden of 0s
    for(int i=0;i<rows;i++){
        garden[i]=calloc(cols,sizeof(int));
    }

    int one=solve(0,0);
    for(int i=0;i<rows;i++){ //print garden
        for(int j=0;j<cols;j++){
            if(garden[i][j]){
                printf("B");
            }else{
                printf("r");
            }
        }
        printf("\n");
    }
}