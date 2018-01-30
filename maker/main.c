#include <stdio.h> // printf, fprintf
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "client.h"
#include <string.h>
#include "aux.h"
#include "server.h"

server_on = true;
int cmd = 0;

int main(int argc, char *argv[])
{
    int err;
    pthread_t server_thread;

    err = pthread_create(&server_thread, NULL, server_run, NULL);
    if (err != 0) {
    	fprintf(stderr, "Error: Unable to create server_thread - %s\n", strerror(err));
    	return 1;
    }

    client_run();

    if (pthread_join(server_thread, NULL)) {
        fprintf(stderr, "Error: Unable to join server_thread\n");
    }

    return 0;
}
