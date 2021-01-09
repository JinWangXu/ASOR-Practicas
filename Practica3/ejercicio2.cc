#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sched.h>

int main(int argc, char **argv) {
   struct sched_param p;
   int policy;
   int max;
   int min;

   if (policy = sched_getscheduler(0) == -1) {
      printf("Error: %s\n",strerror(errno));
      return -1;
   }
   printf("La politica de planificación del proceso actual: %i \n", policy);
   if (sched_getparam(0, &p) == -1) {
      printf("Error: %s\n",strerror(errno));
      return -1;
   }
   printf("La prioridad de planificacion del proceso actual: %i \n", p.sched_priority);
   if (max = sched_get_priority_max(policy) == -1) {
      printf("Error: %s\n",strerror(errno));
      return -1;
   }
   printf("Su prioridad maxima es: %i \n", max);
   if (min = sched_get_priority_min(policy) == -1) {
      printf("Error: %s\n",strerror(errno));
      return -1;
   }
   printf("Su prioridad minima es: %i \n", min);
   return 0;
}
