#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define START_NUMBER_VM_NUMBER 1;

typedef struct VM_NODE {
    struct VM_INFO *vm_infos;
    struct VM_NODE *next;
} VM_NODE;

typedef struct VM_INFO {
    int number;
    unsigned char busy;
    unsigned short *point_start_vm;
    unsigned short *offset_start_code;
    unsigned short *offset_end_code;
} VM_INFO;

void add_vm();
void print_vm(int start, int end);
void delete_vm(int number);
int is_vm_exists(int number);

#endif