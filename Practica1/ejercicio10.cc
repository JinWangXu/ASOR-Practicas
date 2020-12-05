#include <limits.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>

int main() {
   struct passwd *id;
   id = getpwuid(getuid());
   if(id == NULL){
      strerror(errno);
      return -1;
   }
   printf("Real User ID: %i\n", getuid());
   printf("Effective User ID: %i\n",geteuid());
   printf("Username: %s\n",id->pw_name);
   printf("Home Directory: %s\n",id->pw_dir);
   printf("User Information: %s\n",id->pw_gecos);
   return 0;
}
