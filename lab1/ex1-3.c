#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pid;
    pid = fork();
    if (pid != 0) /* κώδικας διεργασίας-πατέρα, parent code*/
    {
        printf("Διεργασία πατέρας με PID % d και PPID % d\n", getpid(), getppid());
        printf("Το PID της διεργασίας - παιδί είναι : %d\n", pid);
    }
    else /* κώδικας διεργασίας-παιδί, child code */
        printf("Διεργασία παιδί με PID % d και PPID % d\n", getpid(), getppid());
    printf("Η διεργασία με PID % d τερματίζει \n", getpid());
    return 0;
}