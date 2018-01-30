#ifndef SERVER_H
#define SERVER_H

#include "worker.h"

// types
typedef void *(*server_op_t)(void*); // for pthreads
typedef struct {
    int err;
} server_t;

void server_run(void);
void server_worker(server_op_t);

#endif // SERVER_H
