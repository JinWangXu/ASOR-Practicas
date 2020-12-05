#include <limits.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
   printf("Real User ID: %i - Effective User ID: %i\n", getuid(), geteuid());
   return 0;
}
