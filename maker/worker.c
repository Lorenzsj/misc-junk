#include <stdio.h>
#include <stdlib.h>
#include "worker.h"

void *test(void *ptr)
{
    int i = 0;

    while(i < 100) {
        printf("%d\n", i);
        i++;
    }

    return NULL;
}

void worker_spawn(pthread_t *th, void *(*f)(void *p))
{
    int err;
    
    err = pthread_create(th, NULL, (*f), NULL);
    if (err != 0) {
        fprintf(stderr, "Worker: pthread_create failed\n");
        exit(err);
    }
}

void worker_kill(void)
{
}