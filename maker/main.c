#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <unistd.h> // sleep

#define MS_PER_UPDATE 1600

volatile bool server_on;
volatile int cmd;

void* server_run(void*);
void server_tick(double*);
void server_update(void);

void*
server_run(void* ptr)
{
    double prev_tick = 1;
    double lag = 0.0;
    double curr_time = 0;
    
    while(server_on){ 
        curr_time += 0.00001;
        double elapsed = curr_time - prev_tick;
        prev_tick = curr_time;
        lag += elapsed;

        while(lag >= MS_PER_UPDATE){
            server_update(); 
            lag -= MS_PER_UPDATE;
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
