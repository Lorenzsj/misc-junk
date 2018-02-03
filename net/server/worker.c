#include <stdio.h>
#include <stdlib.h>
#include "worker.h"

/**
 * @brief Return a default worker structure, requires an operation to be passed.
 */
worker_t worker_new(op_t op)
{
    worker_t worker;
    worker.job.op = op;
    worker.job.state.status = 0;
    worker.job.state.alive = false;
	return worker;
}

/**
 * @brief Spawn worker thread by using pthread_create.
 */
void worker_spawn(worker_t *worker)
{
    int err;
    
    if (!worker->job.state.alive) {
        err = pthread_create(&worker->thread, NULL, &job_default, &worker->job);
        if (err != 0) {
            fprintf(stderr, "Worker: pthread_create failed\n");
            exit(1);
        }
    }
}

/**
 * @brief Kill worker thread by setting it's alive state to false.
 */
void worker_kill(worker_t *worker)
{
    if (worker->job.state.alive) {
        worker->job.state.alive = false;
    }
}

/**
 * @brief Check if worker is alive and not suspended. Returns true is yes, false if no.
 */
 bool worker_active(const worker_t *worker)
 {
     if (worker->job.state.alive) {
         return true;
     }
     else {
         return false;
     }
 }

