/* Παράδειγμα 2 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t pid;
  int status;

  char *command = "ls";
  char *params[] = {"ls", "-l", NULL};

  pid = fork();

  if (pid < 0) {
    printf("Η fork απέτυχε\n");
    exit(1);
  }

  if (pid) {
    wait(&status);
  } else {
    if (execvp(command, params) == -1) {
      printf("Η εντολή δεν βρέθηκε.\n");
    }

    exit(0);
  }

  return 0;
}