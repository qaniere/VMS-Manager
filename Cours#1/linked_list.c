#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Task {
    char *text; // The task text
    struct Task *next; //The memory address of the next task
};


/**
 * Flush the standard input. Flush the standard input 
 * in order to be able to scan the next input properly.
 */
void flush_stdin() { 
    for(int c = 0; c != '\n' && c != EOF; c = getchar()); 
}

/**
 * Show the menu of the program.
 */
void show_menu() {
    printf("What do you want to do?\n");

    printf(" 1 - See the list\n");
    printf(" 2 - Add a task\n");
    printf(" 3 - Remove a task\n");
    printf(" 4 - Exit the application\n");
    printf("> ");
}

/**
 * Show the list of tasks.
 * @param list The head of the linked list.
 */
void display_tasks(struct Task *list) {

    int count = 0;
    //This count will be used to number the tasks

    if(list->next == NULL) {
    //If the first node of list have no next node, it means that the list is empty
        printf("The list is empty.\n");

    } else {
        while(list->next != NULL) {
            count++;
            list = list->next;
            printf(" %d - %s\n", count, list->text);
        }
    } 
}

/**
 * Add a task to the list.
 * @param list The head of the linked list.
 */
void add_task(struct Task *list) {

    char user_input[1000];
    printf("Enter the new task : ");

    flush_stdin(); //Flush the standard input in order to properly scan the next input
    scanf("%[^\n]s",&user_input);

    struct Task *new_task = NULL;
    new_task = malloc(sizeof(struct Task));
    new_task->next = NULL;
    //Allocate memory for the new task

    new_task->text = malloc(sizeof(char) * (strlen(user_input) + 1)); 
    strcpy(new_task->text, user_input);
    //Allocate memory for the text of the new task and copy the user input into it

    while(list->next != NULL) {
    //Reach the end of the list
        list = list->next;
    }
    
    list->next = new_task;
}

/**
 * Remove a task from the list.
 * @param list The head of the linked list.
 */
void delete_task(struct Task *list) {

    if(list->next == NULL) {
        printf("The list is empty\n");
        return;
    } 

    display_tasks(list);

    int task_to_delete;
    printf("Which task must be deleted ? > ");
    scanf("%d", &task_to_delete);
    //No need to flush the standard input here
    //because only a number is expected

    int count = 0;

    struct Task* temporary_task;
    struct Task* previous_task;
    temporary_task = list;
    previous_task = list;

    task_to_delete++; //Because the first node of list is empty (Fix upcoming)

    for(int i = 0; i < task_to_delete; i++) {
    //Reach the task to delete

        if(i == 0 && task_to_delete == 1) {
            list = list->next;
            free(temporary_task);

        } else if (i == task_to_delete - 1 && temporary_task) {
            previous_task->next = temporary_task->next;
            free(temporary_task);

        } else {
            previous_task = temporary_task;
            if(previous_task == NULL) {
                break;
            } 
            temporary_task = temporary_task->next;
        }
    }
}


int main(int argc, char argv[]) {

    struct Task *list = NULL;
    list = malloc(sizeof(struct Task));
    list->text = NULL;
    list->next = NULL;

    char user_input[1000];

    printf("Welcome to the tasklist management system.\n");
    show_menu();

    while(scanf(" %s", &user_input) == 1) {

        if(user_input[0] == '1') {
            display_tasks(list);
        
        } else if(user_input[0] == '2') {
            add_task(list);

        } else if(user_input[0] == '3') {
            delete_task(list);

        } else if(user_input[0] == '4') {
            exit(0);
        }

        show_menu();
    }
    
    return 0;
}
