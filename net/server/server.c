#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void *debug_op(void *p)
{
    printf("A debug operation");
    return NULL;
}

void server_worker(server_op_t op)
{
    worker_spawn();

    return;
}

void server_run(void)
{
    server_worker(&debug_op);
}
