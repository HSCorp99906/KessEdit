#ifndef WRITE_BUFFER_H
#define WRITE_BUFFER_H

#include <stdlib.h>


struct WriteBuffer {
	size_t size;
	char** lines;
	unsigned long pos;
};


void wb_init(struct WriteBuffer* wb);
void wb_pushc(struct WriteBuffer* wb);
void wb_pushl(struct WriteBuffer* wb);
void wb_popc(struct WriteBuffer* wb);


#endif
