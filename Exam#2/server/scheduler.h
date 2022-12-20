//SIF1015 - Fall 2022
//Made by Quentin Anière

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

typedef struct ThreadArgsScheduler {
    sem_t *client_transaction_semaphore; //The semaphore of the client transaction, to avoid collision between threads
    Transaction *client_transaction; //The transaction of the client, the response
    RANGE range; //The range of VMs to process (Only used for the "list" operation)
    NUMBER number; //The VM number to process (Only used for the "delete" and "execute" operations)
} ThreadArgsScheduler;
//Used to pass arguments to a pthread

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
Transaction *read_transaction(Transaction *transaction);

#endif
