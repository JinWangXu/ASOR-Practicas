#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <dirent.h>

int main(int argc, char **argv) {

   struct stat status;
   unsigned long totalSize = 0;
   if(argc == 2 ){
      DIR *d = opendir(argv[1]);
      dirent* dir = readdir(d);
      while(dir != NULL){
         if(lstat(dir->d_name, &status) == -1){
            printf("Error: %s\n",strerror(errno));
            return -1;
         }
         if (((status.st_mode & S_IEXEC) != 0)) {
            printf("Execute, %s*\n", dir->d_name);
            totalSize += status.st_size;
         }
         else if (S_ISREG(status.st_mode)) {
            printf("Regular File, %s\n", dir->d_name);
            totalSize += status.st_size;
         }
         else if (S_ISDIR(status.st_mode)) {
            printf("Directory, %s/\n", dir->d_name);
         } 
         else if (S_ISLNK(status.st_mode)) {
            printf("Symbolic Link, %s->\n", dir->d_name);
            char * linkname = (char*) malloc(status.st_size + 1);
            if (linkname == NULL) {
               printf("Error: %s\n",strerror(errno));
               return -1;
            }
            if (readlink(dir->d_name, linkname, status.st_size + 1) == -1) {
               printf("Error: %s\n",strerror(errno));
               return -1;
            }
            totalSize += status.st_size;
         }
         dir = readdir(d);
      }
      unsigned long totalSizeKB = totalSize /1024;
      printf("Total size: %lu\n", totalSizeKB);
      closedir(d);
   }
   else{
      printf("Parametros incorrectos");
   }
   return 0;
}
