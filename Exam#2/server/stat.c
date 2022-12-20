//SIF1015 - Fall 2022
//Made by Quentin Anière

#include "stat.h"

void remove_spaces(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];
    str[count] = '\0';
}

/**
 * Return 1 if the file exists, 0 otherwise
 * @param filepath The path to the file to check
 * @return int 1 if the file exists, 0 otherwise
 */
int is_file(char filepath[]) {

    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        return 0;
    }

    close(fd);
    return 1;
}

/**
 * Return the file data into the transaction struct
 * @param filepath The path to the file to read
 */
void parse_data(char filepath[], Transaction *transaction) {

    remove_spaces(filepath);

    if(!is_file(filepath)) {
        strcpy(transaction->operations, "File not found");
        return;
    }

    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        strcpy(transaction->operations, "Error while opening the file");
        return;
    }

    char buffer[1024];

    struct stat file_stat;
    int inode_number = stat(filepath, &file_stat);

    if (inode_number == -1) {
        strcpy(transaction->operations, "Error while getting the file stat");
        return;
    }

    sprintf(buffer, "* Numero d'INODE: %ld/* Nombre de liens : %ld /* Taille du fichier (octets) : %ld/* Nombre de blocks : %ld", file_stat.st_ino, file_stat.st_nlink, file_stat.st_size, file_stat.st_blocks);
    strcpy(transaction->operations, buffer);

    close(fd);
}
