/* Παράδειγμα 5 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define PERMS 0644

int main(int argc, char *argv[]) {
  int fd[2], fd1, fd2, n;
  pid_t pid;
  char buf[BUFSIZ];

  if (argc != 3) {
    printf("Χρήση: %s <from> <to>\n", argv[0]);
    exit(1);
  }

  fd1 = open(argv[1], O_RDONLY);

  if (fd1 == -1) {
    printf("Σφάλμα: Δεν ανοίγει %s\n", argv[1]);
    exit(1);
  }

  fd2 = creat(argv[2], PERMS);

  if (fd2 == -1) {
    printf("Σφάλμα: Δεν δημιουργείται %s\n", argv[2]);
    exit(1);
  }

  pipe(fd);

  pid = fork();

  if (pid < 0) {
    printf("Σφάλμα: Αποτυχία της fork\n");
    exit(1);
  }

  if (pid == 0) {
    close(fd[1]);

    while ((n = read(fd[0], buf, BUFSIZ)) > 0) {
      if (write(fd2, buf, n) != n) {
        printf("Σφάλμα: σφάλμα κατά την εγγραφή στο αρχείο\n");
        exit(1);
      }
    }

    close(fd[0]);
    close(fd2);
    exit(0);
  } else {
    close(fd[0]);

    while ((n = read(fd1, buf, BUFSIZ)) > 0) {
      if (write(fd[1], buf, n) != n) {
        printf("Σφάλμα: σφάλμα κατά τη διασωλήνωση στο παιδί\n");
        exit(1);
      }
    }

    close(fd[1]);
    close(fd1);
    wait(NULL);
  }

  return 0;
}