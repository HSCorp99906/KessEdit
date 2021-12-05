#ifndef WRITE_BUFFER_H
#define WRITE_BUFFER_H

#include <stdlib.h>

struct WbCell {
	unsigned long pos;
	size_t strsize;
	char* line;
};


struct WriteBuffer {
	size_t size;
	struct WbCell* cells;
};


void wb_init(struct WriteBuffer* wb);
void wb_destroy(struct WriteBuffer* wb);
void wb_pushc(struct WriteBuffer* wb, unsigned long cellidx, char c);

#endif
