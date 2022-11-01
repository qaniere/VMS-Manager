#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define THREADS 5

sem_t semaphore;

void* say_hello(void* args) {
    sem_wait(&semaphore); //Queue start here
    sleep(1);
    printf("Hello from thread #%d\n", *(int*)args);
    sem_post(&semaphore); //Exit the queue
    free(args);
}

int main(int argc, char *argv[]) {
    sem_init(&semaphore, 0, 1); //Initialize the semaphore
    pthread_t threads[THREADS];
    int i;
    for(i = 0; i < THREADS; i++) {
        int* count = malloc(sizeof(int));
        *count = i;
        if(pthread_create(&threads[i], NULL, &say_hello, count) != 0) {
            perror("Failed to create thread");
        }
    }

    for(i = 0; i < THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    sem_destroy(&semaphore); //Close the semaphore
    return 0;
}