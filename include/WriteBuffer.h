#ifndef WRITE_BUFFER_H
#define WRITE_BUFFER_H

#include <stdlib.h>


struct WriteBuffer {
	size_t size;
	char** lines;
	unsigned long stringpos;  // Pos for string.
	unsigned long charpos;  // Pos for char of each string.
};


void wb_init(struct WriteBuffer* wb);
void wb_pushc(struct WriteBuffer* wb, char c);
void wb_pushl(struct WriteBuffer* wb, const char* restrict line);
void wb_popc(struct WriteBuffer* wb);


#endif
