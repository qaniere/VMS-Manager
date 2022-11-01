#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> //For file reading
#include <string.h> //For string manipulation
#include <pthread.h> //For thread management
#include <semaphore.h> //For mutual exclusion

#include "scheduler.h" //Header file
#include "linked_list.c" //For linked list manipulations

int thread_count = 0;
pthread_t threads[MAX_THREADS];

int is_thread_list_full() {
    return thread_count == MAX_THREADS;
}

void read_transaction_file(char * path) {
    FILE *fd = fopen(path, "r");

    if(fd == NULL) {
        perror("Error - unable to open file");
        exit(1);
    }

    size_t len = 0;
    char *line = NULL;
    int line_count = 0;
    
    while(getline(&line, &len, fd) != -1) {

        sleep(1);

        line_count++;

        if(line[0] == 'A') {
        // Add transaction

            if(!is_thread_list_full()) {
                pthread_create(&threads[thread_count], NULL, add_vm, NULL);
                thread_count++;
            } else {
                printf("Error - the thread list is full. The program will exit.");
                exit(1);
            }

        } else if(line[0] == 'L') {
        //Print a range of VMs

            char *arguments[2];
            char *numbers[2];

            arguments[0] = strtok(line, " ");
            arguments[1] = strtok(NULL, " ");

            numbers[0] = strtok(arguments[1], "-");
            numbers[1] = strtok(NULL, "-");

            if(numbers[0] == NULL || numbers[1] == NULL) {
                printf("Warning : Invalid range on line %d\n", line_count);
                continue;
            }

            RANGE *range = malloc(sizeof(RANGE));
            range->start = atoi(numbers[0]);
            range->end = atoi(numbers[1]);

            if(!is_thread_list_full()) {
                pthread_create(&threads[thread_count], NULL, print_vm, (void *) range);
                thread_count++;
            } else {
                printf("Error - the thread list is full. The program will exit.");
                exit(1);
            }

        } else if(line[0] == 'E') {
        //Delete a VM

            char *arguments[2];

            arguments[0] = strtok(line, " ");
            arguments[1] = strtok(NULL, " ");

            if(arguments[1] == NULL) {
                printf("Warning : Invalid VM number on line %d\n", line_count);
                continue;
            }

            delete_vm(atoi(arguments[1]));

        } else if(line[0] == 'X') {
        //Execute binary code on the VM

            char *arguments[3];

            arguments[0] = strtok(line, " ");
            arguments[1] = strtok(NULL, " ");
            arguments[2] = strtok(NULL, " ");

            if(arguments[1] == NULL || arguments[2] == NULL) {
                printf("Warning : Invalid VM number or binary code on line %d\n", line_count);
                continue;
            }

            if(!is_vm_exists(atoi(arguments[1]))) {
                printf("Warning : VM %d does not exist on line %d\n", atoi(arguments[1]), line_count);
                continue;
            }

            NUMBER *number = malloc(sizeof(NUMBER));
            number->number = atoi(arguments[1]);

            if(!is_thread_list_full()) {
                pthread_create(&threads[thread_count], NULL, execute, (void *) number);
                thread_count++;
            } else {
                printf("Error - the thread list is full. The program will exit.");
                exit(1);
            }
        }
    }

    free(line);
    fclose(fd);
    //Close file descriptor

    for(int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }
    //Wait for all threads to finish
}