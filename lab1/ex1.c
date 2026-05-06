/* Παράδειγμα 1 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t pid;

  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(1);
  } else if (pid > 0) {
    printf("Κώδικας της διεργασίας-πατέρα\n");
  } else {
    printf("Κώδικας της διεργασίας-παιδί\n");
  }

  return 0;
}