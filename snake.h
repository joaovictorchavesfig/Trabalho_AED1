#ifndef TRABFINAL_H_INCLUDED
#define TRABFINAL_H_INCLUDED

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define FRUIT 'o'
#define SNAKE ' '
#define BORDAH '|'
#define BORDAV '_'

#define SNAKE_PAIR 1

void draw_board();

void draw_board(){
	
	int x,y,maxdim;
	
	//Lado esquerdo
	for(y=4;y<LINES-2;y++)
	{
		mvhline(y, 3, BORDAH, 1);
	}
	//Lado de baixo
	for(x=4;x<COLS-6;x++)
	{
		mvvline(LINES-3, x, BORDAV, 1);
	}
	//Lado direito
	for(y=4;y<LINES-2;y++)
	{
		mvhline(y, COLS-6, BORDAH, 1);
	}
	//Lado de cima
	for(x=4;x<COLS-6;x++)
	{
		mvvline(3, x, BORDAV, 1);
	}
	//Contagem de pontos
	move(2,(COLS/2)-5);
	printw("SCORE:");
}

#endif
