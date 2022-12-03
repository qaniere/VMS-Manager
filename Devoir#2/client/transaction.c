#include "transaction.h"

/*
*  Creates a new transaction
*/
Transaction *createTransaction(int clientID) {
    Transaction *transaction = malloc(sizeof(Transaction));
    transaction->clientID = clientID;
    transaction->operations[0] = '\0';
    //Empty char for now, will be filled with 

    return transaction;
}

/*
*  Frees the memory allocated for a transaction
*/
void freeTransaction(Transaction *transaction) {
    free(transaction);
}

/*
* Add a operation to the transaction
*/
void addOperationToTransaction(Transaction *transaction, char *operation) {

    for(int i = 0; i < strlen(operation); i++) {
        transaction->operations[strlen(transaction->operations)] = operation[i];
        //Add the operation to the end of the transaction operations string
    } 

    transaction->operations[strlen(transaction->operations)] = '/';
    //Add a / to the end of the transaction operations string to separate the operations
}

