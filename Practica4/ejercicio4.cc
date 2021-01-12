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
   int fd = open("tuberia", O_WRONLY);
   if(fd == -1){
      perror("Error al abrir fichero");
      return -1;
   }
   if(write(fd,argv[1],strlen(argv[1])) == -1){
      perror("Error al escribir en la tuberia");
      return -1;
   }
   close(fd);
   return 0;
}
