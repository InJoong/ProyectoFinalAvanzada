/*
Librerías:
*/
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>   
#include<unistd.h>      

struct player
{
        int id;
        int x;
        int y;
} typedef Player;

int main(int argc , char *argv[])
{
        struct player p = malloc(sizeof(player));
        p.x = 3;
	p.y = 4;
	p.id = 2;
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
          char mensaje_cliente[2000];
          if(recv(nuevo_socket , mensaje_cliente , 2000 , 0) < 0){
            puts("Error en el mensaje del cliente");
            return -1;
          }
          printf(mensaje_cliente);

          /*
          RESPUESTA AL CLIENTE
          */
          mensaje = "HOLA....desde el server PUM...\n";
          write(nuevo_socket , mensaje , strlen(mensaje));
        }
        return 0;
}
