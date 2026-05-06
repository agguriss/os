/* Παράδειγμα 1 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  char *args[] = {"/bin/date", NULL};

  printf("Η ημερομηνία είναι:\n");

  execv("/bin/date", args);

  perror("execv");
  return 1;
}