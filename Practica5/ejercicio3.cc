#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sched.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <netdb.h>
#include <locale.h>
#include <time.h>
#include <sys/time.h>
int main(int argc, char **argv) {

   //Recogemos el tiempo
   if(setlocale(LC_ALL, "es_ES") == NULL){
      printf("No se ha podido cambiar a español\n");
   }
   char hora[10];
   char host[NI_MAXHOST];
   char serv[NI_MAXSERV];
   struct tm *tm;
   struct addrinfo  filtro;
   struct addrinfo * res;

   memset(&filtro,0, sizeof(addrinfo));
   filtro.ai_flags = AI_PASSIVE; 
   filtro.ai_family = AF_UNSPEC; //IPv4, IPv6
   filtro.ai_socktype = SOCK_DGRAM; //UDP

   int gai = getaddrinfo(argv[1], argv[2], &filtro, &res);
   if(gai != 0){
      printf("Error al recoger informacion: %s\n", gai_strerror(gai));
      return -1;
   }
   int sd = socket(res->ai_family, res->ai_socktype, 0); //socket
   if(sd == -1){
      perror("Socket mal creado\n");
   }
   bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

   struct sockaddr_storage addr; //necesario ya que sockaddr esta anticuado
   socklen_t addrlen = sizeof(struct sockaddr_storage);


   int bSend = sendto(sd, argv[3], 2, 0, res->ai_addr, res->ai_addrlen);
   if(bSend == -1){
      perror("Error en sendto");
   }

   int bytes = recvfrom(sd, hora, 9, 0, (struct sockaddr *) &addr, &addrlen);
   if(bytes == -1){
      perror("Error en recvfrom\n");
   }
   hora[bytes] = '\0';
   printf("La hora es: %s\n", hora);
   close(sd);
   return 0;
}
