#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <time.h>

typedef struct timespec my_timer_t;

void timer_reset(my_timer_t *timer);
int64_t timer_ns(my_timer_t *timer);

#endif
