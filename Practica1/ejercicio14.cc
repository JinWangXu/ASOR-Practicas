#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main() {
   time_t t = time(NULL);
   struct tm *tm;
   tm = localtime(&t);
   if(tm == NULL){
      strerror(errno);
      return(-1);
   }
   printf("Year: %i\n", 1900 + tm->tm_year);
   return 0;
}

