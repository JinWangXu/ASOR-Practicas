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

   int a = 0;
   int c = 0;
   char buf[81]; 
   char host[NI_MAXHOST];
   char serv[NI_MAXSERV];
   struct addrinfo  filtro;
   struct addrinfo * res;

   memset(&filtro,0, sizeof(addrinfo));
   filtro.ai_flags = AI_PASSIVE; 
   filtro.ai_family = AF_UNSPEC; //IPv4, IPv6
   filtro.ai_socktype = SOCK_STREAM; //TCP
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
   freeaddrinfo(res);

   listen(sd, 5);
   while(1) {
      struct sockaddr_storage addr; //necesario ya que sockaddr esta anticuado
      socklen_t addrlen = sizeof(struct sockaddr_storage);
      a = accept(sd, (struct sockaddr *) &addr, &addrlen);
      if(a == -1){
          perror("Error en la conexion establecida");
          return -1;
      }
      getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST,
      serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
      printf("Conexion desde Host:%s Puerto:%s\n", host, serv);
      pid_t pid = fork();
      switch(pid){
         case -1:
            close(sd);
            close(a);
            break;

         case 0:
            close(sd); //Duplicado y como no se usa, se cierra
            c = 0;
            while (1) {
               c = recv(a, buf, 80, 0);
               if(c == -1){
                  perror("Error en recibir");
               }
               if(c == 0){
                  break;
               }
               buf[c] = '\0';
               send(a, buf, c, 0);
            }
            printf("Conexion terminada\n");
            close(a);
            return 0;
         default:
            close(a); //Lo cierra el padre porque no lo va a usar, y ademas esta duplicado tanto en el padre como en el hijo
            break;
      }
   }
   close(sd);
   return 0;
}
