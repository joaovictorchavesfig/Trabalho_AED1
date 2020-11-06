#include "snake.h"

int main()
{
    // BUFFER, serve para não desenhar-mos diretamente na tela e assim
    // evitando o efeito de pisca-pisca
    BITMAP *buffer = NULL;

    // inicializa contagem do tempo
    srand(time(NULL));
    
    // inicializa a posição da cobra
    pont head = NULL;
    append(&head,0,0);
    
    int dirX = 0;
    int dirY = 0;
    
    // inicializa a primeira fruta
    int *fruit_x;
    int *fruit_y;
    fruit_x = (int*)malloc(sizeof(int));
    fruit_y = (int*)malloc(sizeof(int));
 	*fruit_x = rand()%820;
	*fruit_y = rand()%580;
	
	// cria pontuação
	int pontos = 0;

    // dimensao da cabeça da cobra
    const int tamanho = 20;

    // inicializa a biblioteca
    allegro_init();

    // profundidade de cores
    set_color_depth(32);

    // permite a leitura do teclado
    install_keyboard();

    // cria a janela com a largura 840 e altura 600 pixels
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 840, 600, 0, 0);

    // Criando BUFFER, ela é um ponteiro para um BITMAP
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    
    // Laço principal
    while(1) // o programa deve rodar enquanto não pressionar a tecla ESC
    {
    	
        if(key[KEY_UP] || key[KEY_W]) // se pressionou para cima
        {
            dirY = -1;
			dirX = 0; // move a cobra para cima
        }
        if(key[KEY_DOWN] || key[KEY_S]) // se pressionou para baixo
        {
            dirY = 1; 
			dirX = 0;// move a cobra para baixo
        }
    	if (key[KEY_LEFT] || key[KEY_A]) // se pressionou para esquerda
        {
            dirX = -1;
			dirY = 0; // move a cobra para a esquerda
        }
    	if (key[KEY_RIGHT] || key[KEY_D]) // se pressionou para direita
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
			head->x = 0;
		}
		else if(head->x<0)
		{
			head->x = 820;
		}
		else if(head->y>590)
		{
			head->y = 0;
		}
		else if(head->y<0)
		{
			head->y = 580;
		}
		else
		{
			head->x = head->x+dirX*tamanho;
	    	head->y = head->y+dirY*tamanho;
		}
        // limpa o buffer para um novo desenho (pinta tudo de preto)
        clear(buffer);

        // pinta o quadrado no buffer
        rectfill(buffer, head->x, head->y, head->x + tamanho, head->y + tamanho, makecol(220, 220, 220));
		
		// verifica colisão da fruta com a cobra
		pontos = pontos + eat_fruit(fruit_x,fruit_y,head->x,head->y);
		
		// adiciona uma fruta ao jogo
		add_fruit(buffer,*fruit_x,*fruit_y);
		
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
