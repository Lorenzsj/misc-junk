#ifndef STATUS_H
#define STATUS_H

typedef struct {
    volatile int active;
} status_t;

status_t status_new(void);

#endif // STATUS_H

