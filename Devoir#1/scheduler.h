#ifndef SCHDULER_H
#define SCHDULER_H

#define MAX_THREADS 1000 
//The maximum number of threads that can be created
//If the program need to create more threads, it will warn the user and exit

typedef struct RANGE {
    int start;
    int end;
} RANGE;

//Read the transaction file and call the functioneed to create more threads, it will n to process the transactions
void read_transaction_file(char * path);

//Return 1 if the thread list is full, 0 otherwise
int is_thread_list_full();

#endif
