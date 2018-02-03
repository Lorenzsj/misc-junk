#ifndef WORKER_H
#define WORKER_H

#include <stdbool.h>
#include <pthread.h>
#include "job.h"

typedef struct {
    pthread_t thread;
    job_t job;
} worker_t;

worker_t worker_new(op_t); // malloc
void worker_del(worker_t*); // free
void worker_spawn(worker_t*);
void worker_kill(worker_t*);
bool worker_active(const worker_t*);

#endif // WORKER_H
