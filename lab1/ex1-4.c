#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int pid, status, chpid;
    pid = fork();
    if (pid != 0) /* ΚΩΔΙΚΑΣ ΔΙΕΡΓΑΣΙΑΣ ΠΑΤΕΡΑ */
    {
        printf("ιεργασία πατέρας με PID % d και PPID % d\n", getpid(), getppid());
        chpid = wait(&status); /* Επιστρέφει το PID της διεργασίας παιδί που τερματίζεται
          και τοποθετεί ένα κωδικό στη status*/
        printf("Η διεργασία - παιδί με PID % d τερμάτισε με κωδικό εξόδου\n", pid, status);
    }
    else /* ΚΩΔΙΚΑΣ ΔΙΕΡΓΑΣΙΑΣ ΠΑΙΔΙ */
    {
        printf("Διεργασία παιδί με PID % d και PPID % d\n", getpid(), getppid());
        exit(42);
    }
    printf("Η διεργασία με PID % d τερματίζει \n", getpid());
    return 0;
}