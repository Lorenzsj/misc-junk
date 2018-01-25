#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool
#include <pthread.h>
#include <time.h>
#include <unistd.h> // sleep

volatile bool server_on;
volatile int cmd;

void* server_run(void*);
void server_tick(unsigned int*);
void server_process(void);

void*
server_run(void* ptr)
{
    time_t clock = time(NULL);
    unsigned int prev_tick = 0; 

    while(server_on){
        server_tick(&prev_tick);
        server_process();
    }

    return NULL;
}


void 
server_tick(unsigned int* prev)
{
    *prev += 1;
    printf("Tick: %u\n", *previous);
    sleep(1);
}

void 
server_process(void)
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

    pthread_t server_thread;
    server_on = true;

    if(pthread_create(&server_thread, NULL, server_run, NULL)){
    	fprintf(stderr, "Error: Unable to create server_thread\n");
    	return 1;
    }

    client_run();
    

    if(pthread_join(server_thread, NULL)){
        fprintf(stderr, "Error: Unable to join server_thread\n");
    }
    
    return 0;
}
