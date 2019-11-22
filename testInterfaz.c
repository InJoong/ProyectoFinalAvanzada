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
	getch();
	endwin();
		
	pthread_exit( salida ); 
}

void * imprimir(void * vargs){
	for(int i = 0; i < 100054; i++){
		printw("%d", i);
	}
			
}

int main(){
	void * salida_funcion;
	char * ip;
	ip = (char *) malloc(20);
	strcpy(ip, "192.168.0.1");
	
	pthread_t hiloUno_id;
	pthread_create(&hiloUno_id, NULL, manejadorDeInterfaz, ip);
	pthread_t hiloDos_id;
	pthread_create(&hiloDos_id, NULL, imprimir, ip);
	pthread_join(hiloUno_id, &salida_funcion);
	exit(0);
}
