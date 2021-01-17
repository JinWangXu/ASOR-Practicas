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

   char host[NI_MAXHOST];
   char serv[NI_MAXSERV];
   char buf[80];
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
   int cn = connect(sd, res->ai_addr, res->ai_addrlen);
   if(cn == -1){
      perror("Error en la conexion");
   } 
   while(1){
      int c = read(0, buf, 79);
      if(c == -1){
         perror("Error en la lectura del terminal");
      }
      buf[c] = '\0';
      if(buf[0] == 'Q' && c == 2){ //2 porque hay que tener en cuenta \n que se lee del terminal
          break;
      }
      int bSend = send(sd, buf, c, 0);
      if(bSend == -1){
         perror("Error en sendto");
      }
      int bytes = recv(sd, buf, 79, 0);
      if(bytes == -1){
         perror("Error en recvfrom\n");
      }
      buf[bytes] = '\0';
      printf("%s\n", buf);
   }
   close(sd);
   return 0;
}
