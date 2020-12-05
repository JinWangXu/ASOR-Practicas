#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {

   int ret = 0;
   if(setuid(0) == -1){
      ret = -1;
      printf("Codigo de error: %d", errno);
      printf(strerror(errno));
   }
   return ret;
}

