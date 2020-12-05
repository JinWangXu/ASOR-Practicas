#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {

   int max_error = 255;
   printf("Lista de errores");
   for(int i = 1; i < max_error; i++){ 
      printf("Cod: %d - MSG: %s", i, strerror(i));
   }
   return 0;
}

