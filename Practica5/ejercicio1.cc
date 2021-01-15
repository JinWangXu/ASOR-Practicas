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


int main(int argc, char **argv) {
   struct addrinfo  filtro;
   memset(&filtro,0, sizeof(addrinfo)); //memset sirve para inicializar los valores dentro del struct a 0, muy util para no estar poniendo todo a 0 linea por linea

   filtro.ai_flags = AI_PASSIVE;
   filtro.ai_family = AF_UNSPEC;

   struct addrinfo * res;

   int gai = getaddrinfo(argv[1], NULL, &filtro, &res);
   if(gai != 0){
      printf("Error al recoger informacion: %s\n", gai_strerror(gai));
      return -1;
   }

   while(res != NULL){
      char host[NI_MAXHOST];

      getnameinfo(res->ai_addr,res->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
      printf("Host: %s | Familia: %i   | Tipo: %i\n", host, res->ai_family, res->ai_socktype);
      res = res->ai_next;
   }
   freeaddrinfo(res);
   return 0;
}
