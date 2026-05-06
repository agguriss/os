/* Παράδειγμα 5 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int i;
  pid_t pidValue;
  int value;
  int status;

  for (i = 0; i < argc; i++) {
    printf("argc[%d] = %s\n", i, argv[i]);
  }

  if (argc > 1) {
    exit(2);
  }

  value = 42;

  pidValue = fork();

  if (pidValue < 0) {
    perror("fork");
    exit(1);
  }

  if (pidValue == 0) {
    printf("Η διεργασία-παιδί: %d\n", value);

    value = 43;

    execl("./fork", "first", "second", NULL);

    perror("execl");
    exit(1);
  } else {
    pid_t pid;

    printf("Πατέρας της διεργασίας %d: %d\n", pidValue, value);

    pid = wait(&status);

    printf("Η διεργασία-παιδί %d τερμάτισε σε κατάσταση: %d\n", (int)pid,
           status);

    printf("value = %d\n", value);
  }

  return 0;
}