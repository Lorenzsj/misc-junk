#include "status.h"

status_t status_new(void)
{
    status_t status;

    status.active = 0;

    return status;
}