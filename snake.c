#include "snake.h"
#include <ncurses.h>
#include <time.h>

int main(){
	
	int ch;
	
	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	
	start_color();
	init_pair(SNAKE_PAIR, COLOR_WHITE, COLOR_BLACK);
	clear();
	
	draw_board();
	
	ch = getch();
	
	endwin();

	exit(0);
}
