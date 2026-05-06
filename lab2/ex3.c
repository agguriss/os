/* Παράδειγμα 3 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 1
#define MAX_LINE 1024
#define MAX_ARGS 64

void type_prompt(void) {
  printf("simple_shell> ");
  fflush(stdout);
}

void read_command(char *command, char *parameters[]) {
  char line[MAX_LINE];
  int i = 0;

  if (fgets(line, sizeof(line), stdin) == NULL) {
    exit(0);
  }

  line[strcspn(line, "\n")] = '\0';

  parameters[i] = strtok(line, " ");

  while (parameters[i] != NULL && i < MAX_ARGS - 1) {
    i++;
    parameters[i] = strtok(NULL, " ");
  }

  parameters[i] = NULL;

  if (parameters[0] != NULL) {
    strcpy(command, parameters[0]);
  }
}

int main(void) {
  char command[MAX_LINE];
  char *parameters[MAX_ARGS];
  pid_t pid;
  int status;

  while (TRUE) {
    type_prompt();

    read_command(command, parameters);

    if (parameters[0] == NULL) {
      continue;
    }

    if (strcmp(parameters[0], "exit") == 0) {
      break;
    }

    pid = fork();

    if (pid < 0) {
      printf("Η fork απέτυχε\n");
      continue;
    }

    if (pid != 0) {
      waitpid(pid, &status, 0);
    } else {
      execve(command, parameters, NULL);
      perror("execve");
      exit(1);
    }
  }

  return 0;
}