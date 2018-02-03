#include <stdio.h>
#include <stdlib.h>
#include "worker.h"

/**
 * @brief Return a default worker structure, requires an operation to be passed.
 */
worker_t worker_new(op_t op)
{
    worker_t worker;

    worker.job = job_new(op);

	return worker;
}

/**
 * @brief Spawn worker thread by using pthread_create.
 */
void worker_spawn(worker_t *worker)
{
    int err;
    
    if (!worker_active()) {
        err = pthread_create(&worker->thread, NULL, &job_handler, &worker->job);
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
    if (worker_active()) {
        worker->job.status.active = 0;
    }
}

/**
 * @brief Check if worker is alive and not suspended. Returns true is yes, false if no.
 */
 bool worker_active(const worker_t *worker)
 {
     if (worker->job.status.active) {
         return 1;
     }
     else {
         return 0;
     }
 }

