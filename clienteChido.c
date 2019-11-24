#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int miId = 0;
//Eston son socket de los clientes
int socketHermano1, socketHermano2; //Descriptor_socket
struct sockaddr_in serverHermano1, serverHermano2; //server

//Estos son el server del host
int miServerSocket, nuevoSocketServer; //Descriptor_socket, nuevo_socket
struct sockaddr_in miServer, clienteTemporal; //server, client

pthread_mutex_t lockParaDibujar;


struct IPContainer{
	char * ip1;
	char * ip2;	
};

struct IPContainer * ips;


struct Personaje
{
	int id;
	int xPosition;
	int yPosition;
	char c;
};


void serializador(struct Personaje * persona, char serializado[]){

	serializado[0] = persona->id + 48; //ASCII niero
	if(persona->xPosition < 9){
		serializado[1] = 48;
		serializado[2] = persona->xPosition + 48;
	} else {
		serializado[1] = ((int) (persona->xPosition / 10)) + 48;
		serializado[2] = (persona->xPosition % 10) +48;
	}
	
	if(persona->yPosition < 9){
		serializado[3] = 48;
		serializado[4] = persona->yPosition + 48;
	} else {
		serializado[3] = ((int) (persona->yPosition / 10)) + 48;
		serializado[4] = (persona->yPosition % 10) +48;
	}
	
	serializado[5] = persona->c;
	
	serializado[6] = '\0';
	

	
}

void deserializador(char personajeSerializado[], struct Personaje * recipiente){
		pthread_mutex_lock(&lockParaDibujar);
	move(10, 51);
			//printw("%s", personajeSerializado);
			/*move(11, 51);
			printw("%d", serializado[0]);*/
			refresh();
			pthread_mutex_unlock(&lockParaDibujar);
			
			
	/*recipiente->id = personajeSerializado[0] - 48;
	recipiente->xPosition = ((personajeSerializado[1] - 48) * 10) + (personajeSerializado[2] - 48);
	recipiente->yPosition = ((personajeSerializado[3] - 48) * 10) + (personajeSerializado[4] - 48);
	recipiente->c = personajeSerializado[5];*/
}

struct Personaje personajes[3];


void * llamador(void * vargs){
	
	//Por cada ip
	//Mnda el paquete que recibio en vargs
}

void * escuchador(void * vargs){
	void * salida;
	while(1){
		int c = sizeof(struct sockaddr_in);
		while((nuevoSocketServer = accept(miServerSocket, (struct sockaddr *)&clienteTemporal, (socklen_t *)&c))){
			if(nuevoSocketServer < 0){
			}
			
			struct Personaje * info_jugador = malloc(sizeof(struct Personaje));
			char * mensaje = "112218";
			
			if(recv(nuevoSocketServer, mensaje, sizeof(char)*7, 0) < 0){
				//continue;
			} else {
			
			pthread_mutex_lock(&lockParaDibujar);
			move(10, 51);
			printw("%s", mensaje);
			/*move(11, 51);
			printw("%d", serializado[0]);*/
			refresh();
			pthread_mutex_unlock(&lockParaDibujar);
			
			deserializador(mensaje, info_jugador);
			
			int idExterno = info_jugador->id;
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(personajes[idExterno].xPosition, personajes[idExterno].yPosition, ' ');	
			personajes[idExterno].xPosition = info_jugador->xPosition;
			personajes[idExterno].yPosition = info_jugador->yPosition;
			mvaddch(personajes[idExterno].xPosition, personajes[idExterno].yPosition, personajes[idExterno].c);
			refresh();
			pthread_mutex_unlock(&lockParaDibujar);
		}
			free(info_jugador);
		
		}
	//Otros le hablan
	//Personaje
	//Ubica la ip
	//Dibuja al wey basnadose en quien lo mando 
	}
	
}



void * moverseLocal(void * vargs){
	
	void * salida;
	noecho();
	int c = getch();
	switch(c){
		case 'w':
		case 'W':
			//CHecamos colisiones
			//Gurdamos las nuevas coordenadas
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, ' ');	
			personajes[miId].xPosition = personajes[miId].xPosition - 1;
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, personajes[miId].c);
			pthread_mutex_unlock(&lockParaDibujar);
			
			break;
		case 'a':
		case 'A':
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, ' ');	
			personajes[miId].yPosition = personajes[miId].yPosition - 1;
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, personajes[miId].c);
			pthread_mutex_unlock(&lockParaDibujar);
			break;
		case 's':
		case 'S':
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, ' ');	
			personajes[miId].xPosition = personajes[miId].xPosition + 1;
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, personajes[miId].c);
			pthread_mutex_unlock(&lockParaDibujar);
			break;
		case 'D':
		case 'd':
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, ' ');	
			personajes[miId].yPosition = personajes[miId].yPosition + 1;
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, personajes[miId].c);
			pthread_mutex_unlock(&lockParaDibujar);
			break;
		default:
			break;
	}
	
	char infoAEnviar[7];
	
	
	serializador(&personajes[miId], infoAEnviar);
	
	send(socketHermano1, infoAEnviar,sizeof(infoAEnviar), 0);
	
	//LLAMAR AL QUE LLAMA
	refresh();
	
	pthread_exit( salida ); 
			
}

void * inicializarMapa(void * vargs){
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
	
	mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, personajes[miId].c);
	refresh();
	pthread_exit( salida ); 
}

int main(int argc, char * argv[]){
	initscr();
	ips = malloc(sizeof(struct IPContainer));
	ips->ip1 = argv[1];
	ips->ip2 = argv[2];
	
	//Conexion server propio
	miServerSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(miServerSocket == -1){
		endwin();
		exit(1);
	}
	
	miServer.sin_family = AF_INET;
	miServer.sin_addr.s_addr = INADDR_ANY;
	miServer.sin_port = htons(8082);
	
	if(bind(miServerSocket, (struct sockaddr *)&miServer, sizeof(miServer) ) < 0 ) {
		printw("1");
		getch();
		endwin();
		exit(1);
	}
	
	listen(miServerSocket, 3);
	
	//Conexion Hermano 1
	socketHermano1 = socket(AF_INET, SOCK_DGRAM, 0);
	if(socketHermano1 == -1){
		printw("2");
		getch();
		endwin();
		exit(1);
	}
	
	serverHermano1.sin_addr.s_addr = inet_addr(ips->ip1);
	serverHermano1.sin_family = AF_INET;
	serverHermano1.sin_port = htons(8083);
	
	if(connect(socketHermano1, (struct sockaddr *)&serverHermano1, sizeof(serverHermano1) ) < 0){
		printw("3");
		getch();
		endwin();
		exit(1);
	}
	
	//Conexion Hermano 2 
	socketHermano2 = socket(AF_INET, SOCK_DGRAM, 0);
	if(socketHermano2 == -1){
		printw("4");
		getch();
		endwin();
		exit(1);
	}
	
	serverHermano2.sin_addr.s_addr = inet_addr(ips->ip2);
	serverHermano2.sin_family = AF_INET;
	serverHermano2.sin_port = htons(8081);
	
	if(connect(socketHermano2, (struct sockaddr *)&serverHermano2, sizeof(serverHermano2) ) < 0){
		printw("5");
		getch();
		endwin();
		exit(1);
	}
	
	
	
	

	
	if(argc != 4 ){
		printw("6");
		getch();
		endwin();
		exit(1);
		
	}
	for(int j = 0; j < argc; j++){
		move(j, 51);
		
		printw("%s", argv[j]);
		refresh();
	}
	
	curs_set(0);

	if(pthread_mutex_init(&lockParaDibujar, NULL) != 0){
		
		printf("Fallo el mutex");
		return -1;
	}
	
	void * salida_funcion;
	char * ip;
	ip = (char *) malloc(20);
	strcpy(ip, "192.168.0.1");
	
	
	//Definir el estado inicial de cada player;
	switch(*argv[3]){
		case '1':
			miId = 0;
			break;
		case '2':
			miId = 1;
			break;
		case '3':
			miId = 2;
			break;
		default:
			break;
	}
	//personajes[0] = malloc(sizeof(struct Personaje));
	personajes[0].id = 0;
	personajes[0].xPosition = 2;
	personajes[0].yPosition = 2;
	personajes[0].c = '0';
	
	//HARCODEO MAXIMO
	//personajes[1] = malloc(sizeof(struct Personaje));
	personajes[1].id = 1;
	personajes[1].xPosition = 18;
	personajes[1].yPosition = 18;
	personajes[1].c = '1';
	
	//personajes[2] = malloc(sizeof(struct Personaje));
	personajes[2].id = 2;
	personajes[2].xPosition = 18;
	personajes[2].yPosition = 1;
	personajes[2].c = '2';
	
	
	
	//MAndar a los otros tu informacion
	
	//REcibir informacion inicial de los otros
	
	pthread_t hiloDos_id;
	pthread_t hiloTres_id;
	pthread_t hiloEscuchador_id;
	
	pthread_create(&hiloEscuchador_id, NULL, escuchador, NULL);
	
	
	pthread_create(&hiloTres_id, NULL, inicializarMapa, NULL);
	while(1){
		pthread_create(&hiloDos_id, NULL, moverseLocal, NULL);
		pthread_join(hiloDos_id, &salida_funcion);
	}
	pthread_join(hiloTres_id, &salida_funcion);
	
	
	getch();
	endwin();
	exit(0);
}
