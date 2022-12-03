#include <string.h>

#ifndef TRANSACTION_H
#define TRANSACTION_H

#define TRANSACTION_MAX_SIZE 1024

typedef struct Transaction{
    int clientID; //The ID of the client that made the transaction
    char operations[TRANSACTION_MAX_SIZE]; //The transaction itself
} Transaction;

/*
*  Creates a new transaction
*/
Transaction *createTransaction(int clientID);

/*
*  Frees the memory allocated for a transaction
*/
void freeTransaction(Transaction *transaction);

/*
* Add a operation to the transaction
*/
void addOperationToTransaction(Transaction *transaction, char *operation);

#endif
