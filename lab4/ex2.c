/* Παράδειγμα Α2 */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int testvar;

void *start_routine(void *arg) {
  (void)arg;
  int i;

  printf("Το νέο νήμα δημιουργήθηκε και αυτή είναι η ρουτίνα που εκτελεί\n");

  for (i = 0; i < 10; i++) {
    testvar = testvar + i;
  }

  printf("Νέο νήμα: testvar = %d\n", testvar);
  printf("Το νήμα τώρα τερματίζει\n");

  return NULL;
}

int main(void) {
  int retval, i;
  pthread_t thread;

  printf("Δημιουργία νήματος\n");

  retval = pthread_create(&thread, NULL, start_routine, NULL);

  if (retval == 0) {
    printf("Επιτυχής δημιουργία νήματος\n");
  } else {
    printf("Σφάλμα στη δημιουργία νήματος, %d\n", errno);
    abort();
  }

  retval = pthread_join(thread, NULL);

  if (retval != 0) {
    printf("Σφάλμα στην αναμονή join του νήματος, %d\n", errno);
    abort();
  }

  for (i = 0; i < 10; i++) {
    testvar = testvar + 1;
  }

  printf("Τώρα στην πατρική διεργασία η testvar = %d\n", testvar);

  return 0;
}