//SIF1015 - Fall 2022
//Made by Quentin Anière

#include "scheduler.h" //Header file

int thread_count = 0;
pthread_t threads[MAX_THREADS];
//The array of threads, each slot contains a thread ID

/*
* Return whether the thread list is full or not
* @param void
* @return 1 if the thread list is full, 0 otherwise
*/
int is_thread_list_full() {
    return thread_count == MAX_THREADS;
}

/*
* Process the transaction given in parameter
* @param transaction The transaction to process
* @return transaction result
*/
Transaction *read_transaction(Transaction *transaction) {

    sem_t *client_transaction_semaphore = malloc(sizeof(sem_t));
    sem_init(client_transaction_semaphore, 0, 1);
    //Get the semaphore of the client transaction reponse
    //to avoid threads conflicts

    Transaction *client_transaction = malloc(sizeof(Transaction));
    client_transaction->client_id = transaction->client_id;

    char *operations[400];
    int i = 0;
    int array_size = 0;

    operations[i] = strtok(transaction->operations, "/");
    //Split the operation string into an array of string

    while(operations[i] != NULL) {
        operations[++i] = strtok(NULL, "/");
        array_size++;
    }
    
    int client = atoi(operations[0]);
    //The first operation is the client id

    for(int i = 1; i < array_size; i++) {

        char *operation = operations[i];

        sleep(0.5); 
        //Sleep half second to avoid collision between threads

    }

    for(int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }
    //Wait for all threads to finish

    return client_transaction;
}
