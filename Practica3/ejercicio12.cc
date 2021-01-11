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
#include <signal.h>

static volatile int contInt = 0;
static volatile int contStp = 0;

void contadorInt(int cont){
   contInt++;
}
void contadorStp(int cont){
   contStp++;

}
int main(int argc, char **argv) {
   
   struct sigaction saInt;
   saInt.sa_handler = contadorInt;
   saInt.sa_flags = SA_RESTART;

   sigaction(SIGINT, &saInt, 0);

   struct sigaction saStp;
   saStp.sa_handler = contadorStp;
   saStp.sa_flags = SA_RESTART;
   
   sigaction(SIGTSTP, &saStp, 0);

   while((contInt + contStp) < 10){}
   printf("El valor del contador de señales SIGINT es: %i\n", contInt);
   printf("El valor del contador de señales SIGTSTP es: %i\n", contStp);

   return 0;
}
