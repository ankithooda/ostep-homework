#include <stdio.h>

#include "common_threads.h"

int balance = 0;

void* worker(void* arg) {
    balance++; // unprotected access 
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    pthread_mutex_t lock;
    Pthread_create(&p, NULL, worker, NULL);

    Mutex_init(&lock);
    balance++; // unprotected access
    Mutex_unlock(&lock);

    Pthread_join(p, NULL);
    printf("Balance %d\n", balance);
    return 0;
}
