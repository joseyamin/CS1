/*
 *  UCF COP3502 Spring 2021 Assignment Solution
 *  Copyright 2021 Jose Yamin
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct table table;
long long int boringness=0; //the "excitment" of the torny

struct table{ //my nodes
    int n;
    table *l,*r;
};

table * createTable(int n){ //create table
    table *x=malloc(sizeof(table));
    x->n=n;
    x->l=NULL;
    x->r=NULL;
    return x;
}

table * addTable(table *root,int n){//add table
    if(root==NULL){
        return createTable(n);
    }
    if(root->n<n){
        root->r=addTable(root->r,n);
    }else{
        root->l=addTable(root->l,n);
    }
    return root;
}

table *createTree(int *tables,int size){ //adds tables into a bst in reverse order
    table *root=NULL;
    for(int i=size-1;i>=0;i--){
        root=addTable(root,tables[i]);
    }
    return root;
}

int victor(table* root){ 
    if(root==NULL){//if null is reached read in a player and return it
        int p;
        scanf("%d",&p);
        return p;
    }
    int l=victor(root->l); //store the victor(or next player if null/basecase) from the left side
    int r=victor(root->r);//same thing for right side
    boringness+=abs(l-r);//add the "excitment" to the global
    if(l>r){ //return tables victor equal to the greater one
        return l;
    }else{
        return r;
    }
}

void destroyTree(table *root){ //free tree
    if(root==NULL){
        return;
    }
    destroyTree(root->l);
    destroyTree(root->r);
    free(root);    
}

int main(){
    int n;
    scanf("%d",&n);
    int *tables=malloc((n-1)*sizeof(int)); 
    for(int i=0;i<n-1;i++){ //scan in tables into array
        scanf("%d",&tables[i]);
    }
    table *root=createTree(tables,n-1); //create bst of tables
    int nothing=victor(root); //will return the final victor but this is useless
    printf("%lld",boringness); //since victor function updates the global just print it for the "excitment"
    free(tables);
    destroyTree(root);
}