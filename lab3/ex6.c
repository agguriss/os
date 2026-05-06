/* Παράδειγμα 6 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void read_from_pipe(int file) {
  FILE *stream;
  int c;

  stream = fdopen(file, "r");

  while ((c = fgetc(stream)) != EOF) {
    putchar(c);
  }

  fclose(stream);
}

void write_to_pipe(int file) {
  FILE *stream;

  stream = fdopen(file, "w");

  fprintf(stream, "hello, world!\n");
  fprintf(stream, "goodbye, world!\n");

  fclose(stream);
}

int main(void) {
  pid_t pid;
  int mypipe[2];

  if (pipe(mypipe)) {
    fprintf(stderr, "Απέτυχε η δημιουργία του pipe.\n");
    return EXIT_FAILURE;
  }

  pid = fork();

  if (pid == 0) {
    close(mypipe[1]);
    read_from_pipe(mypipe[0]);
    return EXIT_SUCCESS;
  } else if (pid < 0) {
    fprintf(stderr, "Απέτυχε η fork.\n");
    return EXIT_FAILURE;
  } else {
    close(mypipe[0]);
    write_to_pipe(mypipe[1]);
    wait(NULL);
    return EXIT_SUCCESS;
  }
}