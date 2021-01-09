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


int main(int argc, char **argv) {
   int pid = getpid();
   int ppid = getppid();
   int gpid = getpgid(pid);
   int spid = getsid(pid);
   char cwd[PATH_MAX];
   struct rlimit rlim;

   printf("Proceso Padre:%i\n", pid);
   printf("Proceso Actual:%i\n", ppid);
   printf("Grupo de procesos:%i\n", gpid);
   printf("Sesion de procesos:%i\n", spid);
  
   if(getrlimit(RLIMIT_NOFILE, &rlim) == -1){
       printf("Error: %s\n",strerror(errno));
       return 1;
   }
   printf("Número máximo de ficheros que abren el proceso actual: %i\n", rlim.rlim_cur);
   if (getcwd(cwd, sizeof(cwd)) == NULL) {
       printf("Error: %s\n",strerror(errno));
       return 1;
   }
   printf("Direccion Actual: %s\n", cwd);
   return 0;
}
