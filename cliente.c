/*
Librerías:
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<ncurses.h>

struct player
{
	int id;
	int x;
	int y;
};

int main(int argc , char *argv[])
{
	struct player plyr;
	plyr.id = 2;
	plyr.x = 1;
	plyr.y = 3;
	
	struct player * ptrp = malloc(sizeof(struct player));
	
	ptrp = &plyr;
	
	int descriptor_socket;
	struct sockaddr_in server;	
	char * mensaje, respuesta_server[2000];

	/*
	CREA un socket
	*/
	descriptor_socket = socket(AF_INET , SOCK_STREAM , 0);
	if (descriptor_socket == -1)
	{
		printf("NO SE CREA EL SOCKET");
		return 1;
	}

	server.sin_addr.s_addr = inet_addr("10.48.193.25");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8007 );

	/*
	Conexión con el server
	*/
	if (connect(descriptor_socket , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("ERROR de conexión con el server");
		return 1;
	}

	puts("CONNECTADO... PUM!\n");

	/*
	Enviar datos al server
	*/
	mensaje = "Fer fue tocado";
	if( send(descriptor_socket , (struct player *) ptrp , sizeof(struct player), 0) < 0)
	{
		puts("FALLA AL ENVIAR");
		return 1;
	}
	puts("DATOS ENVIADOS \n");

	/*
	RECEPCIOn de DATOS del SERVER
  redes2tec
	*/
	struct player *rev_player = malloc(sizeof(struct player));
	if(recv(descriptor_socket, rev_player , sizeof(struct player), 0) < 0)
	{
		puts("FALLA EN LA RECEPCION");
	}
	puts("DATOS RECIBIDOS\n");
	printf("id: %d\n", rev_player->id);

	return 0;
}
