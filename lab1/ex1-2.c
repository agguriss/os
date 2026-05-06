#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid = fork();
    if (!pid)
        printf("Στο τμήμα του κώδικα της διεργασίας - παιδί pid:%d\n", pid);

    printf("Στο τμήμα του κώδικα της διεργασίας - πατέρα το παιδί είναι : % d\n", pid);
}