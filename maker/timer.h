#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <time.h>

typedef struct timespec net_timer_t;

void timer_reset(net_timer_t *timer);
int64_t timer_ns(net_timer_t *timer);

#endif // TIMER_H
