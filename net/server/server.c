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

void server_branch(worker_t *worker)
{
    worker_spawn(worker);
}

void server_merge(worker_t *worker)
{
    worker_kill(worker);
}

void server_shell(worker_t *workers)
{
    int i = -1;
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
        else if (!strcmp(buffer, "spawn")) {
            if (i < 3) {
                i++;
                workers[i] = worker_new(debug_op);
                server_branch(&workers[i]);
                printf("Spawned worker %d!\n", i);   
            }
        }
        else if (!strcmp(buffer, "kill")) {
            if (i == 0) {
                i--;
                printf("Killed worker 0\n");
                server_merge(&workers[0]);
            }
            else {
                printf("Killed worker %d!\n", i);
                server_merge(&workers[i]);
                i--;
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

    server_shell(workers); // interactive loop
}
