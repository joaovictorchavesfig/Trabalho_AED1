#include "snake.h"

int main()
{

    // inicializa contagem do tempo
    srand(time(NULL));
    
    // inicializa a cobra e sua posição
    pont head =(list*) malloc(sizeof(list));
    head->prox = NULL;
    head->x = 1;
    head->y = 1;
    
    dirX = 0;
    dirY = 0;
    
    // inicializa a primeira fruta
    int *fruit_x;
    int *fruit_y;
    int i,j;
    fruit_x = (int*)malloc(sizeof(int));
    fruit_y = (int*)malloc(sizeof(int));
 	*fruit_x = rand()%820;
	*fruit_y = rand()%580;
	
	// cria pontuação
	pontos = 0;

    // inicializa a biblioteca
    allegro_init();

    // profundidade de cores
    set_color_depth(32);

    // permite a leitura do teclado
    install_keyboard();

    // cria a janela com a largura 840 e altura 600 pixels
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, MAP_WIDTH, MAP_HEIGHT, 0, 0);

    // Criando BUFFER, ela é um ponteiro para um BITMAP
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    
    for(i=0;i<MAP_WIDTH;i++)
	{
		for(j=0;j<MAP_HEIGHT;j++)
		{
			matrix[i][j] = 0;
		}
	}
    
    // Laço principal
    while(1) // o programa deve rodar enquanto não pressionar a tecla ESC
    {
		// verifica colisão da fruta com a cobra
    	pontos = pontos + eat_fruit(fruit_x,fruit_y,head->x,head->y,head);
		move_body(head,head->x,head->y);
    	
        if(dirY!=1 && (key[KEY_UP] || key[KEY_W])) // se pressionou para cima
        {
            dirY = -1;
			dirX = 0; // move a cobra para cima
        }
        if(dirY!=-1 && (key[KEY_DOWN] || key[KEY_S])) // se pressionou para baixo
        {
            dirY = 1; 
			dirX = 0;// move a cobra para baixo
        }
    	if (dirX!=1 && (key[KEY_LEFT] || key[KEY_A])) // se pressionou para esquerda
        {
            dirX = -1;
			dirY = 0; // move a cobra para a esquerda
        }
    	if (dirX!=-1 && (key[KEY_RIGHT] || key[KEY_D])) // se pressionou para direita
        {
            dirX = 1;
			dirY = 0; // move a cobra para a direita
        }
		if (key[KEY_ESC]) // termina o jogo
		{
			return 0;
		}
		// verifica se a cobra saiu da tela e a faz retornar do lado oposto
		if(head->x>830)
		{
			head->x = 1;
			matrix[head->x][head->y] = 1;
		}
		else if(head->x<1)
		{
			head->x = 820;
			matrix[head->x][head->y] = 1;
		}
		else if(head->y>590)
		{
			head->y = 1;
			matrix[head->x][head->y] = 1;
		}
		else if(head->y<1)
		{
			head->y = 580;
			matrix[head->x][head->y] = 1;
		}
		else
		{
			head->x = head->x+dirX*tamanho;
	    	head->y = head->y+dirY*tamanho;
	    	if(matrix[head->x][head->y]==1)
			{
				gameover();
			}
	    	matrix[head->x][head->y] = 1;
		}
        // limpa o buffer para um novo desenho (pinta tudo de preto)
        clear(buffer);
        
        // adiciona uma fruta ao jogo
		add_fruit(buffer,*fruit_x,*fruit_y);
		
        // pinta o quadrado no buffer
        for(i=0;i<SCREEN_W;i++)
		{
			for(j=0;j<SCREEN_H;j++)
			{
				if(matrix[i][j]==1)
				{
					rectfill(buffer, i, j, i + tamanho, j + tamanho, makecol(220, 220, 220));
				}
			}
		}
		rectfill(buffer, head->x, head->y, head->x + tamanho, head->y + tamanho, makecol(220, 220, 220));
        // imprimimos as coordenadas x e y no buffer para o usuário ver na tela
        textprintf_ex(buffer, font, 370, 10, makecol(255, 0, 0), -1, "Pontos: %d", pontos);

        // imprime o buffer na tela
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // essa função faz o allegro esperar um pouco antes de voltar para o while
        rest(50);
    }

    allegro_exit();
    return 0;
}
END_OF_MAIN();
