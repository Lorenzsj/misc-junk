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

void server_branch(worker_t *workers)
{
    size_t i;

    for (i = 0; i < 4; i++) {
        workers[i] = worker_new(debug_op);
        worker_spawn(&workers[i]);
    }
}

void server_merge(worker_t *worker)
{
    worker_kill(worker);
}

void server_shell(worker_t *workers)
{
    size_t i = 0;
    char buffer[MAX_LINE];

    
    while(1) {
        printf("Input: ");
        if (fgets(buffer, MAX_LINE, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0; // remove newline and carriage
        }

        // process input
        if (!strcmp(buffer, "debug")) {
            printf("Output: %s\n", buffer);
        }
        else if (!strcmp(buffer, "kill")) {
            if (i < 4) {
                printf("Killed worker %lu!\n", i+1);
                server_merge(&workers[i]);
                i++;
            }
            else {
                printf("No workers to kill!\n");
            }
        }
        else if (!strcmp(buffer, "quit")) {
            break;
        }
        else {
            printf("Try debug, kill, quit\n");
        }

        memset(buffer, 0, sizeof(buffer));
    }
}

void server_run(void)
{
    worker_t workers[4];

    server_branch(workers); // create worker threads

    server_shell(workers); // interactive loop
}
