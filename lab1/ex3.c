/* Παράδειγμα 3 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  pid_t pid;

  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(1);
  }

  if (pid != 0) {
    printf("Διεργασία πατέρας με PID %d και PPID %d\n", getpid(), getppid());
    printf("Το PID της διεργασίας-παιδί είναι: %d\n", pid);
  } else {
    printf("Διεργασία παιδί με PID %d και PPID %d\n", getpid(), getppid());
  }

  printf("Η διεργασία με PID %d τερματίζει\n", getpid());

  return 0;
}