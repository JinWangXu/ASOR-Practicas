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
      struct stat status;
      if(stat(argv[1], &status) == -1){
         printf("Error: %s\n",strerror(errno));
         return -1;
      }
      int statusMajor = major(status.st_dev);
      int statusMinor = minor(status.st_dev);
      printf("Major:%d\n", statusMajor);
      printf("Minor:%d\n", statusMinor);
      printf("I-node:%d\n", status.st_ino);
      if (S_ISREG(status.st_mode)) {
         printf("Regular File\n");
      }
      if (S_ISDIR(status.st_mode)) {
         printf("Directory\n");
      }
      if (S_ISLNK(status.st_mode)) {
         printf("Symbolic Link\n");
      }
      printf("Last Time Access:%d\n", status.st_atime);
   }
   else{
      printf("Parametros incorrectos");
   }
      
   return 0;
}
