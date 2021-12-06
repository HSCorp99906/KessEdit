#ifndef WRITE_BUFFER_H
#define WRITE_BUFFER_H

#include <stdlib.h>
#include <string.h>

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
void wb_popc(struct WriteBuffer* wb, unsigned long cellidx);
char* wb_fetchline(struct WriteBuffer wb, unsigned long cellidx);
void wb_create_newline(struct WriteBuffer* wb);
void wb_destroy_last_line(struct WriteBuffer* wb);
void wb_clear_buffer(struct WriteBuffer* wb);

#endif
