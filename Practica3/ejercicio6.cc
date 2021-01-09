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
   pid_t pid;
   pid = fork();
   switch (pid) {
      case -1:
         perror("fork");
         exit(1);
      case 0:
         pid_t sPid;
         struct rlimit rlim;
         char cwd[PATH_MAX];
         chdir("/tmp");
         sPid = setsid();
         if(sPid == -1){
            printf("Error: %s\n",strerror(errno));
            return 1;
         }
         if(getrlimit(RLIMIT_NOFILE, &rlim) == -1){
            printf("Error: %s\n",strerror(errno));
            return 1;
         }
         if (getcwd(cwd, sizeof(cwd)) == NULL) {
             printf("Error: %s\n",strerror(errno));
             return 1;
         }
         printf("Hijo: %i, (padre: %i)\n", getpid(), getppid());
         printf("Grupo: %i, Sesion: %i\n", getpgid(pid), getsid(pid));
         printf("Número máximo de ficheros que abren el proceso actual: %i\n", rlim.rlim_cur);
         printf("Direccion Actual: %s\n", cwd);
	 return 0;
      default:
         sleep(4);
         printf("Padre %i (hijo: %i)\n", getpid(), pid);
   }
}
