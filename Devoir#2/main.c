//SIF1015 - Fall 2022
//Made by Julio Bangadebia and Quentin Anière

#include <stdio.h> //For using standart output
#include "scheduler.c" //For reading files and manages threads  

int main(int argc, char *argv[]) {

    if(argv[1] == NULL){
    //No transaction file was provided
        printf("usage: %s <transaction files> \n", argv[0]);
        return 1;
    } 

    read_transaction_file(argv[1]);
    //Read the transaction file and call the function in threads to process the transactions

    clean_linked_list();
    //Free all the allocated memory

    return 0;
}
