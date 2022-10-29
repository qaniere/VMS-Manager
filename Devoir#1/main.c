#include <stdio.h>
#include "file_reader.c"

int main(int argc, char *argv[]) {

    if(argv[1] == NULL){
    //No transaction file was provided
        printf("usage: %s <transaction files> \n", argv[0]);
        return 1;
    } 

    read_transaction_file(argv[1]);
}
