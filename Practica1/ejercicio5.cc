#include <sys/utsname.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
   int ret = 0;
   struct utsname buf;
   if(uname(&buf) == -1){
      strerror(errno);
   }
   else{
      printf("System: %s\n", buf.sysname);
      printf("Nodename: %s\n", buf.nodename);
      printf("Release: %s\n", buf.release);
      printf("Version: %s\n", buf.version);
      printf("Machine: %s\n", buf.machine);
   }
   return ret;
}
