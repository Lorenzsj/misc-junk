#include <stdio.h>
#include "client.h"
#include "aux.h"

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
    cmd = 0;

    while (cmd != -1) {
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