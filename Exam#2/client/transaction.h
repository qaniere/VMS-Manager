//SIF1015 - Fall 2022
//Made by Quentin Anière

#include <string.h>

#ifndef TRANSACTION_H
#define TRANSACTION_H

#define TRANSACTION_MAX_SIZE 400

typedef struct Transaction{
    int clientID; //The ID of the client that made the transaction
    char operations[TRANSACTION_MAX_SIZE]; //The transaction itself
} Transaction;

/*
*  Creates a new transaction
*  @param clientID: the ID of the client that made the transaction
*  @return: the transaction
*/
Transaction *createTransaction(int clientID);

/*
*  Frees the memory allocated for a transaction
*  @param transaction: the transaction to free
*/
void freeTransaction(Transaction *transaction);

/*
* Add a operation to the transaction
* @param transaction: the transaction to add the operation to
* @param operation: the operation to add
*/
void addOperationToTransaction(Transaction *transaction, char *operation);

#endif
