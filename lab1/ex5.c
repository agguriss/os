/* Παράδειγμα 5 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  pid_t pid;

  pid = fork();

  if (pid == -1) {
    fprintf(stderr, "%s: απέτυχε η fork()\n", strerror(errno));
    exit(13);
  } else if (pid == 0) {
    printf("PID %ld: η διεργασία-παιδί ξεκίνησε, ο πατέρας είναι %ld.\n",
           (long)getpid(), (long)getppid());
  } else {
    printf("PID %ld: η διεργασία-παιδί ξεκίνησε PID %ld.\n", (long)getpid(),
           (long)pid);
  }

  sleep(1);

  return 0;
}