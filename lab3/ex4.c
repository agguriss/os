/* Παράδειγμα 4 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd;
  pid_t pid;

  if (argc != 3) {
    printf("Χρήση: %s <εντολή> <αρχείο_εξόδου>\n", argv[0]);
    exit(1);
  }

  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(1);
  }

  if (pid != 0) {
    wait(NULL);
  } else {
    fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
      perror("open");
      exit(1);
    }

    dup2(fd, 1);
    close(fd);

    execlp(argv[1], argv[1], NULL);

    perror("execlp");
    exit(1);
  }

  return 0;
}