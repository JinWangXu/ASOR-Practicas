#include <limits.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main() {
   time_t t;
   int sec = time(&t);
   if(sec == -1){
      strerror(errno);
      return -1;
   }
   printf("Time in seconds: %i", sec);
   return 0;
}
