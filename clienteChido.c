#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <wiringPi.h>

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
int miId = 0;
//Eston son socket de los clientes
int socketHermano1, socketHermano2; //Descriptor_socket
struct sockaddr_in serverHermano1, serverHermano2; //server

//Estos son el server del host
int miServerSocket, nuevoSocketServer; //Descriptor_socket, nuevo_socket
struct sockaddr_in miServer, clienteTemporal; //server, client

pthread_mutex_t lockParaDibujar;
pthread_mutex_t lockParaPersonajes;


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

struct Bala{
  int id;
  int xPosition;
  int yPosition;
  char c;
};

//1 - tipo de objeto: 0 - personaje, 1 - bala


//serializador para personajes
void serializador(struct Personaje * persona, char serializado[]){
  serializado[0] = 0;

	serializado[1] = persona->id + 48; //ASCII niero
	if(persona->xPosition < 9){
		serializado[2] = 48;
		serializado[3] = persona->xPosition + 48;
	} else {
		serializado[2] = ((int) (persona->xPosition / 10)) + 48;
		serializado[3] = (persona->xPosition % 10) +48;
	}
	
	if(persona->yPosition < 9){
		serializado[4] = 48;
		serializado[5] = persona->yPosition + 48;
	} else {
		serializado[4] = ((int) (persona->yPosition / 10)) + 48;
		serializado[5] = (persona->yPosition % 10) +48;
	}
	
	serializado[6] = persona->c;
	
  serializado[7] = 0;
  serializado[8] = 0;
  serializado[9] = 0;
  serializado[10] = 0;
  serializado[11] = 0;
	serializado[12] = '\0';
	

	 
}

void serializadorBala(struct Bala * balita, char serializado[]){
  //Tipo de estructura
  serializado[0] = 1;
  //Id de la balita
  int idTemp = balita->id;
	serializado[1] = ((int) (idTemp / 100000)) + 48;
  idTemp %= 100000;
  serializado[2] = ((int) (idTemp / 10000)) + 48;
  idTemp %= 10000;
  serializado[3] = ((int) (idTemp / 1000)) + 48;
  idTemp %= 1000;
  serializado[4] = ((int) (idTemp / 100)) + 48;
  idTemp %= 100;
  serializado[5] = ((int) (idTemp / 10)) + 48;
  idTemp %= 10;
  serializado[6] = idTemp + 48; //ASCII niero
	
  
  if(balita->xPosition < 9){
		serializado[7] = 48;
		serializado[8] = balita->xPosition + 48;
	} else {
		serializado[7] = ((int) (balita->xPosition / 10)) + 48;
		serializado[8] = (balita->xPosition % 10) +48;
	}
	
	if(balita->yPosition < 9){
		serializado[9] = 48;
		serializado[10] = balita->yPosition + 48;
	} else {
		serializado[9] = ((int) (balita->yPosition / 10)) + 48;
		serializado[10] = (balita->yPosition % 10) +48;
	}
	
	serializado[11] = balita->c;
	
	serializado[12] = '\0';
 //Inicilaiza random srand((unsigned) time(&seconds))
 //printf("%d", rand() % 899 + 100)
 
 //time_t seconds
 //time(&seconds)
 //int segundos = (int) seconds
 //int id = ((segundos * 1000) + {random}) % 1 000000

  //Id de la bala son 6 digitosmitere
  //posx, posy, caracter

}

void serializadorDeMuerte(struct Personaje * persona, char serializado[]){
  serializado[0] = 2;

  //Payload
  //id del que se muere
  serializado[1] = persona->id + 48;
  for(int i = 2; i < 12; i++){
    serializado[i] = 0;
  }
  serializado[12] = '\0';

}
struct Personaje personajes[3];
//Solo acepta string
//ACtua
void deserializador(char mensajeSerializado[]){
		/*pthread_mutex_lock(&lockParaDibujar);
	move(10, 51);
			//printw("%s", personajeSerializado);
			move(11, 51);
			printw("%d", serializado[0]);
			refresh();
			pthread_mutex_unlock(&lockParaDibujar);*/
	if(mensajeSerializado[0] == 0){
    struct Personaje * jugadorTemp = malloc(sizeof(struct Personaje));


    
    jugadorTemp->id = mensajeSerializado[1] - 48;
	  jugadorTemp->xPosition = ((mensajeSerializado[2] - 48) * 10) + (mensajeSerializado[3] - 48);
	  jugadorTemp->yPosition = ((mensajeSerializado[4] - 48) * 10) + (mensajeSerializado[5] - 48);
	  jugadorTemp->c = mensajeSerializado[6];

    int idExterno = jugadorTemp->id;
  
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(personajes[idExterno].xPosition, personajes[idExterno].yPosition, ' ');	

			personajes[idExterno].xPosition = jugadorTemp->xPosition;
			personajes[idExterno].yPosition = jugadorTemp->yPosition;
			mvaddch(personajes[idExterno].xPosition, personajes[idExterno].yPosition, personajes[idExterno].c | COLOR_PAIR(2));
			refresh();
			pthread_mutex_unlock(&lockParaDibujar);

  }
			
	
}



void * escuchador(void * vargs){
	void * salida;
	while(1){
		int c = sizeof(struct sockaddr_in);
			
			char mensaje[13];
			
			//Modificar el tamaño de cosas a recibir
			if(recv(miServerSocket, mensaje, 13, 0) < 0){
				move(10, 51);
				printw("%s", ":(");
			} else {
			
			pthread_mutex_lock(&lockParaDibujar);
			move(10, 51);
			printw("%s", mensaje);
			/*move(11, 51);
			printw("%d", serializado[0]);*/
			refresh();
			pthread_mutex_unlock(&lockParaDibujar);
			
			deserializador(mensaje);
		
		}
	//Otros le hablan
	//Personaje
	//Ubica la ip
	//Dibuja al wey basnadose en quien lo mando 
	}
	
	pthread_exit( salida ); 
	
}

int detectarColisiones(int posX, int posY){
  //0 no choco
  //1 si 

  //Chequar por paredes - en map
  if(map[posX][posY] == '#'){
    return 1;
  }

  //Checar por personaje - personaje
  for(int i = 0; i < 3; i++){
    if(personajes[i].xPosition == posX){
      if(personajes[i].yPosition == posY){
        return 1;
      }
    }
  }

  return 0;
}

struct TuplaRetorno{
  int choque;// 0 no choco, 1 choco
  int tipo;//o jugador, 1 pared
  int idJugador;
};

void detectarColisionesParaBala(int posX, int posY, struct TuplaRetorno * resultado){
  //0 no choco
  //1 si 
  //Chequar por paredes - en map
  if(map[posX][posY] == '#'){
    resultado->choque = 1;
    resultado->tipo = 1;
    resultado->idJugador = 0;
    return;
  }

  //Checar por personaje - personaje
  for(int i = 0; i < 3; i++){
    if(personajes[i].xPosition == posX){
      if(personajes[i].yPosition == posY){
        resultado->choque = 1;
        resultado->tipo = 0;
        resultado->idJugador = i;
        return;
      }
    }
  }

  resultado->choque = 0;
  resultado->tipo = 0;
  resultado->idJugador = 0;
  return;
}

void * controlarBala(void * vargs){
  void * salida;
  char direccion = * (char *) vargs;
  //spawnea bala
  int posXOriginal = personajes[miId].xPosition;
  int posYOriginal = personajes[miId].yPosition;

  struct Bala * balaLocal = malloc(sizeof(struct Bala));

  //TODO: AQUI MURIO balaLocal->id = 
  int existe = 1; 
  //--------------------------------------
  int posXNueva = posXOriginal;
  int posYNueva = posYOriginal;
  //i arriba
  //j izquierda
  //l derecha
  //k abajo
  while(existe == 1){
    if(direccion == 'i'){
      posXNueva = posXNueva -1;
    }  else if(direccion == 'j'){
      posYNueva = posYNueva - 1;
    } else if(direccion == 'k'){
      posXNueva = posXNueva + 1;  
    } else if(direccion == 'l'){
      posYNueva = posYNueva + 1;
    }
    //mueve bala
    struct TuplaRetorno * resultado = malloc(sizeof(struct TuplaRetorno));
    detectarColisionesParaBala(posXNueva, posYNueva, resultado);

    if(resultado->choque == 1){
      if(resultado->tipo == 0){
        //printw("Murio:" + personaje[resultado->idJugador].id); 
        // Desaparecer bala
        //Mandar mensaje de quien se murio
      } else if (resultado->tipo == 1){
        //Desaparecer bala
      }

      existe = 0;
    } else {
      //Borrar bala de donde estaba
      //Dibjar bala donde debe de estar
    }
    free(resultado);
  }
  
  pthread_exit( salida ); 
}

void dispararBala(char direccion){
  //i arriba
  //j izquierda
  //l derecha
  //k abajo

  pthread_t hiloControlador;
	
	pthread_create(&hiloControlador, NULL, controlarBala, &direccion);

  
  
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
		digitalWrite(0, HIGH);
		delay(1);
		digitalWrite(0, LOW);

      if(detectarColisiones(personajes[miId].xPosition - 1, personajes[miId].yPosition) == 0){
        pthread_mutex_lock(&lockParaDibujar);
        mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, ' ');	
        personajes[miId].xPosition = personajes[miId].xPosition - 1;
        mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, personajes[miId].c | COLOR_PAIR(1));
        pthread_mutex_unlock(&lockParaDibujar);
      }
			
			break;
		case 'a':
		case 'A':
		digitalWrite(1, HIGH);
		delay(1);
		digitalWrite(1, LOW);

      if(detectarColisiones(personajes[miId].xPosition, personajes[miId].yPosition -1 ) == 0){
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, ' ');	
      personajes[miId].yPosition = personajes[miId].yPosition - 1;
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, personajes[miId].c | COLOR_PAIR(1));
			pthread_mutex_unlock(&lockParaDibujar);
      }
			break;
		case 's':
		case 'S':
		digitalWrite(2, HIGH);
		delay(1);
		digitalWrite(2, LOW);

    if(detectarColisiones(personajes[miId].xPosition + 1, personajes[miId].yPosition) == 0){
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, ' ');	
			personajes[miId].xPosition = personajes[miId].xPosition + 1;
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, personajes[miId].c | COLOR_PAIR(1));
			pthread_mutex_unlock(&lockParaDibujar);
      }
			break;
		case 'D':
		case 'd':
		digitalWrite(3, HIGH);
		delay(1);
		digitalWrite(3, LOW);

    if(detectarColisiones(personajes[miId].xPosition, personajes[miId].yPosition + 1) == 0){
			pthread_mutex_lock(&lockParaDibujar);
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, ' ');	
			personajes[miId].yPosition = personajes[miId].yPosition + 1;
			mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, personajes[miId].c | COLOR_PAIR(1));
			pthread_mutex_unlock(&lockParaDibujar);
      }
			break;
    case 'I':
    case 'i':
      dispararBala('i');
      break;
    case 'J':
    case 'j':
      dispararBala('j');
      break;
    case 'K':
    case 'k':
      dispararBala('k');
      break;
    case 'L':
    case 'l':
      dispararBala('l');
      break;
		default:
			break;
	}
	
	char infoAEnviar[13];
	
	
	serializador(&personajes[miId], infoAEnviar);
	
	send(socketHermano1, infoAEnviar,sizeof(infoAEnviar), 0);
  send(socketHermano2, infoAEnviar,sizeof(infoAEnviar), 0);

	
	//LLAMAR ANULL
	refresh();
	
	pthread_exit( salida ); 
			
}

void * inicializarMapa(void * vargs){
	void * salida;
	
	
	for(int i = 0; i < 20; i++){
		for(int j = 0; j<50; j++){
			if(map[i][j] == '#'){
				mvaddch(i, j, '#' | COLOR_PAIR(3));
			}
		
		}
		
		refresh();
	}
	
	mvaddch(personajes[miId].xPosition, personajes[miId].yPosition, personajes[miId].c | COLOR_PAIR(1));
	refresh();
	pthread_exit( salida ); 
}

int main(int argc, char * argv[]){
	wiringPiSetup();
	for(int i = 0; i < 5; i++) { pinMode(i, OUTPUT); }
	for(int i = 0; i < 5; i++) { digitalWrite(i, LOW); }
	
	initscr();
	ips = malloc(sizeof(struct IPContainer));
	ips->ip1 = argv[1];
	ips->ip2 = argv[2];
	
	//Inicializacion de colores
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK); //JUgador local
	init_pair(2, COLOR_CYAN, COLOR_BLACK); //JUgadores externos
	init_pair(3, COLOR_RED, COLOR_BLACK); //Mapa
	
	//Conexion server propio
	miServerSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(miServerSocket == -1){
		endwin();
		exit(1);
	}
	
	miServer.sin_family = AF_INET;
	miServer.sin_addr.s_addr = INADDR_ANY;
	miServer.sin_port = htons(8081);
	
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
	serverHermano1.sin_port = htons(8081);
	
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

  if(pthread_mutex_init(&lockParaPersonajes, NULL) != 0){
		
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
	
	
	
	
	pthread_create(&hiloTres_id, NULL, inicializarMapa, NULL);
	pthread_join(hiloTres_id, &salida_funcion);
	pthread_create(&hiloEscuchador_id, NULL, escuchador, NULL);
	
	while(1){	
		
		
		pthread_create(&hiloDos_id, NULL, moverseLocal, NULL);
		pthread_join(hiloDos_id, &salida_funcion);
		
	}
	pthread_join(hiloEscuchador_id, &salida_funcion);
	
	
	getch();
	endwin();
	exit(0);
}
