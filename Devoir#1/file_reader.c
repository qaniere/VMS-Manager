#include <stdlib.h> //For file reading
#include <string.h> //For string manipulation

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

        line_count++;

        if(line[0] == 'A') {
        // Add transaction
            printf("Add VM\n");

        } else if(line[0] == 'L') {
        //Print VM

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

            printf("Print VM %s to %s\n", numbers[0], numbers[1]);

        } else if(line[0] == 'E') {
        //Delete a VM

            char *arguments[2];

            arguments[0] = strtok(line, " ");
            arguments[1] = strtok(NULL, " ");

            if(arguments[1] == NULL) {
                printf("Warning : Invalid VM number on line %d\n", line_count);
                continue;
            }

            printf("Delete VM %s.\n", arguments[1]);

        } else if(line[0] == 'X') {
        //Execute binary code on the VM

            char *arguments[3];

            arguments[0] = strtok(line, " ");
            arguments[1] = strtok(NULL, " ");
            arguments[2] = strtok(NULL, " ");

            printf("Execute binary code on VM %s.\n", arguments[1]);

        }
    }
} 
