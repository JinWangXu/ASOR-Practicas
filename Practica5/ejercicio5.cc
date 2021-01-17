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

   char fecha[50];
   char hora[10];
   char buffer[2]; 
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
   int cant = 0;
   pid_t pid;
   while(cant < 5){
      pid = fork();
      if(pid == 0){
         break;
      }
      cant++;
   }
   switch(pid){
      case -1:
         perror("fork");
         exit(1);
      case 0:
         while(1){
            int bytes = recvfrom(sd, buffer, 1, 0, (struct sockaddr *) &addr, &addrlen);
            printf("PID Hijo: %i\n", getpid());
            if(bytes == -1){
               perror("Error en recvfrom\n");
            }
            buffer[bytes] = '\0';

            int gt = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
            if(gt != 0){
               perror("Error en getnameinfo\n");
            }
            time_t t = time(NULL);
            tm = localtime(&t);      
            printf("%i Bytes del Host: %s | Puerto: %s   | MSG: %s\n", bytes, host, serv, buffer); 
            
            if(buffer[0] == 't'){
               int c = strftime(hora, sizeof(hora)- 1, "%R", tm);
               hora[c] = '\0';
               sendto(sd, hora, c, 0, (struct sockaddr *) &addr, addrlen);
            }
            else if(buffer[0] == 'd'){
               int c = strftime(fecha, sizeof(fecha)- 1, "%A, %d de %B de %Y", tm);
               fecha[c] = '\0';
               sendto(sd, fecha, c, 0, (struct sockaddr *) &addr, addrlen);
            }
            else if(buffer[0] == 'q'){
               printf("Se ha terminado el proceso\n");
               break;
            }
            else{
               printf("El comando %s, no es valido\n", buffer);
            }
         }
         break;

      default:
         printf("PID Padre: %i\n", getpid());
         sleep(100);
      }

   return 0;
}
