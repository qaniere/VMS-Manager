//SIF1015 - Fall 2022
//Made by Julio Bangadebia and Quentin Anière

#include <stdio.h> //For io related functions
#include <unistd.h> //For sleep system call
#include <stdlib.h> //For file reading
#include <string.h> //For string manipulation
#include <pthread.h> //For thread management

#ifndef SCHDULER_H
#define SCHDULER_H

#define MAX_THREADS 1000 
//The maximum number of threads that can be created
//If the program need to create more threads, it will warn the user and exit

typedef struct RANGE {
    int start;
    int end;
} RANGE;
//Use to pass a range of VMs to a pthread

typedef struct NUMBER {
    int number;
} NUMBER;
//Use to pass the VM number of a VM to a pthread


/*
* Return whether the thread list is full or not
* @param void
* @return 1 if the thread list is full, 0 otherwise
*/
int is_thread_list_full();

/*
* Process the transaction given in parameter
* @param transaction The transaction to process
* @return void
*/
void read_transaction(Transaction *transaction);

#endif
