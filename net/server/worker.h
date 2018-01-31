#ifndef WORKER_H
#define WORKER_H

#include <pthread.h>

// contains information about the status of the worker
typedef struct {
    bool alive; // for loop condition
} state_t;
typedef struct {
    state_t state;
    pthread_t thread;
} worker_t;
typedef void *(*worker_op_t)(state_t*); // for pthreads

void worker_spawn(pthread_t*, worker_op_t);
void worker_kill(pthread_t*);

#endif // WORKER_H
