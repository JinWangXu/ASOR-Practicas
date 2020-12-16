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
      char* newPathHard = (char*) malloc(255);
      char* newPathSym =  (char*) malloc(255);
      strcpy(newPathHard, argv[1]);
      strcpy(newPathSym, argv[1]);
      struct stat status;
      if(stat(argv[1], &status) == -1){
         printf("Error: %s\n",strerror(errno));
         return -1;
      }

      if (S_ISREG(status.st_mode)) {
         if(link(argv[1], strcat(newPathHard, ".hard")) == -1){
            printf("Error: %s\n",strerror(errno));
            return -1;
         }
         if(symlink(argv[1], strcat(newPathSym, ".sym")) == -1){
            printf("Error: %s\n",strerror(errno));
            return -1;
         }
      }
   }
   else{
      printf("Parametros incorrectos");
   }
      
   return 0;
}
