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
    (*state).alive = true;

    while ((*state).alive) {
        printf("%d: A debug operation\n", (*state).err);
        
        sleep(1);
    }

    return NULL;
}

void server_branch(size_t threads)
{
    size_t i;
    worker_t workers[threads];

    for (i = 0; i < threads; i++) {
        
        worker_spawn(&workers[i], &debug_op);
    }

    sleep(5);
    worker_kill(&workers[0]);
    
}

void server_merge(void)
{

}

void server_shell(void)
{
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
        else if (!strcmp(buffer, "quit")) {
            break;
        }
        else {
            printf("Try debug, quit\n");
        }

        memset(buffer, 0, sizeof(buffer));
    }
}

void server_run(void)
{
    server_branch(1); // create worker threads

    server_shell(); // interactive loop
}
