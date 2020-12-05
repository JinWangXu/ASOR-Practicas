#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main() {
   int million = 1000000;
   struct timeval ti;
   struct timeval tf;
   if(gettimeofday(&ti, NULL) == -1){
      strerror(errno);
      return(-1);
   }
   for(int inc = 0; inc < million; inc++){
   }
   if(gettimeofday(&tf, NULL) == -1){
      strerror(errno);
      return(-1);
   }
   printf("Time transcurred: %ld suseconds \n", (tf.tv_usec - ti.tv_usec));
   return 0;
}
