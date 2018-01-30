#include <stdio.h> // printf, fprintf
#include <stdlib.h>
#include <stdbool.h> // bool
#include <stdint.h> // int64_t
#include <unistd.h> // sleep
#include <string.h>
#include <pthread.h>
#include "timer.h"
#include "server.h"
#include "aux.h"

#define _POSIX_C_SOURCE 199309L // timespec, net_timer_t
#define NS_PER_UPDATE 16000000 // 16ms, 64 ticks/sec

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