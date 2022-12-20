//SIF1015 - Fall 2022
//Made by Quentin Anière

#include "fifo_transactions.h"

sem_t list_semaphore;

/*
* Create a linked list of transactions
* @return the new linked list of transactions
*/
FifoTransactions *create_fifo_transaction_list() {
    FifoTransactions *list = malloc(sizeof(FifoTransactions));
    list->transaction = NULL;
    list->next = NULL;

    sem_init(&list_semaphore, 0, 1);

    return list;
}

/*
* Add a transaction to the linked list
* @param fifoTransactions the linked list of transactions
* @param transaction the transaction to add
*/
void add_transaction(FifoTransactions *list, Transaction transaction) {
    FifoTransactions *new = malloc(sizeof(FifoTransactions));
    new->transaction = &transaction;
    new->next = NULL;
    //Allocate memory for the new transaction node

    sem_wait(&list_semaphore);
    if (list->transaction == NULL) {
        list->transaction = &transaction;

    } else {

        FifoTransactions *current = list;
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new;
    }

    sem_post(&list_semaphore);
}

/*
* Get the first transaction of the linked list
* @param fifoTransactions the linked list of transactions
* @return the first transaction of the linked list
*/
Transaction *get_first_transaction(FifoTransactions *list) {
    Transaction *result = list->transaction;
    return result;
}

/*
* Remove the first transaction of the linked list
* @param fifoTransactions the linked list of transactions
*/
void remove_first_transaction(FifoTransactions *list) {
    sem_wait(&list_semaphore);

    if(list->next == NULL) {
        list->transaction = NULL;
        
    } else {
        FifoTransactions *next = list->next;
        list->transaction = next->transaction;
        list->next = next->next;
        free(next);
    }

    sem_post(&list_semaphore);
    //Protect the list from concurrent access
}

/*
* Clear the linked list of transactions memory
* @param fifoTransactions the linked list of transactions
*/
void free_fifo_transactions_list(FifoTransactions *list) {
    FifoTransactions *current = list;
    FifoTransactions *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    sem_destroy(&list_semaphore);
}
