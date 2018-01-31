#include <stdio.h>
#include <stdlib.h>
#include "worker.h"

void worker_spawn(pthread_t *th, worker_op_t op)
{
    int err;
    
    err = pthread_create(th, NULL, op, NULL);
    if (err != 0) {
        fprintf(stderr, "Worker: pthread_create failed\n");
        exit(1);
    }
}

void worker_kill(pthread_t *th)
{

}
