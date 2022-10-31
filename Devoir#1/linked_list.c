#include <stddef.h>
#include "linked_list.h"

int vm_count = 0;
struct VM_NODE *head = NULL;

void add_vm() {
    vm_count++;

    struct VM_NODE *new_vm = NULL;
    new_vm = malloc(sizeof(struct VM_NODE));
    new_vm->next = NULL; 
    //Create a new VM node in the linked list and allocate it memory

    struct VM_INFO *new_vm_infos = NULL;
    new_vm_infos = malloc(sizeof(struct VM_INFO));

    int vm_number = START_NUMBER_VM_NUMBER;
    while(is_vm_exists(vm_number)) {
        vm_number++;
    }

    new_vm_infos->number = vm_number;
    new_vm_infos->busy = 0;
    new_vm_infos->point_start_vm = NULL;
    new_vm_infos->offset_start_code = NULL;
    new_vm_infos->offset_end_code = NULL;
    //Allocate memory for the VM infos and set the values

    new_vm->vm_infos = new_vm_infos;

    if(head == NULL) {
    //If the head is null, then this is the first node of the list
        head = new_vm;

    } else {
        struct VM_NODE *list = head;
        while(list->next != NULL) {
        //Reach the end of the list
            list = list->next;
        }

        list->next = new_vm;
    }
}

void print_vm(int start, int end) {
    struct VM_NODE *list = head;

    while(list != NULL) {
        if(list->vm_infos->number >= start && list->vm_infos->number <= end) {
            printf(" - VM #%d", list->vm_infos->number);
            printf(" : Busy = %d\n", list->vm_infos->busy);
        }

        list = list->next;
    }
}

void delete_vm(int number) {
    struct VM_NODE *list = head;
    struct VM_NODE *previous = NULL;

    while(list != NULL) {
        if(list->vm_infos->number == number) {
            if(previous == NULL) {
            //If the previous node is null, then this is the first node of the list
                head = list->next;
            } else {
                previous->next = list->next;
            }

            free(list->vm_infos);
            free(list);
            break;
        }

        previous = list;
        list = list->next;
    }
}

int is_vm_exists(int number) {
    struct VM_NODE *list = head;

    while(list != NULL) {
        if(list->vm_infos->number == number) {
            return 1;
        }

        list = list->next;
    }

    return 0;
}
