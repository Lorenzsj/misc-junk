#include "op.h"
#include "status.h"
#include <pthread.h>

typedef struct {
    op_t op;
    status_t status;
} job_t;

job_t job_new(op_t);

void *job_handler(void*);