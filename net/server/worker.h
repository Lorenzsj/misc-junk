#ifndef WORKER_H
#define WORKER_H

#include <stdbool.h>
#include <pthread.h>

// types
typedef void *(*op_t)(void*); // for pthreads

// information about the worker
typedef struct {
    volatile bool alive; // loop condition
    int err;
} state_t;
// wrapper
typedef struct {
    pthread_t thread;
    state_t state;
    op_t op;
} worker_t;

worker_t worker_new(op_t);
void worker_spawn(worker_t*);
void worker_kill(worker_t*);

#endif // WORKER_H
