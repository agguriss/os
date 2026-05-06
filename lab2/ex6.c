/* Παράδειγμα 6 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PS_PATH "/bin/ps"

extern char **environ;

static void exec_ps_cmd(void) {
  static char *argv[] = {"ps", "-f", NULL};

  execve(PS_PATH, argv, environ);

  fprintf(stderr, "%s: execve()\n", strerror(errno));
  exit(1);
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  pid_t pid;
  pid_t wpid;
  int status;

  pid = fork();

  if (pid == -1) {
    fprintf(stderr, "%s: η fork απέτυχε\n", strerror(errno));
    exit(13);
  } else if (pid == 0) {
    printf("PID %ld: η διεργασία-παιδί ξεκίνησε, ο πατέρας είναι %ld.\n",
           (long)getpid(), (long)getppid());

    exec_ps_cmd();
  } else {
    printf("PID %ld: η διεργασία-παιδί ξεκίνησε PID %ld.\n", (long)getpid(),
           (long)pid);

    wpid = wait(&status);

    if (wpid == -1) {
      fprintf(stderr, "%s: wait()\n", strerror(errno));
      return 1;
    } else if (wpid != pid) {
      abort();
    } else {
      if (WIFEXITED(status)) {
        printf("Exited: $? = %d\n", WEXITSTATUS(status));
      } else if (WIFSIGNALED(status)) {
        printf("Signal: %d%s\n", WTERMSIG(status),
               WCOREDUMP(status) ? " με core file." : "");
      } else {
        printf("Stopped.\n");
      }
    }
  }

  return 0;
}