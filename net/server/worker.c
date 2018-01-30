#include "worker.h"

void worker_spawn(worker_op_t op)
{
    op(NULL);
}

void worker_kill(void);
