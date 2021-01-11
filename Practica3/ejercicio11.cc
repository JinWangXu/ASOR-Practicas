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

int main(int argc, char **argv) {
   sigset_t s;
   sigemptyset(&s);
   sigaddset(&s, SIGINT);
   sigaddset(&s, SIGTSTP);
   sigprocmask(SIG_BLOCK, &s, NULL);

   char *sp = getenv("SLEEP_SECS");
   int seg = atoi(sp);
   printf("Durmiendo...");
   sleep(seg);

   sigset_t p;
   sigpending(&p);

   if(sigismember(&p, SIGINT)) {
      sigdelset(&s, SIGINT);
   }
   if(sigismember(&p, SIGTSTP)) {
      sigdelset(&s, SIGTSTP);
   }

   sigprocmask(SIG_UNBLOCK, &s, NULL);
   return 0;
}
