#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// worker.h
void worker_init(void);
void worker_kill(void);
void worker_dispatch(pthread_t*, void *(*)(void*));
void *test(void*);

// worker.c
void *test(void *ptr)
{
    int i = 0;

    while(i < 100) {
        printf("%d\n", i);
        i++;
    }

    return NULL;
}

void worker_init(void)
{
}

void worker_kill(void)
{
}

void worker_dispatch(pthread_t *th, void *(*f)(void *p))
{
    int err = pthread_create(th, NULL, (*f), NULL);
    if (err != 0) {
        fprintf(stderr, "Worker: pthread_create failed\n");
        exit(err);
    }
}

int main(void)
{
    size_t i, j;
    const size_t MAX_THREADS = 4;
    pthread_t worker_threads[MAX_THREADS]; 

    // start worker threads
    for (i = 0; i < MAX_THREADS; i++) {
        worker_dispatch(&worker_threads[i], &test);
    }

    // wait for threads to finish
    for (j = 0; j < MAX_THREADS; j++) {
        if (pthread_join(worker_threads[j], NULL)) {
            fprintf(stderr, "Worker (%lu): pthread_join failed\n", j);
        }
    }

    return 0;
}
