//SIF1015 - Fall 2022
//Made by Julio Bangadebia and Quentin Anière

#include "vms_linked_list.h"

struct VM_NODE *head = NULL;
//The head of the linked list

int vm_count = 0;
sem_t vm_count_semaphore;
int was_vm_count_semaphore_initialized = 0;
//The number of VMs in the linked list and the protection semaphore

sem_t list_semaphore;
int was_list_semaphores_initialized = 0;

sem_t stdout_semaphore;
int was_stdout_semaphores_initialized = 0;

/*
* Add a VM to the linked list
*/
void *add_vm(void *args) {

    ThreadArgsScheduler *thread_args = (ThreadArgsScheduler *) args;
    sem_t *client_transaction_semaphore = thread_args->client_transaction_semaphore;
    Transaction *client_transaction = thread_args->client_transaction;

    if(was_list_semaphores_initialized == 0) {
        sem_init(&list_semaphore, 0, 1);
        was_list_semaphores_initialized = 1;
    }

    if(was_vm_count_semaphore_initialized == 0) {
        sem_init(&vm_count_semaphore, 0, 1);
        was_vm_count_semaphore_initialized = 1;
    }
    //Initialize the semaphores if they were not initialized

    sem_wait(&vm_count_semaphore);
    vm_count++;
    sem_post(&vm_count_semaphore);

    struct VM_NODE *new_vm = NULL;
    new_vm = malloc(sizeof(struct VM_NODE));
    new_vm->next = NULL; 
    //Create a new VM node in the linked list and allocate it memory

    struct VM_INFO *new_vm_infos = NULL;
    new_vm_infos = malloc(sizeof(struct VM_INFO));
    //Allocate memory for the VM infos

    int vm_number = START_NUMBER_VM_NUMBER;
    while(is_vm_exists(vm_number)) {
        vm_number++;
    }
    //Find the first available VM number

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

    sem_wait(client_transaction_semaphore); 
    //Protect the client transaction

    char *message = malloc(sizeof(char) * 100);
    sprintf(message, "VM %d added/", new_vm_infos->number);

    strcat(client_transaction->operations, message);

    //Set the result of the transaction

    sem_post(client_transaction_semaphore);

    free(message);
    free(thread_args);
}

/*
* Print a range of VMs
* @param *numbers The range of numbers, must be a RANGE struct
*/
void *print_vm(void *args) {

    ThreadArgsScheduler *thread_args = (ThreadArgsScheduler *) args;
    sem_t *client_transaction_semaphore = thread_args->client_transaction_semaphore;
    Transaction *client_transaction = thread_args->client_transaction;

    RANGE numbers = thread_args->range;
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
    //Initialize the semaphores if they were not initialized

    sem_wait(&list_semaphore); //Starting to use semaphores to protect the linked list
     //Starting to use semaphores to protect the stdout

    char *message = malloc(sizeof(char) * 100);
    sprintf(message, "VMs %d-%d:/", start, end);

    sem_wait(client_transaction_semaphore);
    strcat(client_transaction->operations, message);

    while(list != NULL) {
    //Iterate through the list until the end
        if(list->vm_infos->number >= start && list->vm_infos->number <= end) {
        //If the VM number is between the range, print it
            sprintf(message, "  - VM #%d: Busy = %d/", list->vm_infos->number,  list->vm_infos->busy);
            strcat(client_transaction->operations, message);
        }

        list = list->next;
    }

    strcat(client_transaction->operations, "/");

    sem_post(&list_semaphore); //End of the list usage
     //End of the stdout usage
    sem_post(client_transaction_semaphore);

    free(args);
}

/*
* Delete a VM from the linked list
* @param number The number of the VM to delete
*/
void *delete_vm(void *args) {

    struct VM_NODE *list = head;
    struct VM_NODE *previous = NULL;

    if(was_list_semaphores_initialized == 0) {
        sem_init(&list_semaphore, 0, 1);
        was_list_semaphores_initialized = 1;
    }
    //Initialize the semaphores if they were not initialized
    
    ThreadArgsScheduler *thread_args = (ThreadArgsScheduler *) args;
    sem_t *client_transaction_semaphore = thread_args->client_transaction_semaphore;
    Transaction *client_transaction = thread_args->client_transaction;

    NUMBER s_number = thread_args->number;
    int vm_number = s_number.number;

    sem_wait(&list_semaphore); //Starting to use semaphores to protect the linked list

    while(list != NULL) {
    //Iterate through the list until the end
        if(list->vm_infos->number == vm_number) {
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

    sem_wait(client_transaction_semaphore);
    //Protect the client transaction

    char *message = malloc(sizeof(char) * 100);
    sprintf(message, "VM %d deleted/", vm_number);
    strcat(client_transaction->operations, message);

    sem_post(client_transaction_semaphore);

    sem_post(&list_semaphore); //End of the list usage
    free(args);
}

/*Return whether a VM exists or not
* @param number The number of the VM to check
* @return 1 if the VM exists, 0 if not
*/
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

/*
* Dummy function that suppose to execute binary code
* @param *args The number of the VM to execute. Must be a NUMBER struct
*/
void *execute(void *args) {

    if(was_stdout_semaphores_initialized == 0) {
        sem_init(&stdout_semaphore, 0, 1);
        was_stdout_semaphores_initialized = 1;
    }

    ThreadArgsScheduler *thread_args = (ThreadArgsScheduler *) args;
    sem_t *client_transaction_semaphore = thread_args->client_transaction_semaphore;
    Transaction *client_transaction = thread_args->client_transaction;

    NUMBER number = thread_args->number;
    int vm_number = number.number;

    sleep(2);

    sem_wait(client_transaction_semaphore);
    //Protect the client transaction

    char *message = malloc(sizeof(char) * 100);
    sprintf(message, "VM %d executed/", vm_number);
    strcat(client_transaction->operations, message);

    sem_post(client_transaction_semaphore);

    free(args);
}

/*
* Free the memory of the linked list
*/ 
void clean_linked_list() {
    struct VM_NODE *list = head;
    struct VM_NODE *next = NULL;

    while(list != NULL) {
        next = list->next;
        free(list->vm_infos);
        free(list);
        list = next;
    }

    head = NULL;
    free(head);
}
