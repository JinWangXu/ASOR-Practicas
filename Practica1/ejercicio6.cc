#include <limits.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
   int error = 0;
   int error2 = 0;
   int error3 = 0;

   error = sysconf(_SC_ARG_MAX);
   error2 = sysconf(_SC_CHILD_MAX);
   error3 = sysconf(_SC_OPEN_MAX);
   if(error  == -1 || error2 == -1 || error3 == -1 ){
      printf(strerror(errno));
      return -1;
   }
   else{
      printf("The maximum length of the arguments to the exec(3) family of functions. Must not be less than _POSIX_ARG_MAX (4096).\n");
      printf("The  maximum number of files that a process can have open at any time. Must not be less than _POSIX_OPEN_MAX (20).\n");
      printf("The maximum number of simultaneous  processesper user ID. Must not be less than _POSIX_CHILD_MAX (25).\n");
   }
   return 0;
}
