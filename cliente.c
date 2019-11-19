/*
Librerías:
*/
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<ncurses.h>

struct player
{
	int id;
	int x;
	int y;
} typedef Player;



int main(int argc , char *argv[])
{
	struct player p = malloc(sizeof(player));
	int descriptor_socket;
	struct sockaddr_in server;
	char * mensaje;
	void * respuesta_server;

	/*
	CREA un socket
	*/
	descriptor_socket = socket(AF_INET , SOCK_STREAM , 0);
	if (descriptor_socket == -1)
	{
		printf("NO SE CREA EL SOCKET");
		return 1;
	}

	server.sin_addr.s_addr = inet_addr("10.48.149.150");
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
	if( send(descriptor_socket , mensaje , strlen(mensaje) , 0) < 0)
	{
		puts("FALLA AL ENVIAR");
		return 1;
	}
	puts("DATOS ENVIADOS \n");

	/*
	RECEPCIOn de DATOS del SERVER
  redes2tec
	*/
	if( recv(descriptor_socket, respuesta_server , 2000 , 0) < 0)
	{
		puts("FALLA EN LA RECEPCION");
	}
	puts("DATOS RECIBIDOS\n");
	
	p = (struct player) *respuesta_server;
	printf("id: %d x: %d y: %d", p.id, p.x, p.y);

	return 0;
}
