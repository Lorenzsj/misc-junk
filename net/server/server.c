#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "worker.h"
#include "server.h"

#define MIN_WORKERS 0
#define MAX_WORKERS 4

void debug_op(status_t *status)
{
    while (status->active) {
        printf("A debug operation\n");
        
        sleep(1);
    }
}

void server_root()
{    
    worker_t workers[MAX_WORKERS];

    server_shell(workers);
}

void server_branch(worker_t *worker)
{
    *worker = worker_new(&debug_op);
    worker_spawn(worker);
}

void server_merge(worker_t *worker)
{
    worker_kill(worker);
}

void server_run(void)
{
    server_root();
}

/* debug functions */
void server_shell(worker_t *workers)
{
    size_t i = 0;
    char buffer[MAX_LINE];
    
    while(1) {
        printf("$ ");
        if (fgets(buffer, MAX_LINE, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;
        }
        else {
            break;
        }

        if (!strcmp(buffer, "quit")) {
            break;
        }
        else if (!strcmp(buffer, "spawn")) {
            if (i < MAX_WORKERS) {
                printf("Spawning worker %lu\n", i);
                workers[i] = worker_new(debug_op);
                server_branch(&workers[i]);
                i += 1;
            }
        }
        else if (!strcmp(buffer, "kill")) {
            printf("Killing worker %lu\n", i-1);
            if (i == MIN_WORKERS)
                server_merge(&workers[i]);
            else if (i > MIN_WORKERS) {
                i -= 1;
                server_merge(&workers[i]);
            }
        }
        else if (!strcmp(buffer, "active")) {
            if (i == 0) {
                if (worker_active(&workers[i])) {
                    printf("Worker %lu is active\n", i);
                }
                else {
                    printf("Worker %lu is not active\n", i);
                }
            }
            else if (i < MAX_WORKERS) {
                if (worker_active(&workers[i-1])) {
                    printf("Worker %lu is active\n", i-1);
                }
                else {
                    printf("Worker %lu is not active\n", i-1);
                }
            }
        }
        else {
            printf("Help: Try spawn, kill, active, quit\n");
        }

        memset(buffer, 0, sizeof(buffer));
    }
}
