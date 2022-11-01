#include <stddef.h> // For use of NULL
#include <semaphore.h> // For implementation of semaphores

#include "linked_list.h"

int vm_count = 0;
struct VM_NODE *head = NULL;

sem_t list_semaphore;
int was_list_semaphores_initialized = 0;

sem_t stdout_semaphore;
int was_stdout_semaphores_initialized = 0;

void *add_vm() {

    if(was_list_semaphores_initialized == 0) {
        sem_init(&list_semaphore, 0, 1);
        was_list_semaphores_initialized = 1;
    }

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


    sem_wait(&list_semaphore); //Starting to use semaphores to protect the linked list

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

    sem_post(&list_semaphore); //End of the list usage
}

void *print_vm(void *range) {

    RANGE numbers = *(RANGE *)range;
    int start = numbers.start;
    int end = numbers.end;

    struct VM_NODE *list = head;

    if(was_list_semaphores_initialized == 0) {
        sem_init(&list_semaphore, 0, 1);
        was_list_semaphores_initialized = 1;
    }

    if(was_stdout_semaphores_initialized == 0) {
        sem_init(&stdout_semaphore, 0, 1);
        was_stdout_semaphores_initialized = 1;
    }


    sem_wait(&list_semaphore); //Starting to use semaphores to protect the linked list
    sem_wait(&stdout_semaphore); //Starting to use semaphores to protect the stdout

    printf("VMs from %d to %d:\n", start, end);

    while(list != NULL) {
    //Iterate through the list until the end
        if(list->vm_infos->number >= start && list->vm_infos->number <= end) {
        //If the VM number is between the range, print it
            printf(" - VM #%d", list->vm_infos->number);
            printf(" : Busy = %d\n", list->vm_infos->busy);
        }

        list = list->next;
    }

    sem_post(&list_semaphore); //End of the list usage
    sem_post(&stdout_semaphore); //End of the stdout usage
}

void delete_vm(int number) {
    struct VM_NODE *list = head;
    struct VM_NODE *previous = NULL;

    while(list != NULL) {
    //Iterate through the list until the end
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

void *execute(void *args) {

    if(was_stdout_semaphores_initialized == 0) {
        sem_init(&stdout_semaphore, 0, 1);
        was_stdout_semaphores_initialized = 1;
    }

    sem_wait(&stdout_semaphore); //Starting to use semaphores to protect the stdout
    printf("Executing binary file on VM #%c\n", *(char *)args);
    sem_post(&stdout_semaphore); //End of the stdout usage
}
