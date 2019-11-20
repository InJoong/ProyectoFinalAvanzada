/*
Librerías:
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>   
#include<unistd.h>      

struct player
{
	int id;
	int x;
	int y;
};

int main(int argc , char *argv[])
{
        struct player plyr;
	plyr.id = 1;
	plyr.x = 5;
	plyr.y = 7;
	
	struct player * ptrp = malloc(sizeof(struct player));
        ptrp = &plyr;
        
        int descriptor_socket , nuevo_socket , c;
        struct sockaddr_in server , client;
        char * mensaje;

        /*
        Creaun socket
        */
        descriptor_socket = 
        socket(AF_INET , SOCK_STREAM , 0);
        if (descriptor_socket == -1)
        {
                puts("NO SE CREA SOCKET");
                return -1;
        }

        /*
        Estructura para el SOCKET
        */
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons( 8007 );

        /*
        Ligado
        */
        if( bind(descriptor_socket,
        (struct sockaddr *)&server , sizeof(server)) < 0)
        {
                puts("FALLA AL ASOCIAR EL SERVER");
                return 1;
        }
        puts("LISTO!");

        /*
        SERVER ESCUCHANDO
        */
        listen(descriptor_socket , 3);

        /*
        ACEPTA CONEXIONES
        */
        puts("ESPERANDO nueva CONEXION: ");
        c = sizeof(struct sockaddr_in);
        while((nuevo_socket = accept(descriptor_socket, 
        (struct sockaddr *)&client, (socklen_t*)&c)) ){
          if (nuevo_socket<0)
          {
                  perror("FALLA AL CONECTAR CON CLIENTE");
                  return 1;
          }

          puts("CONEXION ACEPTADA");
          struct player *rev_player = malloc(sizeof(struct player));
          if(recv(nuevo_socket , rev_player , sizeof(struct player), 0) < 0){
            puts("Error en el mensaje del cliente");
            return -1;
          }
          printf("id: %d\n", rev_player->id);

          /*
          RESPUESTA AL CLIENTE
          */
          if(write(nuevo_socket, ptrp, sizeof(struct player)) < 0)
          {
            puts("Error en el envio");
          }
        }
        return 0;
}
