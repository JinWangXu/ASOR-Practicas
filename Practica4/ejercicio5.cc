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


int main(int argc, char **argv) {
   char buffer[256];
   int fd = open("tuberia", O_RDONLY | O_NONBLOCK);
   if(fd == -1){
      perror("Error al abrir fichero");
      return -1;
   }
   int fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
   if(fd == -1){
      perror("Error al abrir fichero");
      return -1;
   }
   while(1){
      fd_set set;
      FD_ZERO(&set);
      FD_SET(fd, &set);
      FD_SET(fd2, &set);
      int nfds = 0;
      if(fd >= fd2){
         nfds = fd + 1;
      }
      else{
         nfds = fd2 + 1;
      }
      int st = select(nfds, &set, 0, 0, 0);
      if(st == -1){
         perror("Error en el select: ");
      }
      if(FD_ISSET(fd, &set)){

         int total = read(fd, &buffer, 255);
         if(total == -1){
            perror("Error en el read: ");
         }
         buffer[total] = '\0';
         if(total == 0){
            fd = open("tuberia", O_RDONLY | O_NONBLOCK);
         }
         else{
            printf("Tuberia:%i  Ha escrito: %s\n", fd, buffer);
         }
      }
      if(FD_ISSET(fd2, &set)){

         int total = read(fd2, &buffer, 255);
         if(total == -1){
            perror("Error en el read: ");
         }
         buffer[total] = '\0';
         if(total == 0){
            fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
         }
         else{
            printf("Tuberia:%i  Ha escrito: %s\n", fd2, buffer);
         }
      }
   }
   return 0;
}
