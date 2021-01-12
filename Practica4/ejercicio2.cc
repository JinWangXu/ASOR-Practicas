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
   int p_h[2];
   int h_p[2];

   pipe(p_h);
   pipe(h_p);

   pid = fork();
   switch (pid) {
      case -1:
         perror("fork");
         exit(1);
      case 0:
         char d;
         char line2;
         close(p_h[1]);
         close(h_p[0]);
         for(int i = 0; i <= 10; i++){
            if(read(p_h[0], &line2, sizeof(line2)) == -1){
               perror("Error al leer de la tuberia p_h");
               return -1;
            }
            printf("El hijo ha leido: %c\n", line2);
            sleep(1);
            if(i < 10){
               d = 'l';
            }
            else{
               d = 'q';
            }
            if(write(h_p[1], &d, sizeof(d)) == -1){
               perror("Error al escribir en la tuberia h_p");
               return -1;
            }
        
         }
         close(p_h[0]);
         close(h_p[1]);
         return 0;  
      default:
         char c;
         char line[255];
         close(p_h[0]);
         close(h_p[1]);
         
         while(c != 'q'){
            printf("Escribe un unico caracter\n");
            fgets(line, sizeof(line), stdin);
            if(write(p_h[1], &line, 1) == -1){
               perror("Error al escribir en la tuberia p_h");
               return -1;
            }
            if(read(h_p[0], &c, sizeof(c)) == -1){
               perror("Error al leer de la tuberia h_p");
               return -1;
            }
            printf("El padre ha leido: %c\n", c);
         }
         close(p_h[1]);
         close(h_p[0]); 
         return 0;        
   }
}
