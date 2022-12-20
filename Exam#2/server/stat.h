//SIF1015 - Fall 2022
//Made by Quentin Anière

#ifndef STAT_H
#define STAT_H

#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * Return 1 if the file exists, 0 otherwise
 * @param filepath The path to the file to check
 * @return int 1 if the file exists, 0 otherwise
 */
int is_file(char filepath[]);

/**
 * Return the file data into the transaction struct
 * @param filepath The path to the file to read
 */
void parse_data(char filepath[], Transaction *transaction);

#endif
