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
   int fd[2];
   pipe(fd);
   pid = fork();
   switch (pid) {
      case -1:
         perror("fork");
         exit(1);
      case 0:
         if(dup2(fd[1], 1) == -1){
             printf("Error: %s\n",strerror(errno));
             return -1;
         }
         close(fd[1]);
         close(fd[0]);
         if(execlp(argv[1], argv[1], argv[2], NULL) == -1){
            perror("Exec Failed");
            return -1;
         }
      default:
         if(dup2(fd[0], 0) == -1){
             printf("Error: %s\n",strerror(errno));
             return -1;
         }
         close(fd[0]);
         close(fd[1]);
         if(execlp(argv[3], argv[3], argv[4], NULL) == -1){
            perror("Exec Failed");
            return -1;
         }
   }
}
