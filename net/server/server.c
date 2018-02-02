#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "worker.h"
#include "server.h"

void *debug_op(void *arg)
{
    state_t *state = ((state_t*) arg);

    state->alive = true;
    while (state->alive) {
        printf("A debug operation\n");
        
        sleep(1);
    }

    return NULL;
}

void server_root()
{    
    worker_t workers[4];

    server_shell(workers);
}

void server_branch(worker_t *worker)
{
    *worker = worker_new(debug_op);
    worker_spawn(worker);
}

void server_merge(worker_t *worker)
{
    worker_kill(worker);
}

void server_shell(worker_t *workers)
{
    int i = 0;
    char buffer[MAX_LINE];
    
    while(1) {
        printf("Input: ");
        if (fgets(buffer, MAX_LINE, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;
        }

        if (!strcmp(buffer, "quit")) {
            break;
        }
        else if (!strcmp(buffer, "spawn")) {
            if (i < 4) {
                printf("Spawning worker %d\n", i);
                workers[i] = worker_new(debug_op);
                server_branch(&workers[i]);
                i += 1;
            }
        }
        else if (!strcmp(buffer, "kill")) {
            printf("Killing worker %d\n", i-1);
            if (i == 0)
                server_merge(&workers[i]);
            else if (i > 0) {
                i -= 1;
                server_merge(&workers[i]);
            }
        }
        else {
            printf("Help: Try spawn, kill, quit\n");
        }

        memset(buffer, 0, sizeof(buffer));
    }
}

void server_run(void)
{
    server_root();
}
