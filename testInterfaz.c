#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 
#include <string.h>

pthread_mutex_t lockParaDibujar;

struct Personaje
{
	int id;
	int xPosition;
	int yPosition;
	char c;
};

struct Personaje  * player1;

void * manejadorDeInterfaz(void * vargs){
	void * salida;
	char * ip = (char *) vargs;
	initscr();
	curs_set(0);
	printw("%s", ip);
	refresh();
	
		
	pthread_exit( salida ); 
}

void * imprimir(void * vargs){
	/*for(int i = 0; i < 100054; i++){
		printw("%d", i);
	}*/
	
	void * salida;
	noecho();
	int c = getch();
	switch(c){
		case 'w':
		case 'W':
			//CHecamos colisiones
			//Gurdamos las nuevas coordenadas
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(player1->xPosition, player1->yPosition, ' ');	
			player1->xPosition = player1->xPosition - 1;
			mvaddch(player1->xPosition, player1->yPosition, player1->c);
			pthread_mutex_unlock(&lockParaDibujar);
			break;
		case 'a':
		case 'A':
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(player1->xPosition, player1->yPosition, ' ');	
			player1->yPosition = player1->yPosition - 1;
			mvaddch(player1->xPosition, player1->yPosition, player1->c);
			pthread_mutex_unlock(&lockParaDibujar);
			break;
		case 's':
		case 'S':
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(player1->xPosition, player1->yPosition, ' ');	
			player1->xPosition = player1->xPosition + 1;
			mvaddch(player1->xPosition, player1->yPosition, player1->c);
			pthread_mutex_unlock(&lockParaDibujar);
			break;
		case 'D':
		case 'd':
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(player1->xPosition, player1->yPosition, ' ');	
			player1->yPosition = player1->yPosition + 1;
			mvaddch(player1->xPosition, player1->yPosition, player1->c);
			pthread_mutex_unlock(&lockParaDibujar);
			break;
		default:
			break;
	}
	refresh();
	
	pthread_exit( salida ); 
			
}

void * imprimirNumeros(void * vargs){
	void * salida;
	
	char map[20][50] = {
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','#','#','#','#','#','#','#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','n','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
	};
	for(int i = 0; i < 20; i++){
		for(int j = 0; j<50; j++){
			if(map[i][j] == '#'){
				mvaddch(i, j, '#');
			}
		
		}
		
		refresh();
	}
	
	mvaddch(player1->xPosition, player1->yPosition, player1->c);
	refresh();
	pthread_exit( salida ); 
}

int main(){
	//Vargs las ips
	if(pthread_mutex_init(&lockParaDibujar, NULL) != 0){
		printf("Fallo el mutex");
		return -1;
	}
	
	void * salida_funcion;
	char * ip;
	ip = (char *) malloc(20);
	strcpy(ip, "192.168.0.1");

	player1 = malloc(sizeof(struct Personaje));
	player1->id = 1;
	player1->xPosition = 2;
	player1->yPosition = 2;
	player1->c = 'T';
	

	
	pthread_t hiloUno_id;
	pthread_create(&hiloUno_id, NULL, manejadorDeInterfaz, ip);
	pthread_join(hiloUno_id, &salida_funcion);
	
	pthread_t hiloDos_id;
	pthread_t hiloTres_id;
	
	
	pthread_create(&hiloTres_id, NULL, imprimirNumeros, NULL);
	while(1){
		pthread_create(&hiloDos_id, NULL, imprimir, NULL);
		pthread_join(hiloDos_id, &salida_funcion);
	}
	pthread_join(hiloTres_id, &salida_funcion);
	
	
	getch();
	endwin();
	exit(0);
}
