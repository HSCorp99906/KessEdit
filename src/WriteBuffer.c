#include "../include/WriteBuffer.h"


void wb_init(struct WriteBuffer* wb) {
	wb -> size = 1;
	wb -> cells = (struct WbCell*)calloc(wb -> size, sizeof(struct WbCell));

	for (int i = 0; i < wb -> size; ++i) {
		wb -> cells[i].line = (char*)calloc(5, sizeof(char));
		wb -> cells[i].strsize = 5;
		wb -> cells[i].pos = 0;
	}
}


void wb_destroy(struct WriteBuffer* wb) {
	for (int i = 0; i < wb -> size; ++i) {
		free(wb -> cells[i].line);
	}

	free(wb -> cells);
	wb -> cells = NULL;
}


void wb_pushc(struct WriteBuffer* wb, unsigned long cellidx, char c) {
	if (wb -> cells[cellidx].pos >= wb -> cells[cellidx].strsize - 3) {
		wb -> cells[cellidx].strsize += 10;
		wb -> cells[cellidx].line = (char*)realloc(wb -> cells[cellidx].line,
			sizeof(char) * wb -> cells[cellidx].strsize);
	}

	wb -> cells[cellidx].line[wb -> cells[cellidx].pos] = c;
	++wb -> cells[cellidx].pos;
}


char* wb_fetchline(struct WriteBuffer wb, unsigned long cellidx) {
	if (wb.cells == NULL) {
		return NULL;
	}

	return wb.cells[cellidx].line;
}


void wb_create_newline(struct WriteBuffer* wb) {
	++wb -> size;
	wb -> cells = (struct WbCell*)realloc(wb -> cells, sizeof(struct WbCell) * wb -> size);
	wb -> cells[wb -> size - 1].line = (char*)calloc(5, sizeof(char));
}


void wb_destroy_last_line(struct WriteBuffer* wb) {
	free(wb -> cells[wb -> size - 1].line);
	--wb -> size;
	wb -> cells = (struct WbCell*)realloc(wb -> cells, sizeof(struct WbCell) * wb -> size);
}


void wb_popc(struct WriteBuffer* wb, unsigned long cellidx) {
	wb -> cells[cellidx].line[wb -> cells[cellidx].strsize - 1] = ' ';
	--wb -> cells[cellidx].strsize;
	wb -> cells[cellidx].line = (char*)realloc(wb -> cells[cellidx].line, 
		sizeof(char) * wb -> cells[cellidx].strsize);
}


void wb_clear_buffer(struct WriteBuffer* wb) {
	for (int i = 0; i < wb -> size; ++i) {
		free(wb -> cells[i].line);
	}

	wb -> size = 1;
	wb -> cells = (struct WbCell*)realloc(wb -> cells, sizeof(struct WbCell));
	memset((*wb -> cells).line, ' ', (*wb -> cells).strsize);
}
