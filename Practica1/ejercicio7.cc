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

   error = pathconf("/" , _PC_LINK_MAX);
   error2 = pathconf("/" , _PC_NAME_MAX);
   error3 = pathconf("/" ,_PC_PATH_MAX);
   if(error  == -1 || error2 == -1 || error3 == -1 ){
      printf(strerror(errno));
      return -1;
   }
   else{
      printf("Returns  the  maximum  number  of  links to the file.");
      printf("Returns the maximum length of a filename in the directory  path  or  fd  that  the  process  is allowed  to create.");
      printf("Returns the maximum length of a relative  path‐name  when  path  or  fd is the current working directory.");
   }
   return 0;
}
