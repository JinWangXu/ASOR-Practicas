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
   int fd1;
   int fd2;
   int fd3;

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
         fd1 = open("/tmp/daemon.out", O_CREAT | O_TRUNC | O_RDWR, 0640);
         fd2 = open("/tmp/daemon.err", O_CREAT | O_TRUNC | O_RDWR, 0640);
         fd3 = open("/dev/null", O_CREAT | O_TRUNC | O_RDWR, 0640);

         if(dup2(fd1, 1) == -1){
             printf("Error: %s\n",strerror(errno));
             return -1;
         }
         if(dup2(fd2, 2) == -1){
             printf("Error: %s\n",strerror(errno));
             return -1;
         }
         if(dup2(fd3, 0) == -1){
             printf("Error: %s\n",strerror(errno));
             return -1;
         }


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

         execvp(argv[1], argv + 1);

	 return 0;
      default:
         sleep(4);
         printf("Padre %i (hijo: %i)\n", getpid(), pid);
   }
}
