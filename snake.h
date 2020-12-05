#ifndef _MAIN_H_
#define _MAIN_H_
#define MAP_WIDTH 840
#define MAP_HEIGHT 600

#include <allegro.h>
#include <stdlib.h>
#include <time.h>
//struct de lista ligada encadeada para corpo da cobra
struct list{
	int x;
	int y;
	struct list* prox;
};
typedef struct list list;
typedef struct list* pont;

BITMAP *buffer = NULL;
int pontos;
const int tamanho = 20;
int matrix[MAP_WIDTH][MAP_HEIGHT];
int dirX;
int dirY;

void add_fruit(BITMAP* buffer,int x,int y);
int eat_fruit(int* fruit_x,int* fruit_y,int x,int y,pont head);
void move_body(pont body,int x,int y);
void gameover(pont head,int* fruit_x,int* fruit_y);

//função para encerrar o jogo
void gameover(pont head,int* fruit_x,int* fruit_y){
   struct list* tmp;
   while (head != NULL)
    {
       tmp = head;
       head = head->prox;
       free(tmp);
    }
    free(fruit_x);
    free(fruit_y);
	do{
	clear(buffer);
	textprintf_ex(buffer, font, SCREEN_W/2-50, SCREEN_H/2-20, makecol(255, 0, 0), -1, "GAME OVER");
	textprintf_ex(buffer, font, SCREEN_W/2-50, (SCREEN_H/2), makecol(255, 0, 0), -1, "Pontos: %d",pontos);
	textprintf_ex(buffer, font, SCREEN_W/2-100, (SCREEN_H/2)+20, makecol(255, 0, 0), -1, "Pressione esc para sair");
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}while(!(key[KEY_ESC]));
	exit(0);
}

//função para ajustar movimento da cobra recursivamente
void move_body(pont body,int x,int y){
	if(body->prox==NULL) //ponto de parada da recursividade
	{
		matrix[body->x][body->y] = 0; //apaga último pedaço da cobra da matrix
	}
	else
	{
		move_body(body->prox,body->x,body->y);
	}
	body->x = x;
	body->y = y;
}
//função para checar se a posição atual da cobra bate com a da fruta
int eat_fruit(int* fruit_x,int* fruit_y,int x,int y,pont head)
{
	if((*fruit_x+10>=x && *fruit_x<=x+20) && (*fruit_y+10>=y && *fruit_y<=y+20))
	{
		pont temp = head;
		while(temp->prox!=NULL)
		{
			temp = temp->prox;	
		}
		int newNodex = temp->x;
		int newNodey = temp->y;
		list* newNode = (list*) malloc(sizeof(list)); //adiciona novo pedaço de corpo a cobra
		newNode->x = newNodex;
		newNode->y = newNodey;
		newNode->prox = NULL;
		temp->prox = newNode;
		*fruit_x = rand()%820;
		*fruit_y = 20 + rand()%570;
		return 1;
	}
	return 0;
	
}
//desenha a fruta na tela
void add_fruit(BITMAP* buffer,int x,int y)
{
	rectfill(buffer, x, y, x + 10, y + 10, makecol(255, 0, 0));
}

#endif
