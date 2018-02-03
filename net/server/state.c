#include "state.h"

state_t state_new(void)
{
    state_t state;
    
    state.alive = false;
    state.status = 0;

    return state;
}