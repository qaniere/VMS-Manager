//SIF1015 - Fall 2022
//Made by Julio Bangadebia and Quentin Anière

#include "scheduler.h" //Header file
#include "vms_linked_list.c" //For linked list manipulations

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

    Transaction *client_transaction = malloc(sizeof(Transaction));
    client_transaction->client_id = transaction->client_id;

    char *operations[400];
    int i = 0;
    int array_size = 0;

    operations[i] = strtok(transaction->operations, "/");

    while(operations[i] != NULL) {
        operations[++i] = strtok(NULL, "/");
        array_size++;
    }
    
    int client = atoi(operations[0]);

    for(int i = 0; i < array_size; i++) {

        char *operation = operations[i];

        sleep(1); 
        //Sleep 1 second to avoid collision between threads

        if(operation[0] == 'A') {
        //Add a VM

            if(!is_thread_list_full()) {

                ThreadArgsScheduler *args = malloc(sizeof(ThreadArgsScheduler));
                args->client_transaction_semaphore = client_transaction_semaphore;
                args->client_transaction = client_transaction;

                pthread_create(&threads[thread_count], NULL, (void *) add_vm, (void *) args);
                thread_count++;

                printf("Client %d: VM added\n", client);

            } else {
            //The transaction file required to create more threads than the maximum number of threads
                printf("Error - the thread list is full. The program will exit.");
                exit(1);
            }

        } else if(operation[0] == 'L') {
        //Print a range of VMs

            char *arguments[2];
            char *numbers[2];

            arguments[0] = strtok(operation, " ");
            arguments[1] = strtok(NULL, " ");

            numbers[0] = strtok(arguments[1], "-");
            numbers[1] = strtok(NULL, "-");

            if(numbers[0] == NULL || numbers[1] == NULL) {
                printf("Client %d: Invalid range of VMs. The program will ignore this operation.\n", client);
                continue;
            }

            //Use a struct to pass the range to the thread
            RANGE *range = malloc(sizeof(RANGE));
            range->start = atoi(numbers[0]);
            range->end = atoi(numbers[1]);

            ThreadArgsScheduler *args = malloc(sizeof(ThreadArgsScheduler));
            args->client_transaction_semaphore = client_transaction_semaphore;
            args->client_transaction = client_transaction;
            args->range = *range;
            
            if(!is_thread_list_full()) {
                pthread_create(&threads[thread_count], NULL, print_vm, (void *) args);
                thread_count++;

                printf("Client %d: VMs %d-%d printed\n", client, range->start, range->end);

            } else {
            //The transaction file required to create more threads than the maximum number of threads
                printf("Error - the thread list is full. The program will exit.");
                exit(1);
            }

        } else if(operation[0] == 'E') {
        //Delete a VM

            char *arguments[2];

            arguments[0] = strtok(operation, " ");
            arguments[1] = strtok(NULL, " ");

            if(arguments[1] == NULL) {
                printf("Client %d: Invalid VM number. The program will ignore this operation.\n", client);
                continue;
            }

            struct NUMBER *number = malloc(sizeof(NUMBER));
            number->number = atoi(arguments[1]);

            ThreadArgsScheduler *args = malloc(sizeof(ThreadArgsScheduler));
            args->client_transaction_semaphore = client_transaction_semaphore;
            args->client_transaction = client_transaction;
            args->number = *number;

            if(!is_thread_list_full()) {
                pthread_create(&threads[thread_count], NULL, delete_vm, (void *) args);
                thread_count++;

                printf("Client %d: VM %d deleted\n", client, number->number);

            } else {
            //The transaction file required to create more threads than the maximum number of threads
                printf("Error - the thread list is full. The program will exit.");
                exit(1);
            }

        } else if(operation[0] == 'X') {
        //Execute binary code on the VM
        //(This function is more a proof of concept than a real function)

            char *arguments[3];

            arguments[0] = strtok(operation, " ");
            arguments[1] = strtok(NULL, " ");
            arguments[2] = strtok(NULL, " ");

            if(arguments[1] == NULL || arguments[2] == NULL) {
                printf("Client %d: Invalid VM number or binary code. The program will ignore this operation.\n", client);
                continue;
            }

            if(!is_vm_exists(atoi(arguments[1]))) {
                printf("Client %d: VM %d does not exist", atoi(arguments[1]), client);
                continue;
            }

            //Use a struct to pass the VM number and the binary code to the thread
            NUMBER *number = malloc(sizeof(NUMBER));
            number->number = atoi(arguments[1]);

            ThreadArgsScheduler *args = malloc(sizeof(ThreadArgsScheduler));
            args->client_transaction_semaphore = client_transaction_semaphore;
            args->client_transaction = client_transaction;
            args->number = *number;

            if(!is_thread_list_full()) {
                pthread_create(&threads[thread_count], NULL, execute, (void *) args);
                thread_count++;

                printf("Client %d: VM %d executed\n", client, number->number);

            } else {
            //The transaction file required to create more threads than the maximum number of threads

                printf("Error - the thread list is full. The program will exit.");
                exit(1);
            }
        }

    }

    for(int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }
    //Wait for all threads to finish

    return client_transaction;
}
