/* Παράδειγμα Α5 */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int myglobal;

void *thread_function(void *arg) {
  (void)arg;
  int i, j;

  for (i = 0; i < 20; i++) {
    j = myglobal;
    j = j + 1;
    printf(".");
    fflush(stdout);
    sleep(1);
    myglobal = j;
  }

  return NULL;
}

int main(void) {
  pthread_t mythread;
  int i;

  if (pthread_create(&mythread, NULL, thread_function, NULL) != 0) {
    printf("Σφάλμα στη δημιουργία του νήματος %d\n", errno);
    abort();
  }

  for (i = 0; i < 20; i++) {
    myglobal = myglobal + 1;
    printf("o");
    fflush(stdout);
    sleep(1);
  }

  if (pthread_join(mythread, NULL) != 0) {
    printf("Σφάλμα στην αναμονή join του νήματος\n");
    abort();
  }

  printf("\nmyglobal = %d\n", myglobal);

  return 0;
}