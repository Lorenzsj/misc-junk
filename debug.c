#include <stdio.h>

typedef void *(*op_t)(void*);

typedef struct {
    op_t op;
} worker_t;

worker_t worker_new(op_t);

void *debug_op(void *arg)
{
	printf("Do nothing!\n");
	
	return NULL;
}

worker_t worker_new(op_t op)
{
	worker_t worker;
	worker.op = op;
	return worker;
}

int main(void)
{
	worker_t w;
	
	w = worker_new(debug_op);

	w.op(NULL);
	
	return 0;
}
