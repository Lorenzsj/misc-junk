#ifndef SERVER_H
#define SERVER_H

#define MAX_LINE 256

#include "worker.h"

void server_run(void);
void server_branch(worker_t*);
void server_merge(worker_t*);
void server_shell(worker_t*);

#endif // SERVER_H
