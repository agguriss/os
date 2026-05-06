/* Παράδειγμα Α1 */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *start_routine(void *arg) {
  (void)arg;
  printf("Το νέο νήμα δημιουργήθηκε και αυτή είναι η ρουτίνα που εκτελεί\n");
  return NULL;
}

int main(void) {
  int retval;
  pthread_t thread;

  printf("Δημιουργία νήματος\n");

  retval = pthread_create(&thread, NULL, start_routine, NULL);

  if (retval == 0) {
    printf("Επιτυχής δημιουργία νήματος\n");
  } else {
    printf("Σφάλμα στη δημιουργία νήματος, %d\n", errno);
    abort();
  }

  pthread_join(thread, NULL);

  return 0;
}