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
#include <limits.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
static volatile int cont = 0; 
void killEx(int alarm){
   printf("Borrando el ejecutable...\n");
   cont = 0;
}

void detEx(int alarm){
   printf("Lo ha detenido a tiempo...\n");
   cont = 1;
}
int main(int argc, char **argv) {

   sigset_t s;
   sigfillset(&s);
   sigdelset(&s, SIGALRM);
   sigdelset(&s, SIGUSR1);

   signal(SIGALRM, killEx);
   signal(SIGUSR1, detEx);
   alarm(atoi(argv[1]));

   sigsuspend(&s);
   if(cont == 0) {
      unlink(argv[0]);
   }
   return 0;
}


