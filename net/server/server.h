#ifndef SERVER_H
#define SERVER_H

#define MAX_LINE 256

#include "worker.h"

// types
typedef struct {
} server_t;

void server_run(void);
void server_branch(size_t);
void server_merge(void);
void server_shell(void);

#endif // SERVER_H
