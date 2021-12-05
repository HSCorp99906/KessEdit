#include "../include/WriteBuffer.h"


void wb_init(struct WriteBuffer* wb) {
	wb -> size = 30;
	wb -> lines = (char**)malloc(sizeof(char*) * wb -> size);
	wb -> pos = 0;
}



