#include "job.h"

void *job_default(void *arg)
{
    job_t *job = ((job_t*) arg);

    job->state.alive = 1;
    job->op(&job->state);

    pthread_exit(NULL);
}