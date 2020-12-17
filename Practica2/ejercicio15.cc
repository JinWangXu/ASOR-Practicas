#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char **argv) {
   if(argc == 2 ){
      int fd = open(argv[1], O_RDWR | O_TRUNC);
      int lk = lockf(fd, F_TEST, 0);
      if(lk == 0){ //Desbloqueado
         lockf(fd, F_LOCK, 0);
         char outstr[200];
         time_t t = time(NULL);
         struct tm *tm;
         tm = localtime(&t);
         strftime(outstr, sizeof(outstr), "%R", tm);
         printf("%s\n", outstr);
         sleep(3);
         lockf(fd, F_ULOCK, 0);
         printf("Fichero Desbloqueado\n");
      }
      else{ //Bloqueado
         printf("Fichero Bloqueado\n");
      }
      close(fd);
   }
   else{
      printf("Parametros incorrectos");
   }
   return 0;
}
