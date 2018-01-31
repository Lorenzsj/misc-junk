#include <stdio.h>
#include <stdlib.h>
#include "worker.h"

void worker_spawn(worker_t *worker, worker_op_t op)
{
    int err;
    
    err = pthread_create(&worker->thread, NULL, op, &worker->state);
    if (err != 0) {
        fprintf(stderr, "Worker: pthread_create failed\n");
        exit(1);
    }
}

void worker_kill(worker_t *worker)
{
    worker->state.alive = false;
}
