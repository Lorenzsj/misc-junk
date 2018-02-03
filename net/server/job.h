#include "op.h"
#include "state.h"
#include <pthread.h>

typedef struct {
    state_t state;
    op_t op;
} job_t;

void *job_default(void*);