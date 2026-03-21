#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define DATE_FORMAT_LEN 9

typedef struct{
    char hr[3];
    char min[3];
    char sec[3];
} Time;

typedef struct{
    char dayw[4];
    char mon[4];
    char daym[3];
    Time time;
    char tz[4];
    char year[5];
} Date;

int getDateElements(Date* d){
    char buffer[64];

    FILE* file = popen("date", "r");
    if (file == NULL){
        perror("popen() error");
        return 1;
    }

    if (fgets(buffer, sizeof(buffer), file) == NULL){
        perror("fgets() error");
        pclose(file);
        return 1;
    }

    pclose(file);

    if (sscanf(buffer, "%3s %3s %2s %2[^:]:%2[^:]:%2s %3s %4s",
               d->dayw, d->mon, d->daym,
               d->time.hr, d->time.min, d->time.sec,
               d->tz, d->year) != 8) {
        fprintf(stderr, "sscanf parse error\n");
        return 1;
    }

    return 0;
}

char* getTimestamp(Date* d, char* buffer){
    snprintf(buffer, DATE_FORMAT_LEN, "%s:%s:%s",
             d->time.hr, d->time.min, d->time.sec);
    return buffer;
}

int main(void){
    int pid = getpid();

    Date* date = malloc(sizeof(Date));
    if (date == NULL){
        perror("malloc date");
        return 1;
    }

    memset(date, 0, sizeof(Date));

    char* buffer = malloc(DATE_FORMAT_LEN);
    if (buffer == NULL){
        perror("malloc buffer");
        free(date);
        return 1;
    }

    if (getDateElements(date) == 0){
        printf("pid: %d\n", pid);
        printf("timestamp: %s\n", getTimestamp(date, buffer));
    }

    free(buffer);
    free(date);
    return 0;
}
