/* Παράδειγμα 7 */
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHELL "/bin/sh"

int my_system(const char *command) {
  int status;
  pid_t pid;

  pid = fork();

  if (pid == 0) {
    execl(SHELL, SHELL, "-c", command, NULL);
    _exit(EXIT_FAILURE);
  } else if (pid < 0) {
    status = -1;
  } else {
    if (waitpid(pid, &status, 0) != pid) {
      status = -1;
    }
  }

  return status;
}

int main(void) { return my_system("ls -l"); }