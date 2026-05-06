/* Παράδειγμα 2 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *protasi = "Just a message";

int main(void) {
  int fd[2], bytesread;
  pid_t pid;
  char minima[100];

  pipe(fd);

  pid = fork();

  if (pid == 0) {
    printf("Child: Αυτή είναι η διεργασία-παιδί\n");

    close(fd[0]);

    printf("Child: Γράφοντας στη σωλήνωση\n");
    write(fd[1], protasi, strlen(protasi) + 1);

    printf("Child: Τέλος εγγραφής\n");
    close(fd[1]);

    exit(0);
  } else {
    printf("Parent: Αυτή είναι η διεργασία-πατέρας\n");

    close(fd[1]);

    printf("Parent: Διαβάζοντας από τη σωλήνωση\n");
    bytesread = read(fd[0], minima, sizeof(minima));
    (void)bytesread;

    printf("Parent: το μήνυμα είναι %s\n", minima);
    printf("Parent: Τέλος ανάγνωσης\n");

    close(fd[0]);
    wait(NULL);
  }

  return 0;
}