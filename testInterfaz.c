#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 
#include <string.h>

void * manejadorDeInterfaz(void * vargs){
	void * salida;
	char * ip = (char *) vargs;
	initscr();
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
			printw("%s", "Doble U\n");
			break;
		case 'a':
		case 'A':
			printw("%s", "Gatit(a)\n");
			break;
		case 's':
		case 'S':
			printw("%s", "(S)anchoPanza\n");
			break;
		case 'D':
		case 'd':
			printw("%s", "(D)IU\n");
			break;
		default:
			printw("%s", "Nada\n");
			break;
	}
	refresh();
	
	pthread_exit( salida ); 
			
}

void * imprimirNumeros(void * vargs){
	void * salida;
	for(int i = 0; i < 1000; i++){
		printw("%d", i);
		refresh();
		sleep(1);
	}
	pthread_exit( salida ); 
}
int main(){
	void * salida_funcion;
	char * ip;
	ip = (char *) malloc(20);
	strcpy(ip, "192.168.0.1");

	
	pthread_t hiloUno_id;
	pthread_create(&hiloUno_id, NULL, manejadorDeInterfaz, ip);
	pthread_join(hiloUno_id, &salida_funcion);
	
	pthread_t hiloDos_id;
	pthread_t hiloTres_id;
	
	
	pthread_create(&hiloTres_id, NULL, imprimirNumeros, NULL);
	for(int i = 0; i < 10; i++){
		pthread_create(&hiloDos_id, NULL, imprimir, NULL);
		pthread_join(hiloDos_id, &salida_funcion);
	}
	pthread_join(hiloTres_id, &salida_funcion);
	
	
	getch();
	endwin();
	exit(0);
}
