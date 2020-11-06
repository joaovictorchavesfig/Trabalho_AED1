#ifndef _MAIN_H_
#define _MAIN_H_

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

void append(pont* head_ref, int new_x,int new_y);
void add_fruit(BITMAP* buffer,int x,int y);
int eat_fruit(int* fruit_x,int* fruit_y,int x,int y);

int eat_fruit(int* fruit_x,int* fruit_y,int x,int y)
{
	if((*fruit_x+10>=x && *fruit_x<=x+20) && (*fruit_y+10>=y && *fruit_y<=y+20))
	{
		*fruit_x = rand()%820;
		*fruit_y = 20 + rand()%570;
		return 1;
	}
	return 0;
	
}

void add_fruit(BITMAP* buffer,int x,int y)
{
	rectfill(buffer, x, y, x + 10, y + 10, makecol(255, 0, 0));
}

void append(pont* head_ref, int new_x,int new_y) 
{ 
    //alocar novo elemento
    pont new_node = (pont) malloc(sizeof(list)); 
  
    pont last = *head_ref;
   
    new_node->x  = new_x;
	new_node->y  = new_y;
	
	new_node->prox = NULL; 
  
	// Se a lista esta vazia
	if (*head_ref == NULL) 
	{ 
       *head_ref = new_node; 
       return; 
    }   
       
	// Checa ate último elemento
    while (last->prox != NULL) 
        last = last->prox;
   
    // Muda novo elemento para último da lista
    last->prox = new_node; 
    return;     
} 

#endif
