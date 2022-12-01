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
* Read the transaction file and call the function in threads to process the transactions
* @param path The path of the transaction file
* @return void
*/
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
        //Sleep 1 second to avoid collision between threads

        line_count++;

        if(line[0] == 'A') {
        //Add a VM

            if(!is_thread_list_full()) {
                pthread_create(&threads[thread_count], NULL, add_vm, NULL);
                thread_count++;

            } else {
            //The transaction file required to create more threads than the maximum number of threads
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

            //Use a struct to pass the range to the thread
            RANGE *range = malloc(sizeof(RANGE));
            range->start = atoi(numbers[0]);
            range->end = atoi(numbers[1]);

            if(!is_thread_list_full()) {
                pthread_create(&threads[thread_count], NULL, print_vm, (void *) range);
                thread_count++;

            } else {
            //The transaction file required to create more threads than the maximum number of threads
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

            struct NUMBER *number = malloc(sizeof(NUMBER));
            number->number = atoi(arguments[1]);

            if(!is_thread_list_full()) {
                pthread_create(&threads[thread_count], NULL, delete_vm, (void *) number);
                thread_count++;

            } else {
            //The transaction file required to create more threads than the maximum number of threads
                printf("Error - the thread list is full. The program will exit.");
                exit(1);
            }

        } else if(line[0] == 'X') {
        //Execute binary code on the VM
        //(This function is more a proof of concept than a real function)

            char *arguments[3];

            arguments[0] = strtok(line, " ");
            arguments[1] = strtok(NULL, " ");
            arguments[2] = strtok(NULL, " ");

            if(arguments[1] == NULL || arguments[2] == NULL) {
                printf("Warning : Invalid VM number or binary code on line %d\n", line_count);
                continue;
            }

            if(!is_vm_exists(atoi(arguments[1]))) {
                printf("Warning : VM %d does not exist", atoi(arguments[1]));
                continue;
            }

            //Use a struct to pass the VM number and the binary code to the thread
            NUMBER *number = malloc(sizeof(NUMBER));
            number->number = atoi(arguments[1]);

            if(!is_thread_list_full()) {
                pthread_create(&threads[thread_count], NULL, execute, (void *) number);
                thread_count++;

            } else {
            //The transaction file required to create more threads than the maximum number of threads

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
