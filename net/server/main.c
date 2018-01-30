#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void *test(void* ptr)
{
    printf("hey\n");

    return NULL;
}

int main(void)
{
    server_run();

    return 0;
}
