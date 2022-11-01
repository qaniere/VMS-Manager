#ifndef SCHDULER_H
#define SCHDULER_H

#define MAX_THREADS 1000 
//The maximum number of threads that can be created
//If the program need to create more threads, it will warn the user and exit

typedef struct RANGE {
    int start;
    int end;
} RANGE;
//Use to pass a range of VMs to a pthread

typedef struct NUMBER {
    int number;
} NUMBER;
//Use to pass the VM number of a VM to a pthread


/*
* Return whether the thread list is full or not
* @param void
* @return 1 if the thread list is full, 0 otherwise
*/
int is_thread_list_full();

/*
* Read the transaction file and call the function in threads to process the transactions
* @param path The path of the transaction file
* @return void
*/
void read_transaction_file(char * path);

#endif
