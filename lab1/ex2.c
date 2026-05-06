/* Παράδειγμα 2 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  pid_t child;

  child = fork();

  if (child < 0) {
    perror("fork");
    exit(1);
  }

  if (child == 0) {
    printf("Στο τμήμα του κώδικα της διεργασίας-παιδί\n");
    exit(0);
  }

  printf("Στο τμήμα του κώδικα της διεργασίας-πατέρα το παιδί είναι: %d\n",
         child);

  return 0;
}