/*
 *  UCF COP3502 Spring 2021 Assignment Solution
 *  Copyright 2021 Jose Yamin
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct customer customer;

struct customer{ //struct to hold name, ammount of bills tokens, and its units its worth
    char name[21];
    long long int tokens, bills;
    long long int units;
};

customer *readCustomerArr(int size){ //reads in and returns the pointer of size amount of customers
    customer *arr=malloc(sizeof(customer)*size);
    for(int i=0;i<size;i++){
        scanf("%s %lld %lld",arr[i].name,&arr[i].tokens,&arr[i].bills);
    }
    return arr;
}

void calculateAllUnits(customer *arr,int size, long long int tokensToUnits, long long int billsToUnits){ //iterate through the customer arr and calculate its units and save them based conversion
    for(int i=0;i<size;i++){
        arr[i].units=(arr[i].tokens * tokensToUnits) + (arr[i].bills * billsToUnits);
    }
}

void mergeSortCustomers(customer *arr,int size){ //sort the array based on units least to greatest
    // Base case
    if (size <= 1) {
        return;
    }

    int mid = size / 2;
    mergeSortCustomers(arr, mid);
    mergeSortCustomers(arr+mid, size-mid);

    // merge the array
    customer * temp = calloc(size, sizeof(customer));
    int fptr = 0;
    int bptr = mid;
    for (int i = 0; i < size; i++) {
        if (fptr < mid && bptr < size) {
            if (arr[fptr].units < arr[bptr].units) { // front has smaller element
                temp[i] = arr[fptr];
                fptr++;
            } else { // back has smaller (or equal) element
                temp[i] = arr[bptr];
                bptr++;
            }
        } else if (fptr < mid) { // front is non-empty, back is not
            temp[i] = arr[fptr];
            fptr++;
        } else { // back is non-empty, front is not
            temp[i] = arr[bptr];
            bptr++;
        }
    }
    for (int i = 0; i < size; i++)
        arr[i] = temp[i];
    free(temp);
}

void printNames(customer *arr,int size){ //print names backwards
    for(int i=size-1;i>=0;i--){
        printf("%s\n",arr[i].name);
    }
}

int main(){
    int size;
    scanf("%d",&size);

    customer *customerArr=readCustomerArr(size);

    long long int tokensToUnits, billsToUnits;
    scanf("%lld %lld",&billsToUnits,&tokensToUnits);

    calculateAllUnits(customerArr,size,tokensToUnits,billsToUnits);
    mergeSortCustomers(customerArr,size);
    printNames(customerArr,size);

    free(customerArr);
    return 0;
}