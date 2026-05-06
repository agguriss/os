/* Παράδειγμα 6 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  pid_t pid;
  pid_t wpid;
  int status;

  pid = fork();

  if (pid == -1) {
    fprintf(stderr, "%s: απέτυχε η fork()\n", strerror(errno));
    exit(13);
  } else if (pid == 0) {
    printf("PID %ld: η διεργασία-παιδί ξεκίνησε, ο πατέρας είναι %ld.\n",
           (long)getpid(), (long)getppid());
  } else {
    printf("PID %ld: Started child PID %ld.\n", (long)getpid(), (long)pid);

    wpid = wait(&status);

    if (wpid == -1) {
      fprintf(stderr, "%s: wait()\n", strerror(errno));
      return 1;
    } else if (wpid != pid) {
      abort();
    } else {
      printf("η διεργασία-παιδί PID %ld τερμάτισε με κατάσταση εξόδου 0x%04X\n",
             (long)pid, status);
    }
  }

  return 0;
}