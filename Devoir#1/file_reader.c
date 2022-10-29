#include <stdlib.h>

void read_transaction_file(char * path) {
    FILE *fd = fopen(path, "r");

    if(fd == NULL) {
        perror("Error - unable to open file");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;

    while(getline(&line, &len, fd) != -1) {
        printf("%s", line);
    } 
} 
