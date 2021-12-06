#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>     
#include <string.h>
#include <stdbool.h>
#include "../include/WriteBuffer.h"


void write_from_file(WINDOW* restrict win, const char* restrict filename) {
	FILE* fp = fopen(filename, "r");

	size_t lineBufSize = 5;
	char* lineBuf = (char*)malloc(sizeof(char) * lineBufSize);
	size_t filesize = 0;

	while (getline(&lineBuf, &lineBufSize, fp) != -1) {
		++filesize;
		mvwprintw(win, filesize, 0, "~%d  %s", filesize, lineBuf);
	}
	
	if (filesize > 50) {
		wscrl(win, filesize - 20);
	}

	free(lineBuf);
	fclose(fp);
}


void set_cursor(WINDOW* restrict win, unsigned long curRow, unsigned long curCol) {
	wattron(win, A_STANDOUT);
	mvwprintw(win, curRow, curCol + 1, " ");
	wattroff(win, A_STANDOUT);
}


int main(int argc, const char* restrict argv[]) {
	if (argc < 2) {
		printf("Usage %s <filename>\n", argv[0]);
		return 0;
	}
	initscr();
	noecho();
	curs_set(0);

	WINDOW* win = newwin(1000, 1000, 0, 0);
	// box(win, 0, 0);
	scrollok(win, TRUE);

	if (access(argv[1], F_OK) != 0) {
		char cmdBuf[350];

		if (strlen(cmdBuf) + 6 >= 350) {
			printf("Filename too long!\n");
			endwin();
			delwin(win);
			return 0;
		}

		sprintf(cmdBuf, "touch %s", argv[1]);	
		system(cmdBuf);
	}

	write_from_file(win, argv[1]);

	bool quit = false;
	char curChar;

	// Positions.
	unsigned int curCol = 5;
	unsigned int lastCol = 4;
	unsigned long curRow = 1;
	unsigned long lastRow = 0;

	struct WriteBuffer writeBuf;
	wb_init(&writeBuf);

	/*
	* Write buffer is used for storing
	* the stores in memory, the contents 
	* of what the person has been writing until
	* they are ready to write the changes
	* to the file they are writing to.
	*/
	
	// For our fake cursor.
	bool highlight = true;

	while (!(quit)) {
		if (highlight) {
			highlight = false;
			set_cursor(win, curRow, curCol - 1);
		}

		if (curRow == lastRow + 1) {
			mvwprintw(win, curRow, curCol - 4, "~%d ", curRow);
			++lastRow;
		}

		curChar = wgetch(win);

		switch ((int)curChar) {
			case 127:
				if (curCol > 5) {
					mvwprintw(win, curRow, curCol, "    ");
					--curCol;
					mvwprintw(win, curRow, curCol, " ");
					set_cursor(win, curRow, curCol);
					continue;
				} else {
					if (curRow > 1) {
						mvwprintw(win, curRow, 0, "          ");
						mvwprintw(win, curRow, 0, "   ");
						curCol = lastCol;
						--lastRow;
						--curRow;
					}

					continue;
				}
			case 10:
				wb_create_newline(&writeBuf);  // Adds a new cell to our buffer.
				wb_pushc(&writeBuf, curRow - 1, '\n');  // Adds a new line char to the previous cell.
				lastCol = curCol;  // Sets last column.
				curCol = 5;
				++curRow;
				continue;
		}

		switch (curChar) {
			case '`':
				quit = true;
				break;	
			default:
				mvwprintw(win, curRow, curCol, "      ");
				wb_pushc(&writeBuf, curRow - 1, curChar);
				mvwprintw(win, curRow, curCol, &curChar);
				++curCol;
				set_cursor(win, curRow, curCol - 1);
				break;
		}
	}

	FILE* writefile = fopen(argv[1], "a");

	for (int i = 0; i < writeBuf.size; ++i) {
		fputs(wb_fetchline(writeBuf, i), writefile);
	}

	fclose(writefile);

	endwin();
	wb_destroy(&writeBuf);
	delwin(win);
}
