#include "job.h"

job_t job_new(op_t op)
{
    job_t job;

    job.status = status_new();
    job.op = op;

    return job;
}

void *job_handler(void *arg)
{
    job_t *job = ((job_t*) arg);

    job->status.active = 1;

    job->op(&job->status);

    pthread_exit(NULL);
}
