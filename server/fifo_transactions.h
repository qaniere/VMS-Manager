#include <semaphore.h>

#ifndef FIFO_TRANSACTIONS_H
#define FIFO_TRANSACTIONS_H

typedef struct Transaction {
    int client_id;
    char operations[400];
} Transaction;
//The transaction struct
//Contains the client id and the operation sent by the client

typedef struct FifoTransactions {
    Transaction *transaction;
    struct FifoTransactions *next;
} FifoTransactions;
//The linked list of transactions

/*
* Create a linked list of transactions
* @return the new linked list of transactions
*/
FifoTransactions *create_fifo_transaction_list();

/*
* Add a transaction to the linked list
* @param fifoTransactions the linked list of transactions
* @param transaction the transaction to add
*/
void add_transaction(FifoTransactions *list, Transaction transaction);

/*
* Get the first transaction of the linked list
* @param fifoTransactions the linked list of transactions
* @return the first transaction of the linked list
*/
Transaction *get_first_transaction(FifoTransactions *list);

/*
* Remove the first transaction of the linked list
* @param fifoTransactions the linked list of transactions
*/
void remove_first_transaction(FifoTransactions *list);

/*
* Clear the linked list of transactions memory
* @param fifoTransactions the linked list of transactions
*/
void free_fifo_transactions_list(FifoTransactions *list);

#endif
