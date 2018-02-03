#ifndef STATE_H
#define STATE_H

#include <stdbool.h>

typedef struct {
    volatile bool alive;
    volatile int status;
} state_t;

state_t state_new(void);

#endif // STATE_H

