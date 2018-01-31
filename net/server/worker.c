#include <stdio.h>
#include <stdlib.h>
#include "worker.h"

worker_t worker_new(op_t op)
{
	worker_t worker;
    worker.op = op;
    worker.state.err = 0;
	return worker;
}

void worker_spawn(worker_t *worker)
{
    int err;
    
    err = pthread_create(&worker->thread, NULL, worker->op, &worker->state);
    if (err != 0) {
        fprintf(stderr, "Worker: pthread_create failed\n");
        exit(1);
    }
}

void worker_kill(worker_t *worker)
{
    worker->state.alive = false;
}
