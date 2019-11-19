/*
Librerías:
*/
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc , char *argv[])
{
	int descriptor_socket;
	struct sockaddr_in server;
	char * mensaje , respuesta_server[2000];

	/*
	CREA un socket
	*/
	descriptor_socket = socket(AF_INET , SOCK_STREAM , 0);
	if (descriptor_socket == -1)
	{
		printf("NO SE CREA EL SOCKET");
		return 1;
	}

	server.sin_addr.s_addr = inet_addr("192.168.1.145");
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
	mensaje = "This is SPARTA! ";
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
	puts(respuesta_server);

	return 0;
}
