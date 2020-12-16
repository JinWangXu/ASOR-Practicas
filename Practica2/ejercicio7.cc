#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {

   umask(0027);
   if(open("fichero.txt", (O_RDWR | O_CREAT), (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IXOTH)) == -1){
      strerror(errno);
      return -1;
   }
   return 0;
}
