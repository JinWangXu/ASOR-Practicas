#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main() {
   char outstr[200];

   time_t t = time(NULL);
   struct tm *tm;

   tm = localtime(&t);

   if(tm == NULL){
      strerror(errno);
      return(-1);
   }

   if (strftime(outstr, sizeof(outstr), "%A, %d de %B de %Y, %R", tm) == 0) {
      strerror(errno);
      return(-1);
   }
   printf("%s\n", outstr);
   return 0;
}
