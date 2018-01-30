#ifndef WORKER_H
#define WORKER_H

#include <pthread.h>

typedef void *(*worker_op_t)(void*); // for pthreads

void worker_spawn(worker_op_t);

#endif // WORKER_H
