#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define THREADS 5

void* say_hello(void* args) {
    sleep(1);
    printf("Hello from thread #%d\n", *(int*)args);
    free(args);
}

int main(int argc, char *argv[]) {
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

    return 0;
}