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
         char a[100];
         int i;
         for (i = 1; i < argc; i++){
            strcat(a, argv[i]);
            strcat(a," ");
         }
         system(a);
         printf("El comando terminó de ejecutarse \n");
	 return 0;
      default:
         sleep(2);
         execvp(argv[1], argv + 1);
         printf("El comando terminó de ejecutarse \n"); //Tras realizar el exec, no ejecuta ningún codigo debajo del programa, por lo que este printf no se ejecuta
   }
}
