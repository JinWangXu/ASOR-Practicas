#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {

   ret = 0;
   if(setuid(0) == -1){
      ret = -1
      perror("Ha ocurrido un error");
   }
   return ret;
}

