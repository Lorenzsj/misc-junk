#ifndef SERVER_H
#define SERVER_Hh

#include <stdint.h> // int64_t

void server_boot(void);
void server_shutdown(void);
void *server_run(void*);
void server_update(int64_t*);

#endif // SERVER_H