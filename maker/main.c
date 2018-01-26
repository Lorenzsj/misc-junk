#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <unistd.h> // sleep
#include <stdint.h>
#include "timer.h"

#define _POSIX_C_SOURCE 199309L
#define NS_PER_UPDATE 256000000 // 16ms, 64 ticks

volatile bool server_on;
volatile int cmd;
volatile int64_t lag = 0;

void* server_run(void*);
void server_tick(double*);
void server_update(void);

void*
server_run(void* ptr)
{
    my_timer_t now;
    timer_reset(&now);
    
    int64_t prev_tick = 0;
    int64_t curr_time = 0;
    // int64_t lag = 0;
    
    while(server_on){ 
        curr_time = timer_ns(&now);
        int64_t elapsed = curr_time - prev_tick;
        prev_tick = curr_time;
        lag += elapsed;

        while(lag >= NS_PER_UPDATE){
            fprintf(stderr, "Server: Current = %ld\n", curr_time);
            fprintf(stderr, "Server: Latency = %ld\n", lag);
            server_update(); 
            lag -= NS_PER_UPDATE;
        }
        // render();
    }

    return NULL;
}


void 
server_tick(double* prev)
{
    *prev += 1;
    printf("Tick: %f\n", *prev);
    sleep(1);
}

void 
server_update(void)
{
    if(cmd == -1){
        fprintf(stderr, "Server: Shutdown\n");
        server_on = false;
    }
    else if(cmd == 0){
        fprintf(stderr, "Server: Waiting\n");
    }
    else if(cmd == 1){
        fprintf(stderr, "Server: Status\n");
    }
    else if(cmd == 2){
        fprintf(stderr, "Server: Input\n");
    }
    else if(cmd == 3){
        fprintf(stderr, "Server: Lag switch\n");
        lag += 512000000;
    }
    else if(cmd == 4){
        fprintf(stderr, "Server: Lag reset\n");
        lag = 0;
    }

    // reset cmd
    cmd = 0;
}

//////////////////////////////////////////////////////////////

void
client_run()
{
    while(1){
        printf("Input: ");
        scanf("%d", &cmd);
    }
}

int
main(int argc, char* argv[])
{
    int err; 
    pthread_t server_thread;
    server_on = true;

    err = pthread_create(&server_thread, NULL, server_run, NULL);
    if(err != 0){
    	fprintf(stderr, "Error: Unable to create server_thread - %s\n", 
                strerror(err));
    	return 1;
    }

    client_run();

    if(pthread_join(server_thread, NULL)){
        fprintf(stderr, "Error: Unable to join server_thread\n");
    }
    
    return 0;
}
