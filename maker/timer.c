#include <stdio.h>
#include "timer.h"

void timer_reset(net_timer_t *timer) {
  clock_gettime(CLOCK_MONOTONIC, timer);
}

int64_t timer_ns(net_timer_t *timer) {
  net_timer_t end;
  timer_reset(&end);

  return
    (end.tv_sec - timer->tv_sec) * 1000000000 +
    (end.tv_nsec - timer->tv_nsec);
}
