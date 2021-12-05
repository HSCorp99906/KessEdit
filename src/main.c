#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>     
#include <string.h>
#include <stdbool.h>


struct Pos {
	unsigned int curRow;
	unsigned int curCol;
	unsigned int lastRow;
};


void write_from_file(WINDOW* restrict win, const char* restrict filename) {
	FILE* fp = fopen(filename, "r");

	size_t lineBufSize = 5;
	char* lineBuf = (char*)malloc(sizeof(char) * lineBufSize);
	size_t filesize = 0;

	while (getline(&lineBuf, &lineBufSize, fp) != -1) {
		++filesize;
		wprintw(win, "~%d  %s", filesize, lineBuf);
	}

	wscrl(win, filesize - 20);

	free(lineBuf);
	fclose(fp);
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

	unsigned int curCol = 5;
	unsigned int curRow = 1;
	unsigned int lastRow = 0;

	while (!(quit)) {
		if (curRow == lastRow + 1) {
			mvwprintw(win, curRow, curCol - 4, "~%d ", curRow);
			++lastRow;
		}

		curChar = wgetch(win);

		switch ((int)curChar) {
			case 127:
				if (curCol > 5) {
					--curCol;
					mvwprintw(win, curRow, curCol, "     ");
					continue;
				} else {
					continue;
				}
		}

		switch (curChar) {
			case '`':
				quit = true;
				break;	
			default:
				mvwprintw(win, curRow, curCol, &curChar);
				++curCol;
				break;
		}
	}

	endwin();
	delwin(win);
}
