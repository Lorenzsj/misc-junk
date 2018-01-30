#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "worker.h"

int main(void)
{
    size_t i, j;
    const size_t MAX_THREADS = 4;
    pthread_t worker_threads[MAX_THREADS]; 

    // start worker threads
    for (i = 0; i < MAX_THREADS; i++) {
        worker_spawn(&worker_threads[i], &test);
    }

    // wait for threads to finish
    for (j = 0; j < MAX_THREADS; j++) {
        if (pthread_join(worker_threads[j], NULL)) {
            fprintf(stderr, "Worker (%lu): pthread_join failed\n", j);
        }
    }

    return 0;
}