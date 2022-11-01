#include <stdio.h>
#include <unistd.h>

#define THREADS 5

void say_hello(int thread_id) {
    sleep(1);
    printf("Hello from thread #%d\n", thread_id);
}

int main() {
    for (int i = 1; i <= THREADS; i++) {
        say_hello(i);
    }
    return 0;
}