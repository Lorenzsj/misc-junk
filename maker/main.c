#include <stdio.h> // printf, fprintf
#include <stdlib.h>
#include <stdbool.h> // bool
#include <stdint.h> // int64_t
#include <unistd.h> // sleep
#include <string.h>
#include <pthread.h>
#include "timer.h"

#define _POSIX_C_SOURCE 199309L // timespec, net_timer_t
#define NS_PER_UPDATE 16000000 // 16ms, 64 ticks/sec

// global variables (debug)
volatile bool server_on;
volatile int cmd;

/******************************************************************************/
/*                                  server                                    */
/******************************************************************************/

// server.h
void server_boot(void);
void server_shutdown(void);
void *server_run(void*); //
void server_update(int64_t*);
void server_worker(void (*f)(char*), char *msg);

// server.c
void server_boot(void)
{
    fprintf(stderr, "Server: Boot\n");
}

void server_shutdown(void)
{
    fprintf(stderr, "Server: Shutdown\n");
}

void *server_run(void *ptr)
{
    fprintf(stderr, "Server: Run\n");

    net_timer_t now;
    int64_t prev_tick = 0;
    int64_t lag = 0;
    int64_t ticker = 0;
    int64_t lag_avg = 0;
    int64_t total_tick = 1;

    server_boot();
    timer_reset(&now);
    while (server_on) {
        int64_t curr_time = timer_ns(&now);
        int64_t elapsed = curr_time - prev_tick;
        prev_tick = curr_time;
        lag += elapsed;

        while (lag >= NS_PER_UPDATE) {
            ticker += lag;
            lag_avg = (ticker/total_tick);
            total_tick++;
            fprintf(stderr, "Server: Average %ldns\n", lag_avg);
            fprintf(stderr, "Server: Clock: %ldns\n", curr_time);
            fprintf(stderr, "Server: Latency: %ldns\n", lag);
            server_update(&lag);
            lag -= NS_PER_UPDATE;
       	}
    }
    server_shutdown();

    return NULL;
}

void server_update(int64_t *lag)
{
    fprintf(stderr, "Server: Update\n");

    if (cmd == -1) {
        fprintf(stderr, "Server: Shutdown\n");
        server_on = false;
    }
    else if (cmd == 0) {
        fprintf(stderr, "Server: Waiting\n");
    }
    else if (cmd == 1) {
        fprintf(stderr, "Server: Status\n");
    }
    else if (cmd == 2) {
        fprintf(stderr, "Server: Input\n");
    }
    else if (cmd == 3) {
        fprintf(stderr, "Server: Lag switch\n");
        *lag += 32000000; // increase lag to 32ms
    }
    else if (cmd == 4) {
        fprintf(stderr, "Server: Lag reset\n");
        *lag = 16000000; // reset to perfect latency
    }

    cmd = 0;
}

void server_worker(pthread_t &t, void (*f)(char*), char *msg)
{
    err = pthread_create(t, NULL, (*f), msg);
    if (err != 0) {
    	fprintf(stderr, "Error: Unable to create server_thread - %s\n", strerror(err));
    	return 1;
    }

    client_run();

    if (pthread_join(*t, NULL)) {
        fprintf(stderr, "Error: Unable to join server_thread\n");
    }
}

void server_log(char *msg)
{
    printf("Server: %s\n", msg);
}

/******************************************************************************/
/*                                  client                                    */
/******************************************************************************/

// client.h
void client_boot(void);
void client_shutdown(void);
void client_run(void);
void client_update(void);

// client.c
void client_boot(void)
{
    fprintf(stderr, "Client: Boot\n");
}

void client_shutdown(void)
{
    fprintf(stderr, "Client: Shutdown\n");
}

void client_run(void)
{
    fprintf(stderr, "Client: Run\n");
    
    client_boot();
    while (1) {
        printf("Input: ");
        scanf("%d", &cmd);
	client_update();
    }
    client_shutdown();
}

void client_update(void)
{
    fprintf(stderr, "Client: Update\n");
}

/******************************************************************************/
/*                                   main                                     */
/******************************************************************************/

int main(int argc, char *argv[])
{
    int err;
    pthread_t server_thread, worker_thread;
    server_on = true;

    server_worker(&worker_thread, &server_log, "hi");

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
