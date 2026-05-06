/* Παράδειγμα 4 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t pid, chpid;
  int status;

  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(1);
  }

  if (pid != 0) {
    printf("Διεργασία πατέρας με PID %d και PPID %d\n", getpid(), getppid());

    chpid = wait(&status);

    printf("Η διεργασία-παιδί με PID %d τερμάτισε με κωδικό εξόδου %d\n", chpid,
           status);
  } else {
    printf("Διεργασία παιδί με PID %d και PPID %d\n", getpid(), getppid());
    exit(42);
  }

  printf("Η διεργασία με PID %d τερματίζει\n", getpid());

  return 0;
}