#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char **argv) {
   if(argc == 2 ){
      int fd = open(argv[1], O_RDWR | O_TRUNC);
      if(dup2(fd, 1) == -1){
         printf("Error: %s\n",strerror(errno));
         return -1;
      }
      printf("Esto es una cadena de caracteres");
      close(fd);
   }
   else{
      printf("Parametros incorrectos");
   }
   return 0;
}
