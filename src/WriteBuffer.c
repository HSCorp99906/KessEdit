#include "../include/WriteBuffer.h"


void wb_init(struct WriteBuffer* wb) {
	wb -> size = 30;
	wb -> lines = (char**)malloc(sizeof(char*) * wb -> size);
	wb -> stringpos = 0;
	wb -> charpos = 0;
}


void wb_pushc(struct WriteBuffer* wb, char c) {
	if (wb -> stringpos >= wb -> size - 3) {
		wb -> size += 15;
		wb -> lines = (char**)realloc(wb -> lines, sizeof(char*) * wb -> size);
	}

	wb -> lines[wb -> stringpos][wb -> charpos] = c;
	++wb -> charpos;
}


void wb_pushl(struct WriteBuffer* wb, const char* restrict line) { }
