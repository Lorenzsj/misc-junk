#ifndef WORKER_H
#define WORKER_H

#include <pthread.h>

void *test(void*);
void worker_spawn(pthread_t*, void *(*)(void*));
void worker_kill(void);

#endif // WORKER_H 