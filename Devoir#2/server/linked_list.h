#include <stddef.h> //For use of NULL
#include <semaphore.h> //For implementation of semaphores

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define START_NUMBER_VM_NUMBER 1;
//The first VM number will be whatever is defined here

typedef struct VM_NODE {
    struct VM_INFO *vm_infos;
    struct VM_NODE *next;
} VM_NODE;
//The struct which contains the VM infos and the pointer to the next node

typedef struct VM_INFO {
    int number;
    unsigned char busy;
    unsigned short *point_start_vm;
    unsigned short *offset_start_code;
    unsigned short *offset_end_code;
} VM_INFO;
//The struct which contains the VM infos

/*
* Add a VM to the linked list
*/
void *add_vm();

/*
* Print a range of VMs
* @param *numbers The range of numbers, must be a RANGE struct
*/
void *print_vm(void *numbers);

/*
* Delete a VM from the linked list
* @param number The number of the VM to delete
*/
void *delete_vm(void *number);

/*Return whether a VM exists or not
* @param number The number of the VM to check
* @return 1 if the VM exists, 0 if not
*/
int is_vm_exists(int number);

/*
* Dummy function that suppose to execute binary code
* @param *args The number of the VM to execute. Must be a NUMBER struct
*/
void *execute(void *args);

/*
* Free the memory of the linked list
*/ 
void clean_linked_list();

#endif
